/* -*- c++ -*- */
/*
 * Copyright 2007 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#include <tmac.h>

static bool verbose = false;

static pmt_t s_timeout = pmt_intern("%timeout");

tmac::tmac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mac(rt, instance_name, user_arg),
  d_state(INIT_TMAC),
  d_base_station(true),
  d_last_sync(0)
{
  define_mac_ports();   // Initialize ports for message passing
  
  // Make sure a local address was specified, convert it from PMT to long
  if(!pmt_eqv(pmt_nth(1, user_arg), PMT_NIL)) {
    d_local_address = pmt_to_long(pmt_nth(1, user_arg));
  } else {
    std::cout << "[TMAC] ERROR: Need to specify local address when initializing MAC\n";
    shutdown_all(PMT_F);
  }

  // The local address 0 is reserved for the base station, the total number of
  // nodes needs to be specified if so.
  if(d_local_address==0) {
    d_base_station=true;

    if(!pmt_eqv(pmt_nth(2, user_arg), PMT_NIL)) {
      d_total_nodes = pmt_to_long(pmt_nth(2, user_arg));
    } else {
      std::cout << "[TMAC] ERROR: Need to specify total number of nodes in the network\n";
      shutdown_all(PMT_F);
    }
  }
}

tmac::~tmac()
{
}

void tmac::define_mac_ports()
{
  // Create a small dictionary to pass some information to the PHY
  pmt_t phy_dict = pmt_make_dict();
  pmt_dict_set(phy_dict, pmt_intern("interp-tx"), pmt_from_long(d_usrp_interp));
  pmt_dict_set(phy_dict, pmt_intern("decim-rx"), pmt_from_long(d_usrp_decim));

  // Connect to physical layer
  define_component("GMSK", "gmsk", phy_dict);
  d_gmsk_cs = define_port("phy-cs", "gmsk-cs", false, mb_port::INTERNAL);
  connect("self", "phy-cs", "GMSK", "cs0");

  // Define ports for the application to connect to us
  d_tx = define_port("tx0", "tmac-tx", true, mb_port::EXTERNAL);  // Transmit
  d_rx = define_port("rx0", "tmac-rx", true, mb_port::EXTERNAL);  // Receive
  d_cs = define_port("cs", "tmac-cs", true, mb_port::EXTERNAL);   // Control/Status
}

// Invoked when the base 'mac' class finishes initializing the USRP
void tmac::usrp_initialized()
{
  initialize_tmac();
}

void tmac::initialize_tmac()
{
  d_state = IDLE;   // State where we wait for messages to do something

  // The base station takes special initialization
  if(d_base_station)
    initialize_base_station();
  
//  d_cs->send(s_response_tmac_initialized,   // Notify the application that
//             pmt_list2(PMT_NIL, PMT_T));    // the MAC is initialized

  if(verbose)
    std::cout << "[TMAC] Waiting for SYNC before notifying application of initialization...\n";
}

// This is the crux of the MAC layer.  The general architecture is to have
// states at which the MAC is in, and then handle messages from the application
// and physical layer based on that state.  
// 
// Then, the incoming 'event' (type of message) in the state triggers some
// functionality.  For example, if we are in the idle state and receive a 
// s_cmd_tx_pkt event from the application (detected by the port ID), we send
// the data to the physical layer to be modulated.
//
// Without the m-block to gr-block connection, all raw samples are forced
// through the MAC layer.  So, in the idle state we receive raw incoming
// samples, pass them to the physical layer for demodulation, and listen for
// responses with frames.  Likewise, we send data to the modulator, get
// modulated data back, and then we write it to the USRP.
void tmac::handle_mac_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();      // type of message
  pmt_t data = msg->data();         // the associated data
  pmt_t port_id = msg->port_id();   // the port the msg was received on

  std::string error_msg;

  switch(d_state) {
    
    //----------------------------- INIT TMAC --------------------------------//
    // In the INIT_TMAC state, now that the USRP is initialized.
    case INIT_TMAC:
      goto unhandled;

    //----------------------------- WAIT SYNC -------------------------------//
    // In this state, we're waiting for a synchronization frame from the
    // basestation so that we can aligned our round and slot.
    case WAIT_SYNC:
      goto unhandled;
    
    //----------------------------- IDLE ------------------------------------//
    // In the idle state the MAC is not quite 'idle', it is just not doing
    // anything specific.  It is still being passive with data between the
    // application and the lower layer.
    case IDLE:
      
      //---- Port: TMAC TX -------------- State: IDLE -----------------------//
      if(pmt_eq(d_tx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_tx_pkt)) {
          d_gmsk_cs->send(s_cmd_mod, data);           // Modulate the data
        }
        return;
      }
      
      //---- Port: TMAC CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_cs->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_rx_enable)) {
          enable_rx();                                // Enable RX
        }
        else if(pmt_eq(event, s_cmd_rx_disable)) {
          disable_rx();                               // Disable RX
        }
        return;
      }

      //---- Port: USRP TX -------------- State: IDLE -----------------------//
      if(pmt_eq(d_us_tx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_xmit_raw_frame)) {
          packet_transmitted(data);                   // Transmission successful
        }
        return;
      }
      
      //---- Port: USRP RX -------------- State: IDLE -----------------------//
      if(pmt_eq(d_us_rx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_recv_raw_samples)) {
          d_gmsk_cs->send(s_cmd_demod, data);         // Demod incoming samples
        }
        return;
      }

      //---- Port: GMSK CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_gmsk_cs->port_symbol(), port_id)) {
        
        if(pmt_eq(event, s_response_mod)) {
          transmit_pkt(data);                         // Data done being mod'ed
        }
        else if(pmt_eq(event, s_response_demod)) {
          incoming_frame(data);                       // Incoming frame!
        }
        return;
      }
      goto unhandled;

  } // End of switch()
  
 // Received an unhandled message for a specific state
 unhandled:
  if(0 && verbose && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[TMAC] unhandled msg: " << msg
              << "in state "<< d_state << std::endl;
}

// This method is used for initializing the MAC as a base station, where it will
// transmit synchronization frames at the start of each round.
void tmac::initialize_base_station()
{
  // The base station specifies the guard time, which it will transmit in its
  // synchronization packets.
  d_guard_time = 1000;
  calculate_parameters();

  // Schedule the initial synchronization frame.
  transmit_sync();
}

// Handles the transmission of a pkt from the application.  The invocation
// handle is passed on but a response is not given back to the application until
// the response is passed from usrp_server.  This ensures that the MAC passes
// back the success or failure. 
void tmac::transmit_pkt(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t samples = pmt_nth(1, data);
  pmt_t pkt_properties = pmt_nth(2, data);

  // A dictionary (a hash like structure) that is used to pass packet properties
  // down the layers.
  pmt_t us_tx_properties = pmt_make_dict();

  pmt_t timestamp = pmt_from_long(0xffffffff);	// 0xffffffff == transmit NOW!

  pmt_t pdata = pmt_list5(invocation_handle,    // Invocation handle is passed back.
		                      d_us_tx_chan,         // Destined for our TX channel.
		                      samples,              // The modulated data (samples).
                          timestamp,            // The time to send the packet.
                          us_tx_properties);    // Our per-packet properties.

  d_us_tx->send(s_cmd_xmit_raw_frame, pdata);   // Finally, send!

  if(verbose && 0)
    std::cout << "[TMAC] Transmitted packet\n";
}

// Invoked when we get a response that a packet was written to the USRP USB bus,
// we assume that it has been transmitted (or will be, within negligable time).
//
// The application is NOT informed that the packet was transmitted successfully
// until an ACK is received, so we enter an ACK wait state.
void tmac::packet_transmitted(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t status = pmt_nth(1, data);

  enable_rx();  // Need to listen for ACKs
  
  d_state = IDLE;
}

// An incoming frame from the physical layer for us!  We check the packet
// properties to determine the sender and if it passed a CRC check, for example.
void tmac::incoming_frame(pmt_t data)
{
  pmt_t invocation_handle = PMT_NIL;
  pmt_t payload = pmt_nth(0, data);
  pmt_t pkt_properties = pmt_nth(1, data);

  // Let's do some checking on the demoded frame
  long lsrc=0, ldst=0;
  bool b_crc = false;

  // Properties are set in the physical layer framing code
  lsrc = pmt_to_long(pmt_dict_ref(pkt_properties,
                                  pmt_intern("src"),
                                  PMT_NIL));

  ldst = pmt_to_long(pmt_dict_ref(pkt_properties,
                                  pmt_intern("dst"),
                                  PMT_NIL));

  if(pmt_t crc = pmt_dict_ref(pkt_properties,
                              pmt_intern("crc"),
                              PMT_NIL)) {
    if(pmt_eqv(crc, PMT_T))
      b_crc = true;   // payload passed CRC
    else
      b_crc = false;  // payload failed CRC
  }

  if(ldst != d_local_address)  // not for this address
    return;
  
  d_rx->send(s_response_rx_pkt, pmt_list3(invocation_handle, payload, pkt_properties));

  if(verbose)
    std::cout << "[TMAC] Passing up demoded frame\n";
}

void tmac::transmit_sync()
{

}

void tmac::incoming_sync(pmt_t data)
{

}

// Here we calculate the crucial TDMA parameters.  Everything is calculated in
// clock cycles, which is 1/64e6 based on the FPGA clock.
void tmac::calculate_parameters()
{
  // The number of clock cycles a bit transmission/reception takes
  d_clock_ticks_per_bit = (d_usrp_decim * gmsk::samples_per_symbol()) / BITS_PER_SYMBOL;

  // The slot time is fixed to the maximum frame time over the air.
  d_slot_time = (gmsk::max_frame_size() * BITS_PER_BYTE) * d_clock_ticks_per_bit;

  // The local slot offset depends on the local address and slot/guard times.
  // The local address defines the node's slot assignment.  Slot 0 is for the
  // base station.
  d_local_slot_offset = d_local_address * (d_slot_time + d_guard_time);
}

REGISTER_MBLOCK_CLASS(tmac);

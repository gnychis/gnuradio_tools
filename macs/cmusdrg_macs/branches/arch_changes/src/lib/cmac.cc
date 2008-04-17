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

#include <cmac.h>

static bool verbose = false;

static pmt_t s_timeout = pmt_intern("%timeout");

cmac::cmac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mac(rt, instance_name, user_arg),
  d_state(INIT_CMAC)
{
  define_mac_ports();   // Initialize ports for message passing
  d_local_address = pmt_to_long(pmt_nth(1, user_arg));
}

cmac::~cmac()
{
}

void cmac::define_mac_ports()
{
  // Create a small dictionary to pass some information to the PHY
  pmt_t phy_dict = pmt_make_dict();
  pmt_dict_set(phy_dict, pmt_intern("interp-tx"), pmt_from_long(d_usrp_interp));
  pmt_dict_set(phy_dict, pmt_intern("decim-rx"), pmt_from_long(d_usrp_decim));

  // Connect to physical layer
  define_component("GMSK", "gmsk", phy_dict);
  d_phy_cs = define_port("phy-cs", "gmsk-cs", false, mb_port::INTERNAL);
  connect("self", "phy-cs", "GMSK", "cs0");

  // Define ports for the application to connect to us
  d_tx = define_port("tx0", "cmac-tx", true, mb_port::EXTERNAL);  // Transmit
  d_rx = define_port("rx0", "cmac-rx", true, mb_port::EXTERNAL);  // Receive
  d_cs = define_port("cs", "cmac-cs", true, mb_port::EXTERNAL);   // Control/Status
}

// Invoked when the base 'mac' class finishes initializing the USRP
void cmac::usrp_initialized()
{
  initialize_cmac();
}

void cmac::initialize_cmac()
{
  set_carrier_sense(false, 25, 0, PMT_NIL);   // Initial carrier sense setting

  d_state = IDLE;   // State where we wait for messages to do something
  
  d_cs->send(s_response_cmac_initialized,   // Notify the application that
             pmt_list2(PMT_NIL, PMT_T));    // the MAC is initialized

  if(verbose)
    std::cout << "[CMAC] Initialized, and idle\n";
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
void cmac::handle_mac_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();      // type of message
  pmt_t data = msg->data();         // the associated data
  pmt_t port_id = msg->port_id();   // the port the msg was received on

  std::string error_msg;

  switch(d_state) {
    
    //----------------------------- INIT CMAC --------------------------------//
    // In the INIT_CMAC state, now that the USRP is initialized we can do things
    // like right the carrier sense threshold to the FPGA register.
    case INIT_CMAC:
      goto unhandled;
    
    //----------------------------- IDLE ------------------------------------//
    // In the idle state the MAC is not quite 'idle', it is just not doing
    // anything specific.  It is still being passive with data between the
    // application and the lower layer.
    case IDLE:
      
      //---- Port: CMAC TX -------------- State: IDLE -----------------------//
      if(pmt_eq(d_tx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_tx_pkt)) {
          d_phy_cs->send(s_cmd_mod, data);           // Modulate the data
        }
        return;
      }
      
      //---- Port: CMAC CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_cs->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_carrier_sense_enable)) {
          enable_carrier_sense(data);                 // Enable carrier sense
        }
        else if(pmt_eq(event, s_cmd_carrier_sense_threshold)) {
          set_carrier_sense_threshold(data);          // Change CS threshold
        } 
        else if(pmt_eq(event, s_cmd_carrier_sense_deadline)) {
          set_carrier_sense_deadline(data);           // Change CS deadline
        }
        else if(pmt_eq(event, s_cmd_carrier_sense_disable)) {
          disable_carrier_sense(data);                // Disable CS
        }
        else if(pmt_eq(event, s_cmd_rx_enable)) {
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
      
      //---- Port: GMSK CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_phy_cs->port_symbol(), port_id)) {
        
        if(pmt_eq(event, s_response_demod)) {
          incoming_data(data);                       // Incoming frame!
        }
        return;
      }
      goto unhandled;


    //---------------------------- ACK WAIT ----------------------------------//
    // In this state, we are waiting for an ACK back before we pass up a
    // "successfull transmission" message to the application.  If we do not get
    // an ACK within a timeout, we retransmit.
    case ACK_WAIT:

      //--------- ACK TIMEOUT -----------------------------------------------//
      // FAIL! We've hit an ACK timeout, time to panic and retransmit.
      // The timer automatically resets, if we want to get smart we can keep
      // track of how many times its fired before we tell the application the
      // transmission has failed.
      if(pmt_eq(event, s_timeout)) {
        std::cout << "x";
        fflush(stdout);
        d_us_tx->send(s_cmd_xmit_raw_frame, d_last_frame);
        return;
      }
      
      //---- Port: USRP RX -------------- State: ACK_WAIT -------------------//
      if(pmt_eq(d_us_rx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_recv_raw_samples)) {
          d_phy_cs->send(s_cmd_demod, data);         // Demod incoming samples
        }
        return;
      }

      //---- Port: GMSK CS -------------- State: ACK_WAIT -------------------//
      if(pmt_eq(d_phy_cs->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_demod)) {
          incoming_data(data);                       // Incoming frame! ACK?
        }
        return;
      }
      goto unhandled;

    
    //---------------------------- SEND ACK ----------------------------------//
    // In this state, we only expect our modulated ACK data to get back from
    // the PHY layer, and then we ship it to usrp_server, and wait for a
    // response back before enabled RX again.
    case SEND_ACK:

      //---- Port: GMSK CS -------------- State: SEND_ACK -------------------//
      if(pmt_eq(d_phy_cs->port_symbol(), port_id)) {
        
        if(pmt_eq(event, s_response_mod)) {
          //transmit_pkt(data);                         // Incoming mod'ed ACK
        }
        return;
      }
        
      //---- Port: USRP TX -------------- State: SEND_ACK -------------------//
      if(pmt_eq(d_us_tx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_xmit_raw_frame)) {
          enable_rx();                                // Response from ACK trans,
          d_state = IDLE;                             // enable RX and enter idle
        }
        return;
      }
      goto unhandled;

  } // End of switch()
  
 // Received an unhandled message for a specific state
 unhandled:
  if(0 && verbose && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[CMAC] unhandled msg: " << msg
              << "in state "<< d_state << std::endl;
}

// Method to handle setting carrier sense within the FPGA via register writes.
void cmac::set_carrier_sense(bool toggle, long threshold, long deadline, pmt_t invocation)
{
  d_carrier_sense = toggle;

  d_us_tx->send(s_cmd_to_control_channel, 
             pmt_list2(invocation, 
                       pmt_list1(
                            pmt_list2(s_op_write_reg, 
                                      pmt_list2(
                                      pmt_from_long(REG_CS_THRESH), 
                                      pmt_from_long(threshold))))));

  d_us_tx->send(s_cmd_to_control_channel, 
             pmt_list2(invocation, 
                       pmt_list1(
                            pmt_list2(s_op_write_reg, 
                                      pmt_list2(
                                      pmt_from_long(REG_CS_DEADLINE), 
                                      pmt_from_long(deadline))))));

  d_cs_thresh = threshold;    // Save our new threshold
  d_cs_deadline = deadline;   // Keep the deadline

  if(verbose)
    std::cout << "[CMAC] Setting carrier sense to " << toggle 
              << "\n ... threshold: " << d_cs_thresh
              << "\n ... deadline:  " << d_cs_deadline
              << std::endl;
}

// Invoked when we get a response that a packet was written to the USRP USB bus,
// we assume that it has been transmitted (or will be, within negligable time).
//
// The application is NOT informed that the packet was transmitted successfully
// until an ACK is received, so we enter an ACK wait state.
void cmac::packet_transmitted(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t status = pmt_nth(1, data);

  enable_rx();  // Need to listen for ACKs
  
  // Schedule an ACK timeout to fire every timeout period. This should be user
  // settable.  The first timeout is now+TIMEOUT_PERIOD
  const double TIMEOUT_PERIOD = 0.15;  // in seconds
  mb_time now = mb_time::time();
  d_ack_timeout = schedule_periodic_timeout(now + TIMEOUT_PERIOD, mb_time(TIMEOUT_PERIOD), PMT_T);
  
  d_state = ACK_WAIT;

}

// This method determines whether carrier sense should be enabled based on two
// properties.  The first is the MAC setting, which the user can set to carrier
// sense packets by default or not.  The second is a per packet setting, which
// can be used to override the MAC setting for the given packet only.
bool cmac::carrier_sense_pkt(pmt_t pkt_properties) 
{
  // First we extract the per packet properties to check the per packet setting
  // if it exists
  if(pmt_is_dict(pkt_properties)) {

    if(pmt_t pkt_cs = pmt_dict_ref(pkt_properties,
                                   pmt_intern("carrier-sense"),
                                   PMT_NIL)) {
      // If the per packet property says true, enable carrier sense regardless
      // of the MAC setting
      if(pmt_eqv(pkt_cs, PMT_T))
        return true;
      // If the per packet setting says false, disable carrier sense regardless
      // of the MAC setting
      else if(pmt_eqv(pkt_cs, PMT_F))
        return false;
    }
  }

  // If we've hit this point, the packet properties did not state whether
  // carrier sense should be used or not, so we use the MAC setting
  if(d_carrier_sense)
    return true;
  else
    return false;

}

// This method is envoked by an incoming cmd-enable-carrier-sense signal on the
// C/S port.  It can be used to re-adjust the threshold or simply enabled
// carrier sense. 
void cmac::enable_carrier_sense(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t threshold = pmt_nth(1, data);
  pmt_t deadline = pmt_nth(2, data);
  long l_threshold, l_deadline;

  // FIXME: for now, if threshold is NIL, we do not change the threshold.
  // This should be replaced with an averaging algorithm
  if(pmt_eqv(threshold, PMT_NIL))
    l_threshold = d_cs_thresh;
  else
    l_threshold = pmt_to_long(threshold);

  // If the deadline is NIL, we do not change the value
  if(pmt_eqv(threshold, PMT_NIL))
    l_deadline = d_cs_deadline;
  else
    l_deadline = pmt_to_long(deadline);
  
  set_carrier_sense(true, l_threshold, l_deadline, invocation_handle);
}

// This method is called when an incoming disable carrier sense command is sent
// over the control status channel.  
void cmac::disable_carrier_sense(pmt_t data) 
{
  pmt_t invocation_handle = pmt_nth(0, data);
  
  // We don't change the threshold, we leave it as is because the application
  // did not request that it changes, only to disable carrier sense.
  set_carrier_sense(false, d_cs_thresh, d_cs_deadline, invocation_handle);
}

// Only change the carrier sense threshold, nothing else, including the state.
void cmac::set_carrier_sense_threshold(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t threshold = pmt_nth(1, data);
  long l_threshold;

  if(pmt_eqv(threshold, PMT_NIL))
    l_threshold = d_cs_thresh;
  else
    l_threshold = pmt_to_long(threshold);
  
  set_carrier_sense(d_carrier_sense, l_threshold, d_cs_deadline, invocation_handle);
}

// Change the carrier sense deadline, AKA the time to wait for the channel to
// become idle before throwing it away.
void cmac::set_carrier_sense_deadline(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t deadline = pmt_nth(1, data);
  long l_deadline;

  // If the deadline passed is NIL, do *not* change the value.
  if(pmt_eqv(deadline, PMT_NIL))
    l_deadline = d_cs_deadline;
  else
    l_deadline = pmt_to_long(deadline);
  
  set_carrier_sense(d_carrier_sense, d_cs_thresh, l_deadline, invocation_handle);
}

// An incoming frame from the physical layer for us!  We check the packet
// properties to determine the sender and if it passed a CRC check, for example.
void cmac::incoming_frame(pmt_t data)
{
  pmt_t invocation_handle = PMT_NIL;
  pmt_t payload = pmt_nth(0, data);
  pmt_t pkt_properties = pmt_nth(1, data);

  // Let's do some checking on the demoded frame
  long lsrc=0, ldst=0;
  bool b_crc = false;
  bool b_ack = false;

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

  if(pmt_t ack = pmt_dict_ref(pkt_properties,
                              pmt_intern("ack"),
                              PMT_NIL)) {
    if(pmt_eqv(ack, PMT_T))
      b_ack = true;   // frame is an ACK
    else
      b_ack = false;  // frame is not an ACK
  }

  if(b_ack) {         // Handle ACKs in a special manner
    handle_ack(lsrc, ldst);
    return;
  }

  if(ldst != d_local_address)  // not for this address
    return;
  
  if(b_crc)  // CRC passes, let's ACK the source
    build_and_send_ack(lsrc);

  d_rx->send(s_response_rx_pkt, pmt_list3(invocation_handle, payload, pkt_properties));

  if(verbose)
    std::cout << "[CMAC] Passing up demoded frame\n";
}

// Special handling for ACK frames
void cmac::handle_ack(long src, long dst)
{
  // CMAC does not care about frames if we're not in the ACK_WAIT state
  if(d_state!=ACK_WAIT)
    return;

  cancel_timeout(d_ack_timeout);    // Cancel our ACK timeout

  // Now that we have an ACK, we can notify the application of a successfully TX
  pmt_t invocation_handle = pmt_nth(0, d_last_frame);
  d_tx->send(s_response_tx_pkt,
             pmt_list2(invocation_handle,
                       PMT_T));

  disable_rx();     // FIXME: spend more time thinking about this, I think its incorrect

  d_state = IDLE;   // Back to the idle state!

  return;
}

void cmac::build_and_send_ack(long dst)
{
  size_t ignore;
  char data;
  long n_bytes=1;   // Negligable payload
  
  disable_rx();     // No need to receive while transmitting, not required,
                    // only saves processing power.

  // Make the PMT data, get a writable pointer to it, then copy our data in
  pmt_t uvec = pmt_make_u8vector(n_bytes, 0);
  char *vdata = (char *) pmt_u8vector_writeable_elements(uvec, ignore);
  memcpy(vdata, &data, n_bytes);

  // Per packet properties
  pmt_t tx_properties = pmt_make_dict();

  pmt_dict_set(tx_properties, pmt_intern("ack"), PMT_T);  // it's an ACK!

  pmt_t pdata = pmt_list5(PMT_NIL,                        // No invocation.
                          pmt_from_long(d_local_address), // From us.
                          pmt_from_long(dst),             // To them.
                          uvec,                           // With data.
                          tx_properties);                 // It's an ACK!

  d_phy_cs->send(s_cmd_mod, pdata);    // Modulate the ACK
  
  d_state = SEND_ACK;                   // Switch MAC states
  
  if(verbose)
    std::cout << "[CMAC] Transmitted ACK from " << d_local_address
              << " to " << dst
              << std::endl;
}

REGISTER_MBLOCK_CLASS(cmac);

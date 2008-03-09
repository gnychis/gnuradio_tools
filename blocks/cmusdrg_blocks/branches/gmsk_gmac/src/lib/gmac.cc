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

#include <gmac.h>

static bool verbose = false;

static pmt_t s_timeout = pmt_intern("%timeout");

gmac::gmac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mac(rt, instance_name, user_arg)
{

  // Initialize the ports
  define_mac_ports();

  // Extract local address from user argument
  // FIXME: just take the local IP address of some interface...
  d_local_address = pmt_to_long(pmt_nth(1, user_arg));

}

gmac::~gmac()
{
}

// The MAC layer connects to 'usrp_server' which has a control/status channel,
// a TX, and an RX port.  The MAC layer can then relay TX/RX data back and
// forth to the application, or a physical layer once available.
void gmac::define_mac_ports()
{
  // ports we use to connect to gmsk
  define_component("GMSK", "gmsk", PMT_NIL);
  d_gmsk_cs = define_port("phy-cs", "gmsk-cs", false, mb_port::INTERNAL);
  connect("self", "phy-cs", "GMSK", "cs0");

  // Ports applications used to connect to us
  d_tx = define_port("tx0", "gmac-tx", true, mb_port::EXTERNAL);
  d_rx = define_port("rx0", "gmac-rx", true, mb_port::EXTERNAL);
  d_cs = define_port("cs", "gmac-cs", true, mb_port::EXTERNAL);
}

// We override the method that is called when the USRP is done initializing and
// use it to bootstrap our MAC
void gmac::usrp_initialized()
{
  initialize_gmac();
}

// In the initialization state of the MAC layer we set default values for
// several functionalities.
void gmac::initialize_gmac()
{

  // The initial state is the INIT state.
  d_state = INIT_GMAC;

  // Set carrier sense to enabled by default with the specified threshold and
  // the deadline to 0 -- which is wait forever.
  set_carrier_sense(false, 25, 0, PMT_NIL);

  // Can now notify the application that we are initialized
  d_cs->send(s_response_gmac_initialized,
             pmt_list2(PMT_NIL, PMT_T));

  // The MAC enters an IDLE state where it waits for messages and dispatches
  // based on them
  d_state = IDLE;

  if(verbose)
    std::cout << "[GMAC] Initialized, and idle\n";
}


// FIXME: lets have two handle_messages, one for the setup junk to be reused
//        and the other strictly for GMAC.

// The full functionality of GMAC is based on messages passed back and forth
// between the application and a physical layer and/or usrp_server.  Each
// message triggers additional events, states, and messages to be sent.
void gmac::handle_mac_message(mb_message_sptr msg)
{

  // The MAC functionality is dispatched based on the event, which is the
  // driving force of the MAC.  The event can be anything from incoming samples
  // to a message to change the carrier sense threshold.
  pmt_t event = msg->signal();
  pmt_t data = msg->data();
  pmt_t port_id = msg->port_id();

  pmt_t handle = PMT_F;
  pmt_t status = PMT_F;
  pmt_t dict = PMT_NIL;
  std::string error_msg;

  switch(d_state) {
    
    //----------------------------- INIT GMAC --------------------------------//
    // In the INIT_GMAC state, now that the USRP is initialized we can do things
    // like right the carrier sense threshold to the FPGA register.
    case INIT_GMAC:
      goto unhandled;

    
    //----------------------------- IDLE ------------------------------------//
    // In the idle state the MAC is not quite 'idle', it is just not doing
    // anything specific.  It is still being passive with data between the
    // application and the lower layer.
    case IDLE:
      
      //---- Port: GMAC TX -------------- State: IDLE -----------------------//
      if(pmt_eq(d_tx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_tx_pkt)) {
          d_gmsk_cs->send(s_cmd_mod, data);           // Modulate the data
        }
        return;
      }
      
      //---- Port: GMAC CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_cs->port_symbol(), port_id)) {

        if(pmt_eq(event, s_cmd_set_address)) {
          handle_cmd_set_address(data);               // Set local address
        }         
        else if(pmt_eq(event, s_cmd_carrier_sense_enable)) {
          handle_cmd_carrier_sense_enable(data);      // Enable carrier sense
        }
        else if(pmt_eq(event, s_cmd_carrier_sense_threshold)) {
          handle_cmd_carrier_sense_threshold(data);   // Change CS threshold
        } 
        else if(pmt_eq(event, s_cmd_carrier_sense_deadline)) {
          handle_cmd_carrier_sense_deadline(data);    // Change CS deadline
        }
        else if(pmt_eq(event, s_cmd_carrier_sense_disable)) {
          handle_cmd_carrier_sense_disable(data);     // Disable CS
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
          handle_response_xmit_raw_frame(data);       // Transmission successful
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
          handle_cmd_tx_pkt(data);                    // Data done being mod'ed
        }
        else if(pmt_eq(event, s_response_demod)) {
          handle_response_demod(data);                // Incoming frame!
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
      // I'm not taking the time to disable the RX port since we don't need any
      // processing power to modulate, since we've cached the modulated data.
      //
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
          d_gmsk_cs->send(s_cmd_demod, data);         // Demod incoming samples
        }
        return;
      }

      //---- Port: GMSK CS -------------- State: ACK_WAIT -------------------//
      if(pmt_eq(d_gmsk_cs->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_demod)) {
          handle_response_demod(data);                // Incoming frame! ACK?
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
      if(pmt_eq(d_gmsk_cs->port_symbol(), port_id)) {
        
        if(pmt_eq(event, s_response_mod)) {
          handle_cmd_tx_pkt(data);                    // Incoming mod'ed ACK
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
  
 // An error occured, print it, and shutdown all m-blocks
 bail:
  std::cerr << error_msg << data
      	    << "status = " << status << std::endl;
  shutdown_all(PMT_F);
  return;

 // Received an unhandled message for a specific state
 unhandled:
  if(0 && verbose && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[GMAC] unhandled msg: " << msg
              << "in state "<< d_state << std::endl;
}

// Method for setting the carrier sense and an associated threshold which is
// written to a register on the FPGA, which it will read if the CS flag is set
// and perform carrier sense based on.
//
// We currently do not wait for the successful response for the write to
// register command, we assume it will succeed else the MAC must
void gmac::set_carrier_sense(bool toggle, long threshold, long deadline, pmt_t invocation)
{
  d_carrier_sense = toggle;

  // Only waste the bandwidth and processing of a C/S packet if needed
  if(threshold != d_cs_thresh) {
    d_us_tx->send(s_cmd_to_control_channel,    // C/S packet
               pmt_list2(invocation,           // invoc handle
                         pmt_list1(
                              pmt_list2(s_op_write_reg, 
                                        pmt_list2(
                                        pmt_from_long(REG_CS_THRESH), 
                                        pmt_from_long(threshold))))));
    d_cs_thresh = threshold;

    if(verbose)
      std::cout << "[GMAC] Changing CS threshold: " << d_cs_thresh << std::endl;
  }

  if(deadline != d_cs_deadline) {
    d_us_tx->send(s_cmd_to_control_channel,    // C/S packet
               pmt_list2(invocation,           // invoc handle
                         pmt_list1(
                              pmt_list2(s_op_write_reg, 
                                        pmt_list2(
                                        pmt_from_long(REG_CS_DEADLINE), 
                                        pmt_from_long(deadline))))));
    d_cs_deadline = deadline;

    if(verbose)
      std::cout << "[GMAC] Changing CS deadline: " << d_cs_deadline << std::endl;
  }

  if(verbose)
    std::cout << "[GMAC] Setting carrier sense to " << toggle << std::endl;
}


// Handles the transmission of a pkt from the application.  The invocation
// handle is passed on but a response is not given back to the application until
// the response is passed from usrp_server.  This ensures that the MAC passes
// back the success or failure.  Furthermore, the MAC could decide to retransmit
// on a failure based on the result of the packet transmission.
//
// This should eventually be connected to a physically layer rather than
// directly to usrp_server. (d_us_tx should be replaced with a different
// connection)
void gmac::handle_cmd_tx_pkt(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t samples = pmt_nth(1, data);
  pmt_t pkt_properties = pmt_nth(2, data);

  pmt_t us_tx_properties = pmt_make_dict();

  // Set the packet to be carrier sensed?
  if(carrier_sense_pkt(pkt_properties))
    pmt_dict_set(us_tx_properties,
                 pmt_intern("carrier-sense"),
                 PMT_T);

  pmt_t timestamp = pmt_from_long(0xffffffff);	// NOW

  // Construct the proper message for USRP server
  pmt_t pdata = pmt_list5(invocation_handle,
		                      d_us_tx_chan,
		                      samples, 
                          timestamp,
                          us_tx_properties);

  d_us_tx->send(s_cmd_xmit_raw_frame, pdata);

  // Save the modulated data incase of a need to retransmit, we don't need to
  // re-modulate it
  d_last_frame = pdata;

  if(verbose && 0)
    std::cout << "[GMAC] Transmitted packet\n";
}

// Handles a response from the USRP server about the transmission of a frame,
// whether it was successful or failed.  This should eventually be replaced with
// a response from the PHY layer.  This is where a retransmit could be
// implemented.
void gmac::handle_response_xmit_raw_frame(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t status = pmt_nth(1, data);

  // Now we enter an ACK wait state before we send the response
  // that we've sucessfully transmitted.
  enable_rx();
  
  // Schedule an ACK timeout to fire every timeout period. This should be user
  // settable.  The first timeout is now+TIMEOUT_PERIOD
  const double TIMEOUT_PERIOD = 0.1;  // in seconds
  mb_time now = mb_time::time();
  d_ack_timeout = schedule_periodic_timeout(now + TIMEOUT_PERIOD, mb_time(TIMEOUT_PERIOD), PMT_T);
  
  d_state = ACK_WAIT;

}

// This method determines whether carrier sense should be enabled based on two
// properties.  The first is the MAC setting, which the user can set to carrier
// sense packets by default or not.  The second is a per packet setting, which
// can be used to override the MAC setting for the given packet only.
bool gmac::carrier_sense_pkt(pmt_t pkt_properties) 
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
// carrier sense.  When a threshold is not provided, the MAC will use an
// averaging algorithm to determine the threshold (in the future).
void gmac::handle_cmd_carrier_sense_enable(pmt_t data)
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
// over the control status channel.  It so far does not ellicit a response, this
// needs to be added correctly.  It needs to wait for the response for the C/S
// packet from usrp_server.
void gmac::handle_cmd_carrier_sense_disable(pmt_t data) 
{
  pmt_t invocation_handle = pmt_nth(0, data);
  
  // We don't change the threshold, we leave it as is because the application
  // did not request that it changes, only to disable carrier sense.
  set_carrier_sense(false, d_cs_thresh, d_cs_deadline, invocation_handle);
}

// When the app requests that the threshold changes, the state of the carrier
// sense should not change.  If it was enabled, it should remain enabled.
// Likewise if it was disabled.  The deadline value should also remain
// unchanged.
void gmac::handle_cmd_carrier_sense_threshold(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t threshold = pmt_nth(1, data);
  long l_threshold;

  // FIXME: for now, if threshold is NIL, we do not change the threshold.
  // This should be replaced with an averaging algorithm
  if(pmt_eqv(threshold, PMT_NIL))
    l_threshold = d_cs_thresh;
  else
    l_threshold = pmt_to_long(threshold);
  
  set_carrier_sense(d_carrier_sense, l_threshold, d_cs_deadline, invocation_handle);
}

// Ability to change the deadline using a C/S packet.  The state of all other
// carrier sense parameters should not change.
void gmac::handle_cmd_carrier_sense_deadline(pmt_t data)
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

// Set the local address of the node
// FIXME: try to pick up the MAC address of the Ethernet for fun
void gmac::handle_cmd_set_address(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  long address = pmt_to_long(pmt_nth(1, data));

  d_local_address = address;
}

// Pass up a demoded frame
void gmac::handle_response_demod(pmt_t data)
{
  pmt_t invocation_handle = PMT_NIL;
  pmt_t payload = pmt_nth(0, data);
  pmt_t pkt_properties = pmt_nth(1, data);

  // Let's do some checking on the demoded frame
  long lsrc=0, ldst=0;
  bool bcrc = false;
  bool back = false;

  // Use the packet properties creating by the framing code in GMSK
  if(pmt_is_dict(pkt_properties)) {

    if(pmt_t src = pmt_dict_ref(pkt_properties,
                                pmt_intern("src"),
                                PMT_NIL)) {
      if(!pmt_eqv(src, PMT_NIL))
        lsrc = pmt_to_long(src);
    }
    
    if(pmt_t dst = pmt_dict_ref(pkt_properties,
                                pmt_intern("dst"),
                                PMT_NIL)) {
      if(!pmt_eqv(dst, PMT_NIL))
        ldst = pmt_to_long(dst);
    }

    if(pmt_t crc = pmt_dict_ref(pkt_properties,
                                pmt_intern("crc"),
                                PMT_NIL)) {
      if(pmt_eqv(crc, PMT_T))
        bcrc = true;  // CRC on payload passed
      else
        bcrc = false; // CRC on payload failed
    }

    if(pmt_t ack = pmt_dict_ref(pkt_properties,
                                pmt_intern("ack"),
                                PMT_NIL)) {
      if(pmt_eqv(ack, PMT_T))
        back = true;
      else
        back = false;
    }
  }

  // If we were in the ACK_WAIT state and the frame is an ACK, then we
  // transmitted successfully! Let's tell the application to move on.
  if(d_state==ACK_WAIT && back==true) {
    cancel_timeout(d_ack_timeout);
    invocation_handle = pmt_nth(0, d_last_frame);
    d_tx->send(s_response_tx_pkt,
               pmt_list2(invocation_handle,
                         PMT_T));
    disable_rx();
    d_state = IDLE;
    return;
  }

  if(ldst != d_local_address)  // not for this address
    return;
  
  if(bcrc)  // CRC passes, let's ACK the source
    build_and_send_ack(lsrc);

  d_rx->send(s_response_rx_pkt, pmt_list3(invocation_handle, payload, pkt_properties));

  if(verbose)
    std::cout << "[GMAC] Passing up demoded frame\n";
}

void gmac::build_and_send_ack(long dst)
{
  size_t ignore;
  long n_bytes;
  
  // Before we send the frame, we stop the RX port since we are not interested
  // in decoding while transmitting, and full processing can go to TX
  disable_rx();

  char data[1];
  n_bytes=1;

  // Make the PMT data, get a writable pointer to it, then copy our data in
  pmt_t uvec = pmt_make_u8vector(n_bytes, 0);
  char *vdata = (char *) pmt_u8vector_writeable_elements(uvec, ignore);
  memcpy(vdata, data, n_bytes);

  // Per packet properties
  pmt_t tx_properties = pmt_make_dict();

  // Specify that it's an ACK
  pmt_dict_set(tx_properties, pmt_intern("ack"), PMT_T);

  pmt_t timestamp = pmt_from_long(0xffffffff);	// NOW
  pmt_t pdata = pmt_list5(PMT_NIL,
                          pmt_from_long(d_local_address),
                          pmt_from_long(dst),
                          uvec,
                          tx_properties);

  d_gmsk_cs->send(s_cmd_mod, pdata);
  
  if(verbose)
    std::cout << "[GMAC] Transmitted ACK from " << d_local_address
              << " to " << dst
              << std::endl;
  
  d_state = SEND_ACK;

}

REGISTER_MBLOCK_CLASS(gmac);

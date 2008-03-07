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

#include <mac.h>

static bool verbose = true;

mac::mac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(rt, instance_name, user_arg),
    d_us_rx_chan(PMT_NIL), d_us_tx_chan(PMT_NIL)
{

  // Initialize the ports
  define_usrp_ports();

  // Initialize the connection to the USRP
  pmt_t usrp_data = pmt_nth(0, user_arg);
  initialize_usrp(usrp_data);

}

void mac::define_usrp_ports()
{
  // Ports we use to connect to usrp_server
  d_us_tx = define_port("us-tx0", "usrp-tx", false, mb_port::INTERNAL);
  d_us_rx = define_port("us-rx0", "usrp-rx", false, mb_port::INTERNAL);
  d_us_cs = define_port("us-cs", "usrp-server-cs", false, mb_port::INTERNAL);
}

void mac::handle_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();
  pmt_t data = msg->data();
  pmt_t port_id = msg->port_id();

  // Messages are split between low level USRP server messages, and messages
  // for the MAC to handle, which the user overrides.
  if(pmt_eq(port_id, d_us_cs->port_symbol()) ||
     pmt_eq(port_id, d_us_tx->port_symbol()) ||
     pmt_eq(port_id, d_us_rx->port_symbol()))
    handle_usrp_message(msg);
  else
    handle_mac_message(msg);
}

void mac::handle_mac_message(mb_message_sptr msg)
{
}

void mac::handle_usrp_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();
  pmt_t data = msg->data();
  pmt_t port_id = msg->port_id();

  pmt_t handle = PMT_F;
  pmt_t status = PMT_F;
  pmt_t dict = PMT_NIL;
  std::string error_msg;

  switch(d_usrp_state) {

    //---------------------------- INIT ------------------------------------//
    // In the INIT state, there should be no messages across the ports. 
    case INIT:
      error_msg = "no messages should be passed during the INIT state:"; 
      goto unhandled;

    //-------------------------- OPENING USRP -------------------------------//
    // In this state we expect a response from usrp_server over the CS channel
    // as to whether or not the opening of the USRP was successful.  If so, we
    // switch states to allocating the channels for use.
    case OPENING_USRP:

      if(pmt_eq(event, s_response_open)     // Response to a USRP open
          && pmt_eq(d_us_cs->port_symbol(), port_id)) {

        status = pmt_nth(1, data);          // PMT_T or PMT_F

        if(pmt_eq(status, PMT_T)) {         // on success, allocate channels!
          allocate_channels();
          return;
        } else {
          error_msg = "failed to open usrp:";
          goto bail;
        }
      }

      goto unhandled;   // all other messages not handled in this state

    //------------------------ ALLOCATING CHANNELS --------------------------//
    // When allocating channels, we need to wait for 2 responses from USRP
    // server: one for TX and one for RX.  Both are initialized to NIL so we
    // know to continue to the next state once both are set.
    case ALLOCATING_CHANNELS:

      //-------------- TX ALLOCATION RESPONSE ------------------//
      if(pmt_eq(event, s_response_allocate_channel)
          && pmt_eq(d_us_tx->port_symbol(), port_id)) 
      {
        status = pmt_nth(1, data);
        
        if(pmt_eq(status, PMT_T)) {   // extract channel on success
          d_us_tx_chan = pmt_nth(2, data);

          if(verbose)
            std::cout << "[MAC] Received TX allocation"
                      << " on channel " << d_us_tx_chan << std::endl;

          // If the RX has also been allocated already, we can continue
          if(!pmt_eqv(d_us_rx_chan, PMT_NIL)) {
            d_usrp_state=IDLE;
            usrp_initialized();
          }

          return;
        }
        else {  // TX allocation failed
          error_msg = "failed to allocate TX channel:";
          goto bail;
        }
      }
      
      //-------------- RX ALLOCATION RESPONSE ----------------//
      if(pmt_eq(event, s_response_allocate_channel)
          && pmt_eq(d_us_rx->port_symbol(), port_id)) 
      {
        status = pmt_nth(1, data);
        
        if(pmt_eq(status, PMT_T)) {
          
          d_us_rx_chan = pmt_nth(2, data);

          if(verbose)
            std::cout << "[MAC] Received RX allocation"
                      << " on channel " << d_us_rx_chan << std::endl;

          // If the TX has also been allocated already, we can continue
          if(!pmt_eqv(d_us_tx_chan, PMT_NIL)) {
            d_usrp_state=IDLE;
            usrp_initialized();
          }

          return;
        }
        else {  // RX allocation failed
          error_msg = "failed to allocate RX channel:";
          goto bail;
        }
      }

      goto unhandled;

    //------------------------------ IDLE -----------------------------------//
    case IDLE:
      goto unhandled;
    
    //------------------------ CLOSING CHANNELS -----------------------------//
    case CLOSING_CHANNELS:

      if (pmt_eq(event, s_response_deallocate_channel)
          && pmt_eq(d_us_tx->port_symbol(), port_id))
      {
        status = pmt_nth(1, data);

        if(pmt_eq(status, PMT_T)) {
          d_us_tx_chan = PMT_NIL;

          if(verbose)
            std::cout << "[MAC] Received TX deallocation\n";

          // If the RX is also deallocated, we can close the USRP
          if(pmt_eq(d_us_rx_chan, PMT_NIL)) 
            close_usrp();

          return;

        } else {

          error_msg = "failed to deallocate TX channel:";
          goto bail;

        }
      }

      if (pmt_eq(event, s_response_deallocate_channel)
          && pmt_eq(d_us_rx->port_symbol(), port_id))
      {
        status = pmt_nth(1, data);

        // If successful, set the port to NIL
        if(pmt_eq(status, PMT_T)) {
          d_us_rx_chan = PMT_NIL;

          if(verbose)
            std::cout << "[MAC] Received RX deallocation\n";

          // If the TX is also deallocated, we can close the USRP
          if(pmt_eq(d_us_tx_chan, PMT_NIL)) 
            close_usrp();

          return;

        } else {
          
          error_msg = "failed to deallocate RX channel:";
          goto bail;

        }
      }

      goto unhandled;

    //-------------------------- CLOSING USRP -------------------------------//
    case CLOSING_USRP:
      goto unhandled;
  }
 
 // An error occured, print it, and shutdown all m-blocks
 bail:
  std::cerr << error_msg << data
      	    << "status = " << status << std::endl;
  shutdown_all(PMT_F);
  return;

 // Received an unhandled message for a specific state
 unhandled:
  if(0 && verbose && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[MAC] unhandled msg: " << msg
              << "in state "<< d_usrp_state << std::endl;
}

void mac::initialize_usrp(pmt_t usrp_ref)
{

  if(verbose)
    std::cout << "[MAC] Initializing USRP\n";

  // The initialization parameters are passed to usrp_server via a PMT
  // dictionary.
  pmt_t usrp_dict = pmt_make_dict();

  // Specify the RBF to use
  pmt_dict_set(usrp_dict,
               pmt_intern("rbf"),
               pmt_intern("local_rssi5.rbf"));

  pmt_dict_set(usrp_dict,
               pmt_intern("interp-tx"),
               pmt_from_long(128));

  pmt_dict_set(usrp_dict,
               pmt_intern("decim-rx"),
               pmt_from_long(64));

  pmt_dict_set(usrp_dict,
               pmt_intern("fake-usrp"),
               PMT_F);
  
  // Center frequency
  pmt_dict_set(usrp_dict,
               pmt_intern("rf-freq"),
               pmt_from_long((long)10e6));

  // FIXME: RFX2400 hack
  pmt_dict_set(usrp_dict,
               pmt_intern("usrp-tx-reference"),
               pmt_nth(0,usrp_ref));
  pmt_dict_set(usrp_dict,
               pmt_intern("usrp-rx-reference"),
               pmt_nth(1,usrp_ref));

  // Default is to use USRP considered '0' (incase of multiple)
  d_which_usrp = pmt_from_long(0);
  
  define_component("USRP-SERVER", "usrp_server", usrp_dict);
  
  connect("self", "us-tx0", "USRP-SERVER", "tx0");
  connect("self", "us-rx0", "USRP-SERVER", "rx0");
  connect("self", "us-cs", "USRP-SERVER", "cs");

  // Finally, enter the OPENING_USRP state by sending a request to open the
  // USRP.
  open_usrp();
}

void mac::usrp_initialized()
{

}

// The following sends a command to open the USRP, which will upload the
// specified RBF when creating the instance of the USRP server and set all other
// relevant parameters.
void mac::open_usrp()
{
  d_usrp_state = OPENING_USRP;

  d_us_cs->send(s_cmd_open, pmt_list2(PMT_NIL, d_which_usrp));
  
  if(verbose)
    std::cout << "[MAC] Opening USRP " 
              << d_which_usrp << std::endl;
}

// RX and TX channels must be allocated so that the USRP server can
// properly share bandwidth across multiple USRPs.  No commands will be
// successful to the USRP through the USRP server on the TX or RX channels until
// a bandwidth allocation has been received.
void mac::allocate_channels()
{
  d_usrp_state = ALLOCATING_CHANNELS;
  
  if(verbose)
    std::cout << "[MAC] Sending channel allocation requests\n";

  long capacity = (long) 16e6;
  d_us_tx->send(s_cmd_allocate_channel, pmt_list2(PMT_T, pmt_from_long(capacity)));
  d_us_rx->send(s_cmd_allocate_channel, pmt_list2(PMT_T, pmt_from_long(capacity)));

}

// Before sending the close to the USRP we wait a couple seconds to let any data
// through the USB exit, else a bug in the driver will kick an error and cause
// an abnormal termination.
void mac::close_usrp()
{
  d_usrp_state = CLOSING_USRP;

  sleep(2);

  d_us_cs->send(s_cmd_close, pmt_list1(PMT_NIL));
}

// Before closing the USRP connection, we deallocate our channels so that the
// capacity can be reused.
void mac::close_channels()
{
  d_usrp_state = CLOSING_CHANNELS;

  d_us_tx->send(s_cmd_deallocate_channel, pmt_list2(PMT_NIL, d_us_tx_chan));
  d_us_rx->send(s_cmd_deallocate_channel, pmt_list2(PMT_NIL, d_us_rx_chan));

  if(verbose)
    std::cout << "[MAC] Closing channels...\n";
}

// Handle an incoming command to start receiving
void mac::enable_rx()
{
  // If we are already receiving, dont do anything
  if(d_rx_enabled) 
    return;

  d_us_rx->send(s_cmd_start_recv_raw_samples,
             pmt_list2(PMT_F,
                       d_us_rx_chan));

  d_rx_enabled = true;
  
  if(verbose)
    std::cout << "[MAC] RX is enabled\n";
}

// Handle an incoming command to stop receiving
void mac::disable_rx()
{
  // If the RX is already disabled, don't do anything
  if(!d_rx_enabled) 
    return;

  d_us_rx->send(s_cmd_stop_recv_raw_samples,
              pmt_list2(PMT_F,
                        d_us_rx_chan));
                        
  d_rx_enabled = false;

  if(verbose)
    std::cout << "[MAC] RX is disabled\n";
}

REGISTER_MBLOCK_CLASS(mac);

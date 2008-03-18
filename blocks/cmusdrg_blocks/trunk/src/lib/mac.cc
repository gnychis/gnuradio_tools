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

static bool verbose = false;

mac::mac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(rt, instance_name, user_arg),
    d_usrp_state(OPENING_USRP),
    d_us_rx_chan(PMT_NIL), d_us_tx_chan(PMT_NIL),
    d_usrp_decim(64), d_usrp_interp(128)
{
  define_usrp_ports();    // Initialize the ports to connect to the USRP

  pmt_t usrp_references = pmt_nth(0, user_arg);
  initialize_usrp(usrp_references);
}

mac::~mac()
{
}

void mac::define_usrp_ports()
{
  // Ports we use to connect to usrp_server, which handles the USRP
  d_us_tx = define_port("us-tx0", "usrp-tx", false, mb_port::INTERNAL);
  d_us_rx = define_port("us-rx0", "usrp-rx", false, mb_port::INTERNAL);
  d_us_cs = define_port("us-cs", "usrp-server-cs", false, mb_port::INTERNAL);
}

// This is the entrance point of all messages to and from the MAC.  This base
// class takes care of intercepting the low-level USRP setup messages.  When the
// USRP is connected, all of the messages will be forwarded to the virtual
// user-overrided method which MAC's implement.
void mac::handle_message(mb_message_sptr msg)
{
  if(d_usrp_state==CONNECTED)
    handle_mac_message(msg);
  else
    handle_usrp_message(msg);
}

// User implementation will override this method to handle messages to the MAC.
void mac::handle_mac_message(mb_message_sptr msg)
{
}

// All incoming messages to the MAC m-block when the USRP is not connected are
// passed to this method to take care of the connection setup and teardown
// process for the user.
void mac::handle_usrp_message(mb_message_sptr msg)
{
  std::string error_msg;
  pmt_t event = msg->signal();      // Message type (signal name)
  pmt_t data = msg->data();         // Data from the message
  pmt_t port_id = msg->port_id();   // The port the message arrived on

  // All messages related to the USRP connection stage carry a status that tells
  // us if the command was successful or not, like allocating a TX channel.
  pmt_t status = pmt_nth(1, data);
  bool success;
  if(pmt_eq(status, PMT_T))
    success=true;
  else
    success=false;

  switch(d_usrp_state) {

    //-------------------------- OPENING USRP -------------------------------//
    // In this state we expect a response from usrp_server over the CS channel
    // as to whether or not the opening of the USRP was successful.  If so, we
    // switch states to allocating the channels for use.
    case OPENING_USRP:

      //---- Port: USRP CS -------------- State: OPENING_USRP ---------------//
      if(pmt_eq(port_id, d_us_cs->port_symbol())) {

        if(pmt_eq(event, s_response_open)) {      // Response to an 'open' cmd
          open_usrp_response(data, success);      // Handle it
        }
        return;
      }
      goto unhandled; 

    //------------------------ ALLOCATING CHANNELS --------------------------//
    // When allocating channels, we need to wait for 2 responses from USRP
    // server: one for TX and one for RX.  Both are initialized to NIL so we
    // know to continue to the next state once both are set.
    case ALLOCATING_CHANNELS:

      //---- Port: USRP TX -------------- State: ALLOCATING_CHANNELS --------//
      if(pmt_eq(port_id, d_us_tx->port_symbol())) {
        
        if(pmt_eq(event, s_response_allocate_channel)) {
          allocate_channels_response(data, TX_CHANNEL, success);
        }
        return;
      }

      //---- Port: USRP RX -------------- State: ALLOCATING_CHANNELS --------//
      if(pmt_eq(port_id, d_us_rx->port_symbol())) {

        if(pmt_eq(event, s_response_allocate_channel)) {
          allocate_channels_response(data, RX_CHANNEL, success);
        }
        return;
      }
      goto unhandled;

    //------------------------- CONNECTED -----------------------------------//
    // We should never get any messages in this state due to handle_message()
    case CONNECTED:
      goto unhandled;
    
    //------------------------ CLOSING CHANNELS -----------------------------//
    // Here we wait for our channels to be deallocated before we close the USRP.
    // We wait for a deallocation on both ports for continuing.
    case DEALLOCATING_CHANNELS:
      
      //---- Port: USRP TX -------------- State: DEALLOCATING_CHANNELS -----------//
      if(pmt_eq(port_id, d_us_tx->port_symbol())) {
        
        if(pmt_eq(event, s_response_allocate_channel)) {
          deallocate_channels_response(data, TX_CHANNEL, success);
        }
        return;
      }

      //---- Port: USRP RX -------------- State: DEALLOCATING_CHANNELS --------//
      if(pmt_eq(port_id, d_us_rx->port_symbol())) {

        if(pmt_eq(event, s_response_allocate_channel)) {
          deallocate_channels_response(data, RX_CHANNEL, success);
        }
        return;
      }
      goto unhandled;

    //-------------------------- CLOSING USRP -------------------------------//
    case CLOSING_USRP:
      goto unhandled;
  }
 
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

  // Specify important parameters like the RBF and frequency
  pmt_dict_set(usrp_dict, pmt_intern("rbf"), pmt_intern("local_rssi5.rbf"));
  pmt_dict_set(usrp_dict, pmt_intern("rf-freq"), pmt_from_long((long)10e6));
  pmt_dict_set(usrp_dict, pmt_intern("interp-tx"), pmt_from_long(d_usrp_interp));
  pmt_dict_set(usrp_dict, pmt_intern("decim-rx"), pmt_from_long(d_usrp_decim));
  pmt_dict_set(usrp_dict, pmt_intern("fake-usrp"), PMT_F);
  
  // FIXME: RFX2400 hack
  pmt_dict_set(usrp_dict, pmt_intern("usrp-tx-reference"), pmt_nth(0,usrp_ref));
  pmt_dict_set(usrp_dict, pmt_intern("usrp-rx-reference"), pmt_nth(1,usrp_ref));

  // Default is to use USRP considered '0' (incase of multiple)
  d_which_usrp = pmt_from_long(0);
  
  define_component("USRP-SERVER", "usrp_server", usrp_dict);
  
  connect("self", "us-tx0", "USRP-SERVER", "tx0");
  connect("self", "us-rx0", "USRP-SERVER", "rx0");
  connect("self", "us-cs", "USRP-SERVER", "cs");

  // Enter the OPENING_USRP state by sending a request to open the USRP.
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
  d_us_cs->send(s_cmd_open, pmt_list2(PMT_NIL, d_which_usrp));
  
  if(verbose)
    std::cout << "[MAC] Opening USRP " 
              << d_which_usrp << std::endl;
}

// Handle a response to a command for opening the USRP.  If the open was
// unsuccessful we bail and shutdown all m-blocks.  
void mac::open_usrp_response(pmt_t data, bool success)
{
  if(!success) {
    std::cerr << "[MAC] Failed to open USRP\n";
    shutdown_all(PMT_F);    // Quit!
    return;
  }

  allocate_channels();      // Go on to allocate TX and RX channels

  if(verbose)
    std::cout << "[MAC] Successfully opened the USRP\n";
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

// If we were given a TX channel, and we have an RX channel set (allocated),
// then we can continue in to the connected state and invoke the method which
// the user will override for us to notify them that the USRP is connected.
void mac::allocate_channels_response(pmt_t data, channel_type chan, bool success)
{
  if(!success) {
    std::cerr << "[MAC] Failed to allocate channel\n";
    shutdown_all(PMT_F);
    return;
  }

  // Save the channel given to us
  pmt_t allocated_channel = pmt_nth(2, data);
  if(chan==TX_CHANNEL) 
    d_us_tx_chan = allocated_channel;
  else
    d_us_rx_chan = allocated_channel;

  if(verbose)
    std::cout << "[MAC] Received allocation"
              << " on channel " << d_us_tx_chan << std::endl;

  if((chan==TX_CHANNEL && !pmt_eqv(d_us_rx_chan, PMT_NIL)) ||
     (chan==RX_CHANNEL && !pmt_eqv(d_us_tx_chan, PMT_NIL))) {
    d_usrp_state=CONNECTED;
    usrp_initialized();
  } 
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
void mac::deallocate_channels()
{
  d_usrp_state = DEALLOCATING_CHANNELS;

  d_us_tx->send(s_cmd_deallocate_channel, pmt_list2(PMT_NIL, d_us_tx_chan));
  d_us_rx->send(s_cmd_deallocate_channel, pmt_list2(PMT_NIL, d_us_rx_chan));

  if(verbose)
    std::cout << "[MAC] Closing channels...\n";
}

void mac::deallocate_channels_response(pmt_t data, channel_type chan, bool success)
{
  if(!success) {
    std::cerr << "[MAC] Failed to deallocate channel\n";
    shutdown_all(PMT_F);
    return;
  }

  // Reset the deallocate channel to NIL
  if(chan==TX_CHANNEL) 
    d_us_tx_chan = PMT_NIL;
  else
    d_us_rx_chan = PMT_NIL;

  if(verbose)
    std::cout << "[MAC] Received allocation"
              << " on channel " << d_us_tx_chan << std::endl;

  if((chan==TX_CHANNEL && pmt_eqv(d_us_rx_chan, PMT_NIL)) ||
     (chan==RX_CHANNEL && pmt_eqv(d_us_tx_chan, PMT_NIL))) {
    close_usrp();
  } 
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


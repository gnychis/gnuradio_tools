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

#include <gcp.h>

static bool verbose = false;

gcp::gcp(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(rt, instance_name, user_arg),
  d_gcp_state(INIT_GCP),
  d_active_mac(NULL),
  d_usrp_interp(128),
  d_usrp_decim(64)
{
  define_ports();  
  initialize_macs();
  allocate_channels();
}

gcp::~gcp()
{
}

void gcp::define_ports()
{
  // Ports we use to connect to usrp_server, which handles the USRP
  d_us_tx = define_port("us-tx1", "usrp-tx", false, mb_port::INTERNAL);
  d_us_rx = define_port("us-rx1", "usrp-rx", false, mb_port::INTERNAL);
  d_us_cs = define_port("us-cs", "usrp-server-cs", false, mb_port::INTERNAL);
  
  connect("self", "us-tx0", "USRP-SERVER", "tx0");
  connect("self", "us-rx0", "USRP-SERVER", "rx0");
  connect("self", "us-cs", "USRP-SERVER", "cs");

  // Create a small dictionary to pass some information to the PHY
  pmt_t phy_dict = pmt_make_dict();
  pmt_dict_set(phy_dict, pmt_intern("interp-tx"), pmt_from_long(d_usrp_interp));
  pmt_dict_set(phy_dict, pmt_intern("decim-rx"), pmt_from_long(d_usrp_decim));

  // Create and connect a physical layer (GMSK) that is used for control frames
  define_component("GMSK-gcp", "gmsk", phy_dict);
  d_phy = define_port("phy", "gmsk-cs", false, mb_port::INTERNAL);
  connect("self", "phy", "GMSK", "cs0");

  // Create and connect to the switch block
  define_component("SWITCH", "switch", PMT_NIL);
  d_switch = define_port("switch", "gcp-switch-cs", false, mb_port::INTERNAL);
  connect("self", "switch", "SWITCH", "cs0");
}

void gcp::handle_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();      // type of message
  pmt_t data = msg->data();         // the associated data
  pmt_t port_id = msg->port_id();   // the port the msg was received on

  pmt_t invocation;
  pmt_t status;

  switch(d_gcp_state) {

    //-------------------- INIT GCP -----------------------------------//
    // Not expecting any messages in this state
    case INIT_GCP:
      goto unhandled;

    //-------------------- CONN MACS ----------------------------------//
    // In this state, we wait for a response from the switch
    // block that the MACs were connected successfully.
    case CONN_MACS:
      goto unhandled;
    
    //------------------------ ALLOCATING CHANNELS --------------------------//
    // When allocating channels, we need to wait for 2 responses from USRP
    // server: one for TX and one for RX.  Both are initialized to NIL so we
    // know to continue to the next state once both are set.
    case ALLOCATING_CHANNELS:

      //---- Port: USRP TX -------------- State: ALLOCATING_CHANNELS --------//
      if(pmt_eq(port_id, d_us_tx->port_symbol())) {
        
        if(pmt_eq(event, s_response_allocate_channel)) {
        pmt_t status = pmt_nth(1, data);
        bool success;
        if(pmt_eq(status, PMT_T))
          success=true;
        else
          success=false;
          allocate_channels_response(data, TX_CHANNEL, success);
        }
        return;
      }

      //---- Port: USRP RX -------------- State: ALLOCATING_CHANNELS --------//
      if(pmt_eq(port_id, d_us_rx->port_symbol())) {

        if(pmt_eq(event, s_response_allocate_channel)) {
        pmt_t status = pmt_nth(1, data);
        bool success;
        if(pmt_eq(status, PMT_T))
          success=true;
        else
          success=false;
          allocate_channels_response(data, RX_CHANNEL, success);
        }
        return;
      }
      goto unhandled;

    case TRAINING:
      goto unhandled;
    
    //----------------------------- IDLE ------------------------------------//
    case IDLE:

      //---- Port: USRP RX --------------------------------------------------//
      if(pmt_eq(d_us_rx->port_symbol(), port_id)) {

        if(pmt_eq(event, s_response_recv_raw_samples)) {
          d_phy_cs->send(s_cmd_demod, data);         // Demod incoming samples
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
      //---- Port: GMSK CS -------------- State: IDLE -----------------------//
      if(pmt_eq(d_phy_cs->port_symbol(), port_id)) {
        
        if(pmt_eq(event, s_response_mod)) {
          transmit_pkt(data);                         // Data done being mod'ed
          return;
        }
      }
      goto unhandled;

    case SWITCHING:
      goto unhandled;

    default:
      goto unhandled;
  }

  unhandled:
    return;
}

// Function that sends a message to the 'switch' block that connects
// the given list of MACs
void gcp::initialize_macs()
{
  // Change the GCP state
  d_gcp_state = CONN_MACS;

  // Invocation handle unused
  pmt_t invocation = PMT_NIL;

  // List of MACs to connect
  std::vector<std::string> macs;
  macs.push_back("cmac");
  macs.push_back("tmac");
  
  long nmacs = macs.size();

  for(int i=0; i<nmacs; i++) {
    struct macs_t curr_mac;

    curr_mac.name = macs[i];
    curr_mac.pname = curr_mac.name+"-cs";

    define_component(curr_mac.name, curr_mac.name, PMT_NIL);
    curr_mac.port = define_port(curr_mac.name, curr_mac.pname, false, mb_port::INTERNAL);

    d_macs.push_back(curr_mac);

    // Connect to the first MAC
    if(i==0)
      connect_mac(&curr_mac);
  }
}

// Better to think of this method as a switching MAC method, there is no
// disconnect without connecting another MAC, a MAC should be connected at all
// times
void gcp::connect_mac(struct macs_t *mac)
{
  if(d_active_mac==NULL) {
    connect("self", mac->pname, mac->name, "mac-cs");
  } else {
    disconnect_component(d_active_mac->name);
    connect("self", mac->pname, mac->name, "mac-cs");
  }
  d_active_mac=mac;
}

void gcp::incoming_frame(pmt_t data)
{
}

void gcp::allocate_channels()
{
  d_gcp_state = ALLOCATING_CHANNELS;
  
  if(verbose)
    std::cout << "[GCP] Sending channel allocation requests\n";

  long capacity = (long) 16e6;
  d_us_tx->send(s_cmd_allocate_channel, pmt_list2(PMT_T, pmt_from_long(capacity)));
  d_us_rx->send(s_cmd_allocate_channel, pmt_list2(PMT_T, pmt_from_long(capacity)));
}

// If we were given a TX channel, and we have an RX channel set (allocated),
// then we can continue in to the connected state and invoke the method which
// the user will override for us to notify them that the USRP is connected.
void gcp::allocate_channels_response(pmt_t data, channel_type chan, bool success)
{
  if(!success) {
    // If unsuccessful, we try to allocate again with the logic that
    // we might have tried to allocate before mac.cc opens the USRP
    allocate_channels();
    return;
  }

  // Save the channel given to us
  pmt_t allocated_channel = pmt_nth(2, data);
  if(chan==TX_CHANNEL) 
    d_us_tx_chan = allocated_channel;
  else
    d_us_rx_chan = allocated_channel;

  if(verbose)
    std::cout << "[GCP] Received allocation"
              << " on channel " << d_us_tx_chan << std::endl;

  if((chan==TX_CHANNEL && !pmt_eqv(d_us_rx_chan, PMT_NIL)) ||
     (chan==RX_CHANNEL && !pmt_eqv(d_us_tx_chan, PMT_NIL))) {
    d_gcp_state=IDLE;

    if(verbose)
      std::cout << "[GCP] Received full channel allocation, going idle\n";
    enable_rx();
  } 
}     

// Handle an incoming command to start receiving
void gcp::enable_rx()
{
  d_us_rx->send(s_cmd_start_recv_raw_samples,
             pmt_list2(PMT_F,
                       d_us_rx_chan));

  if(verbose)
    std::cout << "[GCP] RX is enabled\n";
}

// Entrance of new incoming data
void gcp::incoming_data(pmt_t data)
{
  pmt_t bits = pmt_nth(0, data);
  pmt_t demod_properties = pmt_nth(1, data);
  std::vector<unsigned char> bit_data = boost::any_cast<std::vector<unsigned char> >(pmt_any_ref(bits));

  framer(bit_data, demod_properties);
}

// Handles the transmission of a pkt from the application.  The invocation
// handle is passed on but a response is not given back to the application until
// the response is passed from usrp_server.  This ensures that the MAC passes
// back the success or failure. 
void gcp::transmit_pkt(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t samples = pmt_nth(1, data);
  pmt_t pkt_properties = pmt_nth(2, data);
  pmt_t timestamp;

  pmt_t us_tx_properties = pmt_make_dict();

  if(pmt_is_dict(pkt_properties)) {
    if(pmt_t pkt_cs = pmt_dict_ref(pkt_properties,
                                   pmt_intern("carrier-sense"),
                                   PMT_NIL)) {
      if(pmt_eqv(pkt_cs, PMT_T))                    // carrier sense the packet?
        pmt_dict_set(us_tx_properties,              // set it in our dictionary
                     pmt_intern("carrier-sense"),   // the 'hash'
                     PMT_T);                        // true, but assumed false if no
    }

    if(timestamp = pmt_dict_ref(pkt_properties,
                                pmt_intern("timestamp"),
                                PMT_NIL)) {
      if(pmt_eqv(timestamp, PMT_NIL)) {
        std::cout << "[MAC] Error: MAC did not specify timestamp with transmission\n";
        shutdown_all(PMT_F);
      }
    }
  } else {
    std::cout << "[MAC] Invalid packet properties on transmit frame\n";
    shutdown_all(PMT_F);
  }

  pmt_t pdata = pmt_list5(invocation_handle,    // Invocation handle is passed back.
		                      d_us_tx_chan,         // Destined for our TX channel.
		                      samples,              // The modulated data (samples).
                          timestamp,            // The time to send the packet.
                          us_tx_properties);    // Our per-packet properties.

  d_us_tx->send(s_cmd_xmit_raw_frame, pdata);   // Finally, send!

  if(verbose)
    std::cout << "[CMAC] Transmitted packet\n";
}

void gcp::build_and_send_beacon()
{
  size_t ignore;
  char data;
  long n_bytes=1;   // Negligable payload
  
  // Make the PMT data, get a writable pointer to it, then copy our data in
  pmt_t uvec = pmt_make_u8vector(n_bytes, 0);
  char *vdata = (char *) pmt_u8vector_writable_elements(uvec, ignore);
  memcpy(vdata, &data, n_bytes);

  // Per packet properties
  pmt_t tx_properties = pmt_make_dict();
  pmt_dict_set(tx_properties, pmt_intern("power"), pmt_from_long(128));  // it's an ACK!

  pmt_t pdata = pmt_list4(PMT_NIL,                        // No invocation.
                          pmt_from_long(0xffff),          // To broadcast.
                          uvec,                           // With data.
                          tx_properties);                 // It's an ACK!

  build_frame(pdata);
  
  if(verbose)
    std::cout << "[GCP] Transmitted beacon\n";
}

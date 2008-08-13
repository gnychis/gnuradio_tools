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
  d_gcp_state(INIT_GCP)
{
  define_ports();  
  connect_macs();
}

gcp::~gcp()
{
}

void gcp::define_ports()
{
  // Create a small dictionary to pass some information to the PHY
  pmt_t phy_dict = pmt_make_dict();
  pmt_dict_set(phy_dict, pmt_intern("interp-tx"), pmt_from_long(d_usrp_interp));
  pmt_dict_set(phy_dict, pmt_intern("decim-rx"), pmt_from_long(d_usrp_decim));

  // Create and connect a physical layer (GMSK) that is used for control frames
  define_component("GMSK", "gmsk", phy_dict);
  d_phy = define_port("phy", "gmsk-cs", false, mb_port::INTERNAL);
  connect("self", "phy", "GMSK", "cs0");

  // Create and connect to the switch block
  define_component("SWITCH", "switch", PMT_NIL);
  d_switch = define_port("switch", "switch-cs", false, mb_port::INTERNAL);
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
    INIT_GCP:
      goto unhandled;

    //-------------------- CONN MACS ----------------------------------//
    // In this state, we wait for a response from the switch
    // block that the MACs were connected successfully.
    CONN_MACS:

      //---- Port: SWITCH ----------- State: CONN_MACS -------//
      if(pmt_eq(port_id, d_switch->port_symbol())) {
        
        if(pmt_eq(event, s_response_connect_macs)) {
          invocation = pmt_nth(0, data); 
          status = pmt_nth(1, data); 

          if(pmt_eqv(status, PMT_F)) {
            std::cerr << "[GCP] Error connecting MACs";
            shutdown_all(PMT_F);
          }

          // Switch states
        }
      }
      goto unhandled;

    TRAINING:
      goto unhandled;
    
    IDLE:
      goto unhandled;

    SWITCHING:
      goto unhandled;

    default:
      goto unhandled;
  }

  unhandled:
}

// Function that sends a message to the 'switch' block that connects
// the given list of MACs
void gcp::connect_macs()
{
  // Change the GCP state
  d_gcp_state = CONN_MACS;

  // Invocation handle unused
  pmt_t invocation = PMT_NIL;

  // List of MACs to connect
  pmt_t mac_list = pmt_list2(pmt_intern("cmac"), 
                             pmt_intern("tmac"));

  // Send the message to connect the MACs
  d_switch->send(s_cmd_connect_macs, pmt_list2(invocation, mac_list));
}

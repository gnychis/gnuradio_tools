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
  d_usrp_interp(64),
  d_usrp_decim(32)
{
  define_ports();  
  initialize_macs();
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
    INIT_GCP:
      goto unhandled;

    //-------------------- CONN MACS ----------------------------------//
    // In this state, we wait for a response from the switch
    // block that the MACs were connected successfully.
    CONN_MACS:
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

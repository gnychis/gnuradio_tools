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

#include <gcp_switch.h>

static bool verbose = false;

gcp_switch::gcp_switch(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(rt, instance_name, user_arg),
  d_gcp_switch_state(INIT_GCP_SWITCH)
{
  define_ports();  
}

gcp_switch::~gcp_switch()
{
}

void gcp_switch::define_ports()
{
  d_switch = define_port("cs0", "gcp-switch-cs", true, mb_port::EXTERNAL);
}

void gcp_switch::handle_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();      // type of message
  pmt_t data = msg->data();         // the associated data
  pmt_t port_id = msg->port_id();   // the port the msg was received on

  pmt_t invocation;
  pmt_t status;

  switch(d_gcp_switch_state) {

    //-------------------- INIT GCP SWITCH ----------------------------//
    // Not expecting any messages in this state
    INIT_GCP_SWITCH:
      goto unhandled;

    //-------------------- IDLE ---------------------------------------//
    // General state for handling incoming messages.
    IDLE:

      //---- Port: SWITCH ----------- State: IDLE ------------//
      if(pmt_eq(port_id, d_switch->port_symbol())) {
        
        if(pmt_eq(event, s_cmd_connect_macs)) {
          connect_macs(data);
          return;
        }
      }
      goto unhandled;
  }

  unhandled:
    return;
}

// Function that handles incoming message to connect MACs
void gcp_switch::connect_macs(pmt_t data)
{
  pmt_t invocation = pmt_nth(0, data);
  pmt_t macs = pmt_nth(1, data);
  long nmacs = pmt_length(macs);

  for(int i=0; i<nmacs; i++) {
    struct macs_t curr_mac;
    curr_mac.name = pmt_nth(i, macs);

    std::string sname = pmt_symbol_to_string(curr_mac.name);
    std::string sport = sname+"-cs";

    define_component(sname, sname, PMT_NIL);
    curr_mac.port = define_port(sname, sport, false, mb_port::INTERNAL);
    connect("self", sname, sname, "switcher");

    d_macs.push_back(curr_mac);
  }

}

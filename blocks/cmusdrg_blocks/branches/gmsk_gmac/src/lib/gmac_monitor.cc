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

#include <mb_mblock.h>
#include <mb_runtime.h>
#include <mb_protocol_class.h>
#include <mb_exception.h>
#include <mb_msg_queue.h>
#include <mb_message.h>
#include <mb_msg_accepter.h>
#include <mb_class_registry.h>
#include <pmt.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>

#include <gmsk.h>
#include <gmac.h>
#include <gmac_symbols.h>

static bool verbose = true;

class gmac_monitor : public mb_mblock
{
  mb_port_sptr 	d_tx;
  mb_port_sptr  d_rx;
  mb_port_sptr 	d_cs;
  pmt_t		d_tx_chan;	// returned tx channel handle

  enum state_t {
    INIT,
    DATA_WAIT,
  };

  state_t	d_state;

  long d_tframes;

 public:
  gmac_monitor(mb_runtime *runtime, const std::string &instance_name, pmt_t user_arg);
  ~gmac_monitor();
  void handle_message(mb_message_sptr msg);

 protected:
  void open_usrp();
  void close_usrp();
  void allocate_channel();
  void send_packets();
  void enter_data_wait();
  void handle_response_rx_pkt(pmt_t data);
  void enter_closing_channel();
};

gmac_monitor::gmac_monitor(mb_runtime *runtime, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(runtime, instance_name, user_arg),
    d_state(INIT),
    d_tframes(0)
{ 

  pmt_t args = pmt_nth(1, user_arg);

  define_component("GMAC", "gmac", pmt_nth(0,user_arg)); // FIXME: RFX2400 Hack
  d_tx = define_port("tx0", "gmac-tx", false, mb_port::INTERNAL);
  d_rx = define_port("rx0", "gmac-rx", false, mb_port::INTERNAL);
  d_cs = define_port("cs", "gmac-cs", false, mb_port::INTERNAL);

  connect("self", "tx0", "GMAC", "tx0");
  connect("self", "rx0", "GMAC", "rx0");
  connect("self", "cs", "GMAC", "cs");

  std::cout << "[GMAC_MONITOR] Initialized ...\n";

}

gmac_monitor::~gmac_monitor()
{
}

void
gmac_monitor::handle_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();
  pmt_t data = msg->data();
  pmt_t port_id = msg->port_id();

  pmt_t handle = PMT_F;
  pmt_t status = PMT_F;
  pmt_t dict = PMT_NIL;
  std::string error_msg;
  
  // Dispatch based on state
  switch(d_state) {

    //------------------------------ INIT ---------------------------------//
    // When GMAC is done initializing, it will send a response
    case INIT:
      
      if(pmt_eq(event, s_response_gmac_initialized)) {
        handle = pmt_nth(0, data);
        status = pmt_nth(1, data);

        if(pmt_eq(status, PMT_T)) {
          enter_data_wait();
          return;
        }
        else {
          error_msg = "error initializing gmac:";
          goto bail;
        }
      }
      goto unhandled;

    //-------------------------- DATA_WAIT ----------------------------//
    // In the transmit state we count the number of underruns received and
    // ballpark the number with an expected count (something >1 for starters)
    case DATA_WAIT:
      
      // Check that the transmits are OK
      if (pmt_eq(event, s_response_rx_pkt)){
        handle_response_rx_pkt(data);
        return;
      }
      goto unhandled;

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
  if(verbose && 0 && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[GMAC_RX_FILE] unhandled msg: " << msg
              << "in state "<< d_state << std::endl;
}

// Wait until we get incoming data...
void
gmac_monitor::enter_data_wait()
{
  d_state = DATA_WAIT;
}

void
gmac_monitor::handle_response_rx_pkt(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t payload = pmt_nth(1, data);
  pmt_t pkt_properties = pmt_nth(2, data);

  long lsrc=0, ldst=0;
  bool bcrc=false;

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
        bcrc = true;
      else
        bcrc = false;
    }
  }

  size_t nbytes;
  (char *)pmt_u8vector_writeable_elements(payload, nbytes);

  std::cout << "[GMAC_MONITOR] Detected frame " << d_tframes
            << "\n   SRC:  " << lsrc
            << "\n   DST:  " << ldst
            << "\n   ACK:  " << bcrc
            << "\n   SIZE: " << nbytes
            << std::endl;

  d_tframes++;
}

REGISTER_MBLOCK_CLASS(gmac_monitor);

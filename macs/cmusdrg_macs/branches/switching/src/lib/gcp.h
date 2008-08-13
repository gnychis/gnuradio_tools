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

#ifndef INCLUDED_GCP_H
#define INCLUDED_GCP_H

// Common Includes
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
#include <ui_nco.h>

// External symbols
#include <symbols_usrp_server_cs.h>
#include <symbols_usrp_channel.h>
#include <symbols_usrp_low_level_cs.h>
#include <symbols_usrp_tx.h>
#include <symbols_usrp_rx.h>

class gcp;

class gcp : public mb_mblock
{

 protected:

  // List of states for GCP
  enum gcp_state_t {
    INIT_GCP,
    CONN_MACS,
    TRAINING,
    IDLE,
    SWITCHING,
  };
  gcp_state_t d_gcp_state;
  
  // Used to keep MAC name/port pairs
  struct macs_t {
    pmt_t name;
    mb_port_sptr port;

    macs_t() {
      name = PMT_NIL;
      //port = PMT_NIL;
    }
  };
  
  // GCP Ports
  mb_port_sptr d_phy;
  mb_port_sptr d_switch;
  mb_port_sptr d_control;
  std::vector<struct macs_t> d_macs;
  struct macs_t *d_active_mac;

  // USRP parameters
  long d_usrp_interp;
  long d_usrp_decim;

 public:
  gcp(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~gcp();
  void handle_message(mb_message_sptr msg);

 private:
  void define_ports();
  void initialize_macs();
};

#endif


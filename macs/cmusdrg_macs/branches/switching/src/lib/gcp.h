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

#include <gmsk_symbols.h>
#include <gcp_framer.h>

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
  
  enum state_t {
    SYNC_SEARCH,
    WAIT_HEADER,
    HAVE_HEADER,
    WAIT_PAYLOAD,
    HAVE_PAYLOAD
  };
  state_t	d_framer_state;
  
  // Used to keep MAC name/port pairs
  struct macs_t {
    std::string name;
    std::string pname;
    mb_port_sptr port;

    macs_t() {
      name = "";
      pname = "";
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
  
  // Local control address
  long d_local_address;
  bool d_carrier_sense;
  pmt_t d_last_frame;
  
  // Framer
  d_frame_hdr_t d_frame_hdr;
  d_frame_hdr_t d_cframe_hdr;
  std::vector<unsigned char> d_hdr_bits;
  std::vector<unsigned char> d_payload_bits;
  unsigned long d_frame_timestamp;
  unsigned long d_seq_num;

  mb_port_sptr d_phy_cs;

 public:
  gcp(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~gcp();
  void handle_message(mb_message_sptr msg);
  static int max_frame_size() {
    return(MAX_FRAME_SIZE);
  }
  static int max_frame_payload() {
    return(MAX_FRAME_SIZE-sizeof(d_frame_hdr_t));
  }

 private:
  void define_ports();
  void initialize_macs();
  void connect_mac(struct macs_t *mac);
  
  // Framer
  void framer(const std::vector<unsigned char> input, pmt_t demod_properties);
  void framer_calculate_timestamp(unsigned long timestamp, int bit, int nbits, long sps, long bps);
  void framer_found_sync();
  void framer_new_header_bit(unsigned char bit);
  void framer_new_payload_bit(unsigned char bit);
  void framer_have_header();
  void framer_have_payload();
  void framer_have_frame(pmt_t uvec);
  void build_frame(pmt_t data);
  void incoming_frame(pmt_t data);
};

#endif


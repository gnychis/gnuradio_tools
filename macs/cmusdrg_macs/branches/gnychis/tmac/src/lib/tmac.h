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

#ifndef INCLUDED_TMAC_H
#define INCLUDED_TMAC_H

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

#include <symbols_usrp_server_cs.h>
#include <symbols_usrp_channel.h>
#include <symbols_usrp_low_level_cs.h>
#include <symbols_usrp_tx.h>
#include <symbols_usrp_rx.h>

#include <tmac_symbols.h>
#include <gmsk_symbols.h>
#include <tmac_framer.h>
#include <mac_symbols.h>

#include <mac.h>

class tmac;

class tmac : public mac
{

  enum tmac_state_t {
    INIT_TMAC,
    WAIT_SYNC,
    IDLE,
  };
  tmac_state_t	d_state;
  
  enum state_t {
    SYNC_SEARCH,
    WAIT_HEADER,
    HAVE_HEADER,
    WAIT_PAYLOAD,
    HAVE_PAYLOAD
  };
  state_t	d_framer_state;

  // Ports used for applications to connect to this block
  mb_port_sptr		  d_tx, d_rx, d_cs;

  // TDMA state
  bool d_base_station;
  unsigned long d_total_nodes;
  unsigned long d_last_sync;
  unsigned long d_slot_time;
  unsigned long d_guard_time;
  unsigned long d_round_time;
  unsigned long d_local_slot_offset;
  unsigned long d_next_tx_time;
  unsigned long d_clock_ticks_per_bit;
  pmt_t d_last_frame;

  // Local user address
  long d_local_address;
  
  // Framer
  d_frame_hdr_t d_frame_hdr;
  d_frame_hdr_t d_cframe_hdr;
  std::vector<unsigned char> d_hdr_bits;
  std::vector<unsigned char> d_payload_bits;
  unsigned long d_frame_timestamp;
  
  pmt_t mac_properties;
  
 protected:
  void handle_mac_message(mb_message_sptr msg);   // overriding MAC method
  void usrp_initialized();                        // overriding MAC method

 public:
  tmac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~tmac();
  static int max_frame_size() {
    return(MAX_FRAME_SIZE);
  }
  static int max_frame_payload() {
    return(MAX_FRAME_SIZE-sizeof(d_frame_hdr_t));
  }

 private:
  // TMAC initialization
  void define_mac_ports();
  void initialize_tmac();

  // Crucial TDMA methods
  void initialize_base_station();
  void initialize_node();
  void transmit_pkt(pmt_t data);
  void packet_transmitted(pmt_t data);
  void incoming_data(pmt_t data);
  void incoming_frame(pmt_t data);

  // Synchronization related
  void calculate_parameters();
  void transmit_sync();
  void incoming_sync(pmt_t data);
  
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
};

#endif // INCLUDED_TMAC_H

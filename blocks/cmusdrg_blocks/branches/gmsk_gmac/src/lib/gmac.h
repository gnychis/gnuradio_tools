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

#ifndef INCLUDED_GMAC_H
#define INCLUDED_GMAC_H

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

#include <gmac_symbols.h>
#include <gmsk_symbols.h>

#include <mac.h>

class gmac;

class gmac : public mac
{

  enum gmac_state_t {
    INIT_GMAC,
    ACK_WAIT,
    SEND_ACK,
    IDLE,
  };
  gmac_state_t	d_state;

  // Ports used for applications to connect to this block
  mb_port_sptr		  d_tx, d_rx, d_cs;

  // Ports to connect to gmsk (us)
  mb_port_sptr      d_gmsk_cs;

  pmt_t d_ack_timeout;
  pmt_t d_last_frame;
  long d_last_frame_dst;

  bool d_carrier_sense;
  long d_cs_thresh;
  long d_cs_deadline;

  // Local user address
  long d_local_address;
  
 protected:
  void handle_mac_message(mb_message_sptr msg);   // overriding MAC method
  void usrp_initialized();                        // overriding MAC method

 public:
  gmac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~gmac();

 private:
  // GMAC initialization
  void define_mac_ports();
  void initialize_gmac();
  void set_address(pmt_t data);

  // Crucial CSMA methods
  void transmit_pkt(pmt_t data);
  void packet_transmitted(pmt_t data);
  void incoming_frame(pmt_t data);
  void build_and_send_ack(long dst);
  void handle_ack(long src, long dst);
  
  // Carrier sense functionality
  void disable_carrier_sense(pmt_t data);
  void enable_carrier_sense(pmt_t data);
  void set_carrier_sense(bool toggle, long threshold, long deadline, pmt_t invocation);
  void set_carrier_sense_deadline(pmt_t data);
  void set_carrier_sense_threshold(pmt_t data);
  bool carrier_sense_pkt(pmt_t pkt_properties);
 
};

#endif // INCLUDED_GMAC_H

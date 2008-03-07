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

#ifndef INCLUDED_MAC_H
#define INCLUDED_MAC_H

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

class mac;

class mac : public mb_mblock
{

 protected:
  // The state is used to determine how to handle incoming messages and of
  // course, the state of the MAC protocol.
  enum usrp_state_t {
    INIT,
    OPENING_USRP,
    ALLOCATING_CHANNELS,
    IDLE,
    CLOSING_CHANNELS,
    CLOSING_USRP,
  };
  usrp_state_t	d_usrp_state;

  // Ports to connect to usrp_server (us)
  mb_port_sptr      d_us_tx, d_us_rx, d_us_cs;
  
  // The channel numbers assigned for use
  pmt_t d_us_rx_chan, d_us_tx_chan;

  pmt_t d_which_usrp;
  
  bool d_rx_enabled;

  // FPGA regs
  enum FPGA_REGISTERS {
    REG_CS_THRESH = 51,
    REG_CS_DEADLINE = 52
  };
  
  virtual void handle_mac_message(mb_message_sptr msg);   // MAC overridable
  
 public:
  mac(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~mac();

  // Top level message dispatcher to separate the USRP init and teardown so that
  // every MAC does not have to keep re-writing this code.
  void handle_message(mb_message_sptr msg);

 private:
  void define_usrp_ports();
  void initialize_usrp(pmt_t usrp_ref);
  void allocate_channels();
  void enable_rx();
  void disable_rx();
  void enter_receiving();
  void exit_receiving();
  void close_channels();
  void open_usrp();
  void close_usrp();
  void handle_usrp_message(mb_message_sptr msg);
};

#endif // INCLUDED_MAC_H


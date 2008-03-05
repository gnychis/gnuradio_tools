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
#include <mb_runtime_nop.h>		// QA only
#include <mb_protocol_class.h>
#include <mb_exception.h>
#include <mb_msg_queue.h>
#include <mb_message.h>
#include <mb_mblock_impl.h>
#include <mb_msg_accepter.h>
#include <mb_class_registry.h>
#include <pmt.h>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <fstream>
#include <sys/time.h>

#include <gmsk.h>
#include <gmac.h>
#include <gmac_symbols.h>

static bool verbose = false;

class test_gmac_tx_file : public mb_mblock
{
  mb_port_sptr 	d_tx;
  mb_port_sptr  d_rx;
  mb_port_sptr 	d_cs;
  pmt_t		d_tx_chan;	// returned tx channel handle

  enum state_t {
    INIT,
    TRANSMITTING,
    ACK_WAIT,
  };

  state_t	d_state;
  long		d_nframes_xmitted;
  bool		d_done_sending;

  std::ifstream d_ifile;

  long d_local_addr;
  long d_dst_addr;

  struct timeval d_start, d_end;

 public:
  test_gmac_tx_file(mb_runtime *runtime, const std::string &instance_name, pmt_t user_arg);
  ~test_gmac_tx_file();
  void handle_message(mb_message_sptr msg);

 protected:
  void open_usrp();
  void close_usrp();
  void allocate_channel();
  void send_packets();
  void enter_transmitting();
  void build_and_send_next_frame();
  void handle_xmit_response(pmt_t invocation_handle);
  void handle_response_rx_pkt(pmt_t data);
  void enter_closing_channel();
  void enter_ack_wait();
};

test_gmac_tx_file::test_gmac_tx_file(mb_runtime *runtime, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(runtime, instance_name, user_arg),
    d_state(INIT), 
    d_nframes_xmitted(0),
    d_done_sending(false)
{ 

  pmt_t file = pmt_nth(0, user_arg);
  d_local_addr = pmt_to_long(pmt_nth(1, user_arg));
  d_dst_addr = pmt_to_long(pmt_nth(2, user_arg));
  
  // Open a stream to the input file and ensure it's open
  d_ifile.open(pmt_symbol_to_string(file).c_str(), std::ios::binary|std::ios::in);

  if(!d_ifile.is_open()) {
    std::cout << "Error opening input file\n";
    shutdown_all(PMT_F);
    return;
  }
  
  define_component("GMAC", "gmac", PMT_NIL);
  d_tx = define_port("tx0", "gmac-tx", false, mb_port::INTERNAL);
  d_rx = define_port("rx0", "gmac-rx", false, mb_port::INTERNAL);
  d_cs = define_port("cs", "gmac-cs", false, mb_port::INTERNAL);

  connect("self", "tx0", "GMAC", "tx0");
  connect("self", "rx0", "GMAC", "rx0");
  connect("self", "cs", "GMAC", "cs");

}

test_gmac_tx_file::~test_gmac_tx_file()
{

  d_ifile.close();
}

void
test_gmac_tx_file::handle_message(mb_message_sptr msg)
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

        // Set start time to keep track of performance
        gettimeofday(&d_start, NULL);

        if(pmt_eq(status, PMT_T)) {
          enter_transmitting();
          return;
        }
        else {
          error_msg = "error initializing gmac:";
          goto bail;
        }
      }
      goto unhandled;

    //-------------------------- TRANSMITTING ----------------------------//
    // In the transmit state we count the number of underruns received and
    // ballpark the number with an expected count (something >1 for starters)
    case TRANSMITTING:
      
      // Check that the transmits are OK
      if (pmt_eq(event, s_response_tx_pkt)){
        handle = pmt_nth(0, data);
        status = pmt_nth(1, data);

        if (pmt_eq(status, PMT_T)){
          handle_xmit_response(handle);
          return;
        }
        else {
          error_msg = "bad response-tx-pkt:";
          goto bail;
        }
      }
      goto unhandled;

    //----------------------- ACK WAIT ----------------------------------//
    // In the state of waiting for an ACK, to re-enter the transmit state
    case ACK_WAIT:

      // Check the incoming data
      if (pmt_eq(event, s_response_rx_pkt)){
        handle_response_rx_pkt(data);
        return;
      }

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
  if(verbose && !pmt_eq(event, pmt_intern("%shutdown")))
    std::cout << "[TEST_GMAC_TX_FILE] unhandled msg: " << msg
              << "in state "<< d_state << std::endl;
}

void
test_gmac_tx_file::enter_transmitting()
{
  d_state = TRANSMITTING;

  d_cs->send(s_cmd_carrier_sense_deadline,
             pmt_list2(PMT_NIL,
                       pmt_from_long(50000000)));
  
  // Disable RX to save bandwidth and processing
  d_cs->send(s_cmd_rx_disable, pmt_list1(PMT_NIL));

  build_and_send_next_frame();

}

void
test_gmac_tx_file::build_and_send_next_frame()
{
  size_t ignore;
  long n_bytes;

  // Before we send the frame, we stop the RX port since we are not interested
  // in decoding while transmitting, and full processing can go to TX
  d_cs->send(s_cmd_rx_disable, pmt_list1(PMT_NIL));

  // Let's read in as much as possible to fit in a frame
  char data[MAX_FRAME_SIZE-gmsk::max_frame_payload()];
  d_ifile.read((char *)&data[0], sizeof(data));

  // Use gcount() and test if end of stream was met
  if(!d_ifile) {
    n_bytes = d_ifile.gcount();
    d_done_sending = true;
  } else {
    n_bytes = sizeof(data);
  }

  // Make the PMT data, get a writable pointer to it, then copy our data in
  pmt_t uvec = pmt_make_u8vector(n_bytes, 0);
  char *vdata = (char *) pmt_u8vector_writeable_elements(uvec, ignore);
  memcpy(vdata, data, n_bytes);

  // Per packet properties
  pmt_t tx_properties = pmt_make_dict();

  pmt_t timestamp = pmt_from_long(0xffffffff);	// NOW
  d_tx->send(s_cmd_tx_pkt,
	     pmt_list5(pmt_from_long(d_nframes_xmitted),   // invocation-handle
           pmt_from_long(d_local_addr),// src
           pmt_from_long(d_dst_addr),// destination
		       uvec,				    // the samples
           tx_properties)); // per pkt properties

  d_nframes_xmitted++;

  if(verbose)
    std::cout << "[TEST_GMAC_TX_FILE] Transmitted frame from " << d_local_addr
              << " to " << d_dst_addr 
              << " of size " << n_bytes << " bytes\n";

  std::cout << ".";
  fflush(stdout);
}


void
test_gmac_tx_file::handle_xmit_response(pmt_t handle)
{
  if (d_done_sending && pmt_to_long(handle)==(d_nframes_xmitted-1)){
    gettimeofday(&d_end, NULL);
    std::cout << "Transfer time: " 
              << (d_end.tv_sec-d_start.tv_sec)
              << "."
              << (d_end.tv_usec-d_start.tv_usec)
              << std::endl;
    fflush(stdout);
    shutdown_all(PMT_T);
  }

  // We now want to enter the wait for ACK state
  enter_ack_wait();

}

// Enter the state where we re-enable the RX chain and wait for an ACK to be
// decoded.
void
test_gmac_tx_file::enter_ack_wait()
{
  d_state = ACK_WAIT;

  d_cs->send(s_cmd_rx_enable, pmt_list1(PMT_NIL));

  if(verbose)
    std::cout << "[TEST_GMAC_TX_FILE] Entering ACK wait state\n";
}

void
test_gmac_tx_file::handle_response_rx_pkt(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t payload = pmt_nth(1, data);
  pmt_t pkt_properties = pmt_nth(2, data);

  long lsrc=0, ldst=0;
  bool back;

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

    if(pmt_t ack = pmt_dict_ref(pkt_properties,
                                pmt_intern("ack"),
                                PMT_NIL)) {
      if(pmt_eqv(ack, PMT_T))
        back = true;
      else
        back = false;
    }
  }
  
  // Ensure frame is destined to us, if so we will ACK
  if(ldst != d_local_addr) {
    if(verbose)
      std::cout << "[TEST_GMAC_TX_FILE] Received ACK not destined to us\n";
    return;
  }

  if(!back) {
    if(verbose)
      std::cout << "[TEST_GMAC_TX_FILE] Received a frame that was NOT an ACK\n";
    return;
  }
  
  if(verbose)
    std::cout << "[TEST_GMAC_TX_FILE] Received ACK destined for us!\n";

  // Let's hop back to transmitting, if we're not done sending
  if(!d_done_sending)
    enter_transmitting();

}

REGISTER_MBLOCK_CLASS(test_gmac_tx_file);


// ----------------------------------------------------------------

int
main (int argc, char **argv)
{

  mb_runtime_sptr rt = mb_make_runtime();
  pmt_t result = PMT_NIL;

  rt->run("test_gmac_tx_file", "test_gmac_tx_file", 
      pmt_list3(pmt_intern(argv[1]),
                pmt_from_long(atol(argv[2])),
                pmt_from_long(atol(argv[3]))), 
      &result);
}
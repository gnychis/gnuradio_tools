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

#include <usrp_usb_interface.h>

#include <iostream>
#include <vector>
#include <usb.h>
#include <mb_class_registry.h>
#include <usrp_inband_usb_packet.h>
#include <fpga_regs_common.h>
#include "usrp_rx.h"
#include <usrp_rx_stub.h>
#include "usrp_tx.h"
#include "usrp_standard.h"
#include "db_flexrf_mimo.h"
#include <stdio.h>

typedef usrp_inband_usb_packet transport_pkt;

#include <symbols_usrp_interface_cs.h>
#include <symbols_usrp_tx_cs.h>
#include <symbols_usrp_rx_cs.h>
static pmt_t s_shutdown = pmt_intern("%shutdown");

static const bool verbose = false;


/*!
 * \brief Initializes the USB interface m-block.
 *
 * The \p user_arg should be a PMT dictionary which can contain optional
 * arguments for the block, such as the decimatoin and interpolation rate.
 */
usrp_usb_interface::usrp_usb_interface(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg)
  : mb_mblock(rt, instance_name, user_arg),
  d_fake_usrp(false),
  d_rx_reading(false),
  d_interp_tx(128),
  d_decim_rx(128),
  d_rf_freq(10e6),
  d_rbf("inband_tx_rx.rbf")
{
  // Dictionary for arguments to all of the components
  pmt_t usrp_dict = user_arg;
  
  // Default TX/RX interface
  std::string tx_interface = "usrp_tx";
  std::string rx_interface = "usrp_rx";
  
  if (pmt_is_dict(usrp_dict)) {

    // The 'fake-usrp' key enables the TX and RX stubs if PMT_T
    if(pmt_t fake_usrp = pmt_dict_ref(usrp_dict, 
                                      pmt_intern("fake-usrp"), 
                                      PMT_NIL)) {
      if(pmt_eqv(fake_usrp, PMT_T)) {
        tx_interface = "usrp_tx_stub";
        rx_interface = "usrp_rx_stub";
        d_fake_usrp=true;
      }
    }

    // Read the TX interpolations
    if(pmt_t interp_tx = pmt_dict_ref(usrp_dict, 
                                      pmt_intern("interp-tx"), 
                                      PMT_NIL)) {
      if(!pmt_eqv(interp_tx, PMT_NIL)) 
        d_interp_tx = pmt_to_long(interp_tx);
    }
    
    // Read the RX decimation rate
    if(pmt_t decim_rx = pmt_dict_ref(usrp_dict, 
                                      pmt_intern("decim-rx"), 
                                      PMT_NIL)) {
      if(!pmt_eqv(decim_rx, PMT_NIL)) 
        d_decim_rx = pmt_to_long(decim_rx);
    }

    // Read the RBF
    if(pmt_t rbf = pmt_dict_ref(usrp_dict, 
                                pmt_intern("rbf"), 
                                PMT_NIL)) {
      if(!pmt_eqv(rbf, PMT_NIL)) 
        d_rbf = pmt_symbol_to_string(rbf);
    }

    // The RF center frequency
    if(pmt_t rf_freq = pmt_dict_ref(usrp_dict, 
                                pmt_intern("rf-freq"), 
                                PMT_NIL)) {
      if(!pmt_eqv(rf_freq, PMT_NIL)) 
        d_rf_freq = pmt_to_long(rf_freq);
    }
  }
  
  if (verbose) {
    std::cout << "[USRP_USB_INTERFACE] Setting USRP RBF to " 
              << d_rbf << std::endl;
    
    std::cout << "[USRP_USB_INTERFACE] Setting TX interpolation to " 
              << d_interp_tx << std::endl;
          
    std::cout << "[USRP_USB_INTERFACE] Setting RX interpolation to " 
              << d_decim_rx << std::endl;

    std::cout << "[USRP_USB_INTERFACE] Using TX interface: " 
              << tx_interface << "\n";

    std::cout << "[USRP_USB_INTERFACE] Using RX interface: " 
              << rx_interface << "\n";

  }

  d_cs = define_port("cs", "usrp-interface-cs", true, mb_port::EXTERNAL);	
  d_rx_cs = define_port("rx_cs", "usrp-rx-cs", false, mb_port::INTERNAL);	
  d_tx_cs = define_port("tx_cs", "usrp-tx-cs", false, mb_port::INTERNAL);	

  // Connect to TX and RX
  define_component("tx", tx_interface, usrp_dict);
  define_component("rx", rx_interface, usrp_dict);
  connect("self", "rx_cs", "rx", "cs");
  connect("self", "tx_cs", "tx", "cs");
  
  // FIX ME: the code should query the FPGA to retrieve the number of channels and such
  d_ntx_chan = 2;
  d_nrx_chan = 2;

  d_utx = NULL;
  d_urx = NULL;
  
}

usrp_usb_interface::~usrp_usb_interface() 
{ 

}

void 
usrp_usb_interface::initial_transition()
{

}

/*!
 * \brief Handles all incoming signals to the block from the lowest m-blocks
 * which read/write to the bus, or the higher m-block which is the USRP server.
 */
void
usrp_usb_interface::handle_message(mb_message_sptr msg)
{
  pmt_t event = msg->signal();		// the "name" of the message
  pmt_t port_id = msg->port_id();	// which port it came in on
  pmt_t data = msg->data();
  pmt_t invocation_handle;

  if (pmt_eq(event, s_shutdown))	// ignore (for now)
    return;

  //------------- CONTROL / STATUS -------------//
  if (pmt_eq(port_id, d_cs->port_symbol())) {	

    //------------ OPEN --------------//
    if (pmt_eq(event, s_cmd_usrp_open)){
      handle_cmd_open(data);
      return;
    }
    //----------- CLOSE -------------//
    else if (pmt_eq(event, s_cmd_usrp_close)) {
      handle_cmd_close(data);
      return;
    }
    //---------- NTX CHAN ----------//
    else if (pmt_eq(event, s_cmd_usrp_ntx_chan)) {
      invocation_handle = pmt_nth(0, data);
      d_cs->send(s_response_usrp_ntx_chan, 
                 pmt_list2(invocation_handle, 
                           pmt_from_long(d_ntx_chan)));
      return;
    }
    //---------- NRX CHAN ----------//
    else if (pmt_eq(event, s_cmd_usrp_nrx_chan)) {
      invocation_handle = pmt_nth(0, data);
      d_cs->send(s_response_usrp_nrx_chan, 
                 pmt_list2(invocation_handle, 
                           pmt_from_long(d_nrx_chan)));
      return;
    }
    //------------ WRITE -----------//
    else if(pmt_eq(event, s_cmd_usrp_write)) {
      handle_cmd_write(data);
      return;
    }
    //-------- START READING --------//
    else if(pmt_eq(event, s_cmd_usrp_start_reading)) {
      handle_cmd_start_reading(data);
      return;
    }
    //-------- STOP READING --------//
    else if(pmt_eq(event, s_cmd_usrp_stop_reading)) {
      handle_cmd_stop_reading(data);
      return;
    }

    goto unhandled;
  }

  //---------------- RX ------------------//
  if (pmt_eq(port_id, d_rx_cs->port_symbol())) {	

    // Relay reads back up
    if(pmt_eq(event, s_response_usrp_rx_read))  {
      d_cs->send(s_response_usrp_read, data);
      return;
    }

    goto unhandled;
  }
  
  //---------------- TX ------------------//
  if (pmt_eq(port_id, d_tx_cs->port_symbol())) {	

    if(pmt_eq(event, s_response_usrp_tx_write))  {

      pmt_t invocation_handle = pmt_nth(0, data);
      pmt_t status = pmt_nth(1, data);
      pmt_t channel = pmt_nth(2, data);

      d_cs->send(s_response_usrp_write,
                 pmt_list3(invocation_handle,
                           status,
                           channel));

      return;
    }

    goto unhandled;
  }

 unhandled:
  std::cout << "[USRP_USB_INTERFACE] unhandled msg: " << msg << std::endl;
}

/*!
 * \brief Called by the handle_message() method when the incoming signal is to
 * open a USB connection to the USRP (cmd-usrp-open).
 *
 * The \p data parameter is a PMT list, where the elements are an invocation
 * handle and the USRP number.
 */
void
usrp_usb_interface::handle_cmd_open(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  long which_usrp = pmt_to_long(pmt_nth(1, data));
  pmt_t reply_data;
 
  if(d_fake_usrp) {
    d_cs->send(s_response_usrp_open, pmt_list2(invocation_handle, PMT_T));
    return;
  }

  if (verbose)
    std::cout << "[USRP_USB_INTERFACE] Handling open request for USRP " << which_usrp << "\n";

  // Open up a standard RX and TX for communication with the USRP
   
  d_utx = usrp_standard_tx::make(which_usrp,
				 d_interp_tx,
				 1,		        // 1 channel
				 -1,          // mux
				 4096,        // USB block size
				 16,          // nblocks for async transfers
				 d_rbf
				 );
  
  if(d_utx==0) {
    if (verbose)
      std::cout << "[USRP_USB_INTERFACE] Failed to open TX\n";
    reply_data = pmt_list2(invocation_handle, PMT_F);
    d_cs->send(s_response_usrp_open, reply_data);
    return;
  }

  if(!d_utx->set_mux(0xBA98)) {
    if (verbose)
      std::cout << "[USRP_USB_INTERFACE] Failed to set TX mux\n";
    reply_data = pmt_list2(invocation_handle, PMT_F);
    d_cs->send(s_response_usrp_open, reply_data);
    return;
  }

  if (verbose)
    std::cout << "[USRP_USB_INTERFACE] Setup TX channel\n";

  d_urx =
    usrp_standard_rx::make (which_usrp,
			    d_decim_rx,		
			    1,		        // nchan
			    -1,           // mux
			    0,            // set blank mode to start
			    4096,         // USB block size
			    16,           // number of blocks for async transfers
          d_rbf);

  if(!d_urx) {
    if (verbose)
      std::cout << "[usrp_server] Failed to open RX\n";
    reply_data = pmt_list2(invocation_handle, PMT_F);
    d_cs->send(s_response_usrp_open, reply_data);
    return;
  }

  // Two channels ... this really needs to end up being set correctly by
  // querying for what dboards are connected
  if(!d_urx->set_mux(0x32103210)) {
    if (verbose)
      std::cout << "[USRP_USB_INTERFACE] Failed to set RX mux\n";
    reply_data = pmt_list2(invocation_handle, PMT_F);
    d_cs->send(s_response_usrp_open, reply_data);
    return;
  }

  if (verbose)
    std::cout << "[USRP_USB_INTERFACE] Setup RX channel\n";
    
//  d_utx->_write_fpga_reg(FR_DEBUG_EN,0xf);
//  d_utx->_write_oe(0, 0xffff, 0xffff);
//  d_urx->_write_oe(0, 0xffff, 0xffff);
//  d_utx->_write_oe(1, 0xffff, 0xffff);
//  d_urx->_write_oe(1, 0xffff, 0xffff);

  d_cs->send(s_response_usrp_open, pmt_list2(invocation_handle, PMT_T));

  // Tune daughterboards
  db_flexrf_mimo dboards(d_urx, d_utx, 0);
  dboards.configure(d_rf_freq, 45, 0);
  dboards.configure(d_rf_freq, 0, 1);
  dboards.select_tx();
  
  d_utx->start();

}

/*!
 * \brief Called by the handle_message() method when the incoming signal is to
 * write data to the USB bus (cmd-usrp-write). 
 *
 * The \p data parameter is a PMT list containing 3 mandatory elements in the
 * following order: an invocation handle, channel, and a uniform vector
 * representation of the packets.
 */
void
usrp_usb_interface::handle_cmd_write(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  pmt_t channel = pmt_nth(1, data);
  pmt_t pkts = pmt_nth(2, data);

  pmt_t tx_handle = pmt_make_any(d_utx);

  d_tx_cs->send(s_cmd_usrp_tx_write, 
                pmt_list4(invocation_handle, 
                          channel,
                          pkts,
                          tx_handle));

  return;
}

/*!
 * \brief Called by the handle_message() method when the incoming signal is to
 * start reading data from the USB bus (cmd-usrp-start-reading).
 *
 * The \p data parameter is a PMT list with a single element: an invocation
 * handle which can be returned with the response.
 */
void
usrp_usb_interface::handle_cmd_start_reading(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  
  if(verbose)
    std::cout << "[USRP_USB_INTERFACE] Starting RX...\n";

  if(!d_fake_usrp)
    d_urx->start();

  pmt_t rx_handle = pmt_make_any(d_urx);

  d_rx_cs->send(s_cmd_usrp_rx_start_reading, pmt_list2(PMT_NIL, rx_handle));

  d_rx_reading = true;

  return;
}

/*!
 * \brief Called by the handle_message() method when the incoming signal is to
 * stop reading data from the USB bus (cmd-usrp-stop-reading).
 *
 * The \p data parameter is a PMT list with a single element: an invocation
 * handle which can be returned with the response.
 */
void
usrp_usb_interface::handle_cmd_stop_reading(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);
  
  if(!d_fake_usrp) {
    if(verbose)
      std::cout << "[USRP_USB_INTERFACE] Stopping RX...\n";
    usrp_rx_stop = true;

    // Used to allow a read() being called by a lower layer to complete before
    // stopping, else there can be partial data left on the bus and can generate
    // errors.
    while(usrp_rx_stop) {usleep(1);}
    d_urx->stop();
  }
  else {
    if(verbose)
      std::cout << "[USRP_USB_INTERFACE] Stopping fake RX...\n";
    usrp_rx_stop_stub = true;  // extern to communicate with stub to wait
  }

  d_rx_reading = false;

  return;
}

/*!
 * \brief Called by the handle_message() method when the incoming signal is to
 * close the USB connection to the USRP.
 *
 * The \p data parameter is a PMT list with a single element: an invocation
 * handle which can be returned with the response.
 */
void
usrp_usb_interface::handle_cmd_close(pmt_t data)
{
  pmt_t invocation_handle = pmt_nth(0, data);

  if(d_rx_reading)
    handle_cmd_stop_reading(PMT_NIL);

  if(d_fake_usrp) {
    d_cs->send(s_response_usrp_close, pmt_list2(invocation_handle, PMT_T));
    return;
  }
  
  if (verbose)
    std::cout << "[USRP_USB_INTERFACE] Handling close request for USRP\n";

  delete d_utx;
  d_utx = 0;

  delete d_urx;
  d_urx = 0;

  d_cs->send(s_response_usrp_close, pmt_list2(invocation_handle, PMT_T));

  shutdown_all(PMT_T);
}


REGISTER_MBLOCK_CLASS(usrp_usb_interface);

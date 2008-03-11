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

#ifndef INCLUDED_GMSK_H
#define INCLUDED_GMSK_H

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

#include <gmsk_symbols.h>
#include <gr_interp_fir_filter_fff.h>
#include <gr_fir_fff.h>
#include <gr_firdes.h>
#include <gr_bytes_to_syms.h>
#include <gr_frequency_modulator_fc.h>
#include <gr_quadrature_demod_cf.h>
#include <gr_clock_recovery_mm_ff.h>
#include <gr_binary_slicer_fb.h>
#include <gr_fft_filter_ccc.h>
#include <gr_correlate_access_code_bb.h>
#include <sys/time.h>
#include <fstream>
#include <malloc16.h>
#include <cmath>
#include <bitset>
#include <queue>

#include <boost/crc.hpp>
#include <boost/cstdint.hpp>

#include <gmsk_framer.h>

static const int BITS_PER_BYTE = 8;

class gmsk;

class gmsk : public mb_mblock
{
  d_frame_hdr_t d_frame_hdr;

  enum state_t {
    SYNC_SEARCH,
    WAIT_HEADER,
    HAVE_HEADER,
    WAIT_PAYLOAD,
    HAVE_PAYLOAD
  };
  state_t	d_state;

  // Ports used for applications to connect to this block
  mb_port_sptr		  d_cs;

  long d_samples_per_symbol;
  float d_bt;
  float d_gain_mu;
  float d_mu;
  float d_freq_error;
  float d_omega_relative_limit;
  float d_omega;
  float d_gain_omega;

  long d_ntaps;
  float d_sensitivity;
  long d_sw_decim;
  long d_amplitude;

  bool d_low_pass;
  bool d_squelch;

  long d_corr_thresh;

  gr_complex d_fmdemod_last;

  std::vector<float> d_gaussian_taps;
  std::vector<float> d_chan_coeffs;
  std::vector<gr_complex> d_cchan_coeffs;
  std::vector<float> d_sqwave;
  std::vector<float> d_taps;

  std::string d_access_code;
  std::string d_preamble;
  std::string d_postamble;

  std::queue<gr_complex>  d_filterq;
  std::queue<float>       d_crq;

  std::vector<unsigned char> d_hdr_bits;
  std::vector<unsigned char> d_payload_bits;

  std::vector<float> d_gf_history;
  std::vector<gr_complex> d_fm_history;

  // Block instances
  // NRZ->Gauss->FM
  gr_bytes_to_syms_sptr             d_bts;
  gr_interp_fir_filter_fff_sptr     d_gf;
  gr_frequency_modulator_fc_sptr    d_fm_mod;
  gr_quadrature_demod_cf_sptr       d_fm_demod;
  gr_clock_recovery_mm_ff_sptr      d_cr;
  gr_binary_slicer_fb_sptr          d_slicer;
  gr_fft_filter_ccc_sptr            d_chan_filt;
  gr_correlate_access_code_bb_sptr  d_corr;

  bool d_disk_write;

  d_frame_hdr_t d_cframe_hdr;

  long d_nframes_recvd;
  
 public:
  gmsk(mb_runtime *rt, const std::string &instance_name, pmt_t user_arg);
  ~gmsk();
  void handle_message(mb_message_sptr msg);
  static int max_frame_payload() {
    return(sizeof(d_frame_hdr_t));
  }

 private:
  void define_ports();
  void mod(pmt_t data);
  void convolve(float X[],float Y[], float Z[], int lenx, int leny);
  void demod(pmt_t data);
  void conv_to_binary(std::string code, std::vector<unsigned char> &output);

  void framer(const std::vector<unsigned char> input);
  void framer_found_sync();
  void framer_new_header_bit(unsigned char bit);
  void framer_new_payload_bit(unsigned char bit);
  void framer_have_header();
  void framer_have_payload();
  void framer_have_frame(pmt_t uvec);
};

#endif // INCLUDED_GMAC_H

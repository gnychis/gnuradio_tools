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
#include <queue>
#include <sys/time.h>

static const int BITS_PER_BYTE = 8;
static const int MAX_FRAME_SIZE = 1500;

class gmsk;

class gmsk : public mb_mblock
{

  typedef struct d_frame_hdr_t {
    long src_addr;
    long dst_addr;
    long payload_len;
    bool ack;
    long crc;
  } __attribute__((__packed__)) d_frame_hdr;

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

  struct timeval d_start, d_end;
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
};

#endif // INCLUDED_GMAC_H

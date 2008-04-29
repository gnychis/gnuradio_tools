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
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <cmusdrg_mf_sync_ccf.h>
#include <gr_io_signature.h>
#include <math.h>
#include <assert.h>
#include <stdexcept>
#include <gr_fir_util.h>
#include <gr_fir_ccc.h>

#include <iostream>

const static int NFILTERS = 16;
const static int COEFFS_PER_CHIPSEQ = 64;

cmusdrg_mf_sync_ccf_sptr
cmusdrg_make_mf_sync_ccf(const std::vector<gr_complex> &coeffs)
{
  return cmusdrg_mf_sync_ccf_sptr (new cmusdrg_mf_sync_ccf(coeffs));
}

cmusdrg_mf_sync_ccf::cmusdrg_mf_sync_ccf (const std::vector<gr_complex> &coeffs)
  : gr_block ("cmusdrg_mf_sync_ccf",
      gr_make_io_signature(2, 2, sizeof(gr_complex)),
      gr_make_io_signature(1, 1, sizeof(char)))
{
   set_history(COEFFS_PER_CHIPSEQ);
   found_sync = false;
   d_buffer_size = 0;
   filters.resize(NFILTERS);
  // Extract the coefficients
  for(int i=0; i<NFILTERS; i++) {

    // Split the filters up into COEFFS_PER_CHIPSEQ
    std::vector<gr_complex> filter_coeffs;
    for(int j=i*COEFFS_PER_CHIPSEQ; j<((i+1)*COEFFS_PER_CHIPSEQ); j++)
      filter_coeffs.push_back(coeffs[j]);
    
    // Need to time reverse the coefficients for the filter
    std::reverse(filter_coeffs.begin(), filter_coeffs.end());
    filters[i] = gr_fir_util::create_gr_fir_ccc (filter_coeffs);
  }
}

// The number of input items required for a single output bit sequence is
// the number of complex samples needed to represent a single chip sequence
void
cmusdrg_mf_sync_ccf::forecast (int noutput_items,
                    gr_vector_int &ninput_items_required)
{
  unsigned ninputs = ninput_items_required.size ();
  for (unsigned i = 0; i < ninputs; i++)
    ninput_items_required[i] = noutput_items*COEFFS_PER_CHIPSEQ;
}

cmusdrg_mf_sync_ccf::~cmusdrg_mf_sync_ccf()
{
  for(int i=0; i<NFILTERS; i++)
    delete filters[i];
}

float
cmusdrg_mf_sync_ccf::compute_magnitude(gr_complex input)
{
  float result = sqrt(input.real()*input.real() + input.imag()*input.imag());
  return result;
}

int
cmusdrg_mf_sync_ccf::general_work(int noutput_items,
      gr_vector_int &ninput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items)
{

  gr_complex *in1 = (gr_complex *) input_items[0];
  gr_complex *in2 = (gr_complex *) input_items[1];
  char *out = (char *) output_items[0];

  int ninput = ninput_items[0];

  //the earliest valid sample in the buffer is left offset
  //|1 left off||64 samples||1 right off|
  int items_out = 0;
  int data_left = ninput + d_buffer_size; 
  in1 -= d_buffer_size;
  in2 -= d_buffer_size;

  gr_complex filter_out;
  float max_magnitude;
  float cur_magnitude;
  int decoded_result;
  int freq_offset_correction;

  //samples + offset
  while (data_left >= COEFFS_PER_CHIPSEQ + 1) {
    //note sync if there is any
    for (int i = 0; i< (COEFFS_PER_CHIPSEQ+1); i++) {
      if(in1[i].real() == 1) {
        in1 += i-1;
        in2 += i-1;
        data_left -= i-1;
        found_sync = true;
        break;
      }
    } 

    //may not have enough sample now
    if (data_left < COEFFS_PER_CHIPSEQ + 1) {
      break;
    }
    
    freq_offset_correction = 0;
    max_magnitude = 0;
    decoded_result = 0;
    //start decoding
    // Run each of the NFILTERS to find the best fit
    for(int i=0; i<NFILTERS; i++) {
      filter_out = filters[i]->filter (in2 + 1);
      cur_magnitude = compute_magnitude(filter_out);
      if (cur_magnitude > max_magnitude) {
        max_magnitude = cur_magnitude;
        decoded_result = i;
      }
    }
    //perform offset correction
    filter_out = filters[decoded_result]->filter (in2);
    cur_magnitude = compute_magnitude(filter_out);
    if (cur_magnitude > max_magnitude) {
      max_magnitude = cur_magnitude;
      freq_offset_correction = -1;
    }
    filter_out = (data_left >= COEFFS_PER_CHIPSEQ + 2) ? filters[decoded_result]->filter (in2 + 2) : 0;
    cur_magnitude = compute_magnitude(filter_out);
    if (cur_magnitude > max_magnitude) {
      max_magnitude = cur_magnitude;
      freq_offset_correction = 1;
    }    
    freq_offset_correction = 0;
    data_left       -= COEFFS_PER_CHIPSEQ + freq_offset_correction;
    in1             += COEFFS_PER_CHIPSEQ + freq_offset_correction;
    in2             += COEFFS_PER_CHIPSEQ + freq_offset_correction;
    //mark the output if found_sync
    out[items_out++] = (found_sync) ? (char)decoded_result + 16 : (char)decoded_result;

    found_sync = false;
  }
  d_buffer_size = data_left;
  
  for (int i = 0; i< items_out; i++) {
    if (out[i] >= 16) {
      printf("\nStart of frame\n");
    }
    printf("%x", out[i]%16);
  }

  while (noutput_items - items_out > 0) {
        out[items_out++] = -1;
        std::cout<<"Don't care"<<std::endl;
  }
  consume_each(ninput);
  return noutput_items;
}

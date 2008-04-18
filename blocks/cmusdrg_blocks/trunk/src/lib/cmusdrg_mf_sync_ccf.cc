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
      gr_make_io_signature(1, 1, sizeof(char))),
      d_have_sync(false)
{

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

  // If we do not have sync we use our complex component to look for
  // the sync value being set, once it is we set our symbol boundary
  // synchronization and start to use the filters.
  if(!d_have_sync) {
    for(int i=0; i<ninput; i++) {
      if(in1[i].real()==1) {
        in1 += i;   // Skip through our input to the sync point
        in2 += i;
        d_have_sync=true;
        break;
      }
    }
  }

  // If we still have not found sync, let's consume all of the input
  // and just return, the output will be 0's.
  if(!d_have_sync) {
    consume_each(ninput);
    return noutput_items;
  }

  // Run each of the NFILTERS, putting its complex output into a vector
  std::vector<gr_complex> filter_outputs;
  for(int i=0; i<NFILTERS; i++) {
    gr_complex filter_out = filters[i]->filter (in2);
    filter_outputs.push_back( filter_out );
  }

  consume_each(noutput_items*COEFFS_PER_CHIPSEQ);

  return noutput_items;
}

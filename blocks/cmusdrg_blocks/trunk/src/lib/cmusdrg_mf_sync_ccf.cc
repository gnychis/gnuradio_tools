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
  : gr_sync_block ("cmusdrg_mf_sync_ccf",
      gr_make_io_signature(2, 2, sizeof(gr_complex)),
      gr_make_io_signature(1, 1, sizeof(float)))
{

  // Extract the coefficients
  for(int i=0; i<NFILTERS; i++) {

    std::vector<gr_complex> filter_coeffs;
    for(int j=i*COEFFS_PER_CHIPSEQ; j<((i+1)*COEFFS_PER_CHIPSEQ); j++)
      filter_coeffs.push_back(coeffs[j]);
    
    filters[i] = gr_fir_util::create_gr_fir_ccc (filter_coeffs);
  }
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
cmusdrg_mf_sync_ccf::work(int noutput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items)
{
  gr_complex *in1 = (gr_complex *) input_items[0];
  gr_complex *in2 = (gr_complex *) input_items[1];
  float *out = (float *) output_items[0];

  return noutput_items;
}

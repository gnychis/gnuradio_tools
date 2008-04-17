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

#include <iostream>

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
  // Build match filters
}

cmusdrg_mf_sync_ccf::~cmusdrg_mf_sync_ccf()
{
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

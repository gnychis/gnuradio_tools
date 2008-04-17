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

#include <cmusdrg_acquisition_filter_ccc.h>
#include <gr_io_signature.h>
#include <math.h>
#include <assert.h>
#include <stdexcept>

#include <iostream>

cmusdrg_acquisition_filter_ccc_sptr
cmusdrg_make_acquisition_filter_ccc(long threshold, long window)
{
  return cmusdrg_acquisition_filter_ccc_sptr (new cmusdrg_acquisition_filter_ccc(threshold, window));
}

cmusdrg_acquisition_filter_ccc::cmusdrg_acquisition_filter_ccc (long threshold, long window)
  : gr_block ("cmusdrg_acquisition_filter_ccc",
      gr_make_io_signature(2, 2, sizeof(gr_complex)),
      gr_make_io_signature(2, 2, sizeof(gr_complex))),
    d_threshold(threshold),
    d_window(window)
{
}

cmusdrg_acquisition_filter_ccc::~cmusdrg_acquisition_filter_ccc()
{
}

float
cmusdrg_acquisition_filter_ccc::compute_magnitude(gr_complex input)

  return sqrt(input.real()*input.real() + input.imag()*input.imag());
}

int
cmusdrg_acquisition_filter_ccc::work(int noutput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items)
{
  gr_complex *in1 = (gr_complex *) input_items[0];
  gr_complex *in2 = (gr_complex *) input_items[1];
  gr_complex *out1 = (gr_complex *) output_items[0];
  gr_complex *out2 = (gr_complex *) output_items[1];


  return noutput_items;
}
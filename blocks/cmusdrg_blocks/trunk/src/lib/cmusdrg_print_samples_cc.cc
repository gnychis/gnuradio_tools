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

#include <cmusdrg_print_samples_cc.h>
#include <gr_io_signature.h>
#include <math.h>
#include <assert.h>
#include <stdexcept>

#include <iostream>

cmusdrg_print_samples_cc_sptr
cmusdrg_make_print_samples_cc()
{
  return cmusdrg_print_samples_cc_sptr (new cmusdrg_print_samples_cc());
}

cmusdrg_print_samples_cc::cmusdrg_print_samples_cc ()
  : gr_sync_block ("cmusdrg_print_samples_cc",
      gr_make_io_signature(1, 1, sizeof(gr_complex)),
      gr_make_io_signature(1, 1, sizeof(gr_complex)))
{
}

cmusdrg_print_samples_cc::~cmusdrg_print_samples_cc()
{
}

int
cmusdrg_print_samples_cc::work(int noutput_items,
      gr_vector_const_void_star &input_items,
      gr_vector_void_star &output_items)
{
  gr_complex *in1 = (gr_complex *) input_items[0];
  gr_complex *out1 = (gr_complex *) output_items[0];

  for (int i = 0; i< noutput_items; i++) {
    std::cout << in1[i].real() << " " << in1[i].imag() << std::endl;
    fflush(stdout);
    out1[i]=in1[i];
  }

  return noutput_items;
}

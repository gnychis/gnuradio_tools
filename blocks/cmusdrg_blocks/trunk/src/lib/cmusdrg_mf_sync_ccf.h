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

#ifndef INCLUDED_CMUSDRG_MF_SYNC_CCF_H
#define INCLUDED_CMUSDRG_MF_SYNC_CCF_H

#include <gr_block.h>
#include <gr_io_signature.h>
#include <gr_fir_util.h>
#include <gr_fir_ccc.h>

class cmusdrg_mf_sync_ccf;
typedef boost::shared_ptr<cmusdrg_mf_sync_ccf> cmusdrg_mf_sync_ccf_sptr;

cmusdrg_mf_sync_ccf_sptr
cmusdrg_make_mf_sync_ccf (const std::vector<gr_complex> &coeffs);

class cmusdrg_mf_sync_ccf : public gr_block
{
 private:
  friend cmusdrg_mf_sync_ccf_sptr cmusdrg_make_mf_sync_ccf (const std::vector<gr_complex> &coeffs);

  cmusdrg_mf_sync_ccf(const std::vector<gr_complex> &coeffs);

  float compute_magnitude(gr_complex input);
  
  int  d_buffer_size;

 public:
  ~cmusdrg_mf_sync_ccf();

  void forecast(int noutput_items, gr_vector_int &ninput_items_required);

  int general_work(int noutput_items,
    gr_vector_int &ninput_items,
    gr_vector_const_void_star &input_items,
    gr_vector_void_star &output_items);
 
 protected:
  std::vector<gr_fir_ccc *>     filters;
};

#endif

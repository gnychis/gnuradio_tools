#!/usr/bin/env python
#
# Copyright 2004 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
# 

import sys, array, numpy, math, time

from gnuradio import gr
from gnuradio.eng_option import eng_option

# Rotate the complex numbers 45deg on the unit circle
def rotate(cnum):
  
  # Q1 to (0,i)
  if(cnum.real>0 and cnum.imag>=0):
    return complex(0,1)

  # Q2 to (-1,0)
  if(cnum.real<=0 and cnum.imag>0):
    return complex(-1,0)    

  # Q3 to (0,-i)
  if(cnum.real<0 and cnum.imag<=0):
    return complex(0,-1)

  # Q4 to (1,0)
  if(cnum.real>=0 and cnum.imag<0):
    return complex(1,0)

  # Must already be on an edge
  return cnum

def build_graph (input, output, coeffs, mag):

    # Initialize empty flow graph
    fg = gr.top_block ()

    # Set up file source
    src = gr.file_source (gr.sizeof_gr_complex, input)

    # Read coefficients for the matched filter
    dfile = open(coeffs, 'r')
    data = []
    for line in dfile:
      data.append(complex(*map(float,line.strip().strip("()").split(" "))).conjugate())
    dfile.close()

    # Rotate the coefficients for optimization
    for i in range(0, len(data)):
      data[i] = rotate(data[i])
      print data[i].real, data[i].imag

    # Time reverse the data and pass
    data.reverse()
    mfilter = gr.fir_filter_ccc(1, data)

    # Compute magnitude
    magnitude = gr.complex_to_mag(1)

    # If the output is magnitude, it is float, else its complex
    if mag:
      magnitude = gr.complex_to_mag(1)
      dst = gr.file_sink (gr.sizeof_float, output)
      fg.connect(src, mfilter, magnitude, dst)
    else:
      dst = gr.file_sink (gr.sizeof_gr_complex, output)
      fg.connect(src, mfilter, dst)

    return fg

def main (args):
    nargs = len (args)
    mag = False
    if nargs >= 3:
        input = args[0]
        output = args[1]
        coeffs = args[2]
        if nargs == 4:
          mag = True
    else:
        sys.stderr.write ("usage: ./matched_filter.py input output coeffs mag?\n")
        sys.exit (1)

    fg = build_graph (input, output, coeffs, mag)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])

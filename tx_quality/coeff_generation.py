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
from gmsk     import gmsk_mod

def build_graph(outfile):

  # Initialize our top block
  fg = gr.top_block()

  # Input
  input = [0x00, 0xa7]

  # Unsigned char source to use the input
  src = gr.vector_source_b(input)

  # Set up GMSK modulator, 2 samples per symbol
  mod = gmsk_mod(2)

  # File sink
  fsink = gr.file_sink(gr.sizeof_gr_complex, outfile)

  fg.connect(src, mod, fsink)

  return fg

def main (args):
  nargs = len(args)
  if nargs == 1:
    outfile = args[0]
  else:
    sys.stderr.write ("usage: ./zigbee_acquisition_coeff_generation.py outfile\n")
    sys.exit(1)

  fg = build_graph (outfile)
  fg.run()

if __name__ == '__main__':
  main (sys.argv[1:])


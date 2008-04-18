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
from gnuradio import ucla

def build_graph(outfile):

  # Initialize our top block
  fg = gr.top_block()

  # Input
  input = [0x10, 0x32, 0x54, 0x76, 0x98, 0xBA, 0xDC, 0xFE]

  # Unsigned char source to use the input
  src = gr.vector_source_b(input)

  symbolsToChips = ucla.symbols_to_chips_bi()
  chipsToSymbols = gr.packed_to_unpacked_ii(2, gr.GR_MSB_FIRST)
  symbolsToConstellation = gr.chunks_to_symbols_ic((-1-1j, -1+1j, 1-1j, 1+1j))
  pskmod = ucla.qpsk_modulator_cc()
  delay = ucla.delay_cc(2)

  # File sink
  fsink = gr.file_sink(gr.sizeof_gr_complex, outfile)

  fg.connect(src, symbolsToChips, chipsToSymbols, symbolsToConstellation, pskmod, delay, fsink)

  return fg

def main (args):
  nargs = len(args)
  if nargs == 1:
    outfile = args[0]
  else:
    sys.stderr.write ("usage: ./zigbee_chip_coeff_generation.py outfile\n")
    sys.exit(1)

  fg = build_graph (outfile)
  fg.run()

if __name__ == '__main__':
  main (sys.argv[1:])


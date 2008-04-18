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
from gnuradio import cmusdrg

def build_graph(input, output, coeffs, sync_thresh, sync_window):

  # Initialize our top block
  fg = gr.top_block()

  # Source is a file
  src = gr.file_source (gr.sizeof_gr_complex, input)

  # Read coefficients for the matched filter (FIR filter)
  dfile = open(coeffs, 'r')
  data = []
  for line in dfile:
    data.append(complex(*map(float,line.strip().strip("()").split(" "))).conjugate())
  dfile.close()
  data.reverse()
  mfilter = gr.fir_filter_ccc(1, data)    # Our matched filter!

  # Delay component, to sync the original complex with MF output
  delay = gr.delay(gr.sizeof_gr_complex, len(data)-1)

  # Acquisition filter with threshold and window
  acq = cmusdrg.acquisition_filter_ccc(sync_thresh, sync_window)

  # Connect complex input to matched filter and delay
  fg.connect(src, mfilter)
  fg.connect(src, delay)

  # Connect the mfilter and delay to the acquisition filter
  fg.connect(mfilter, (acq, 0))
  fg.connect(delay, (acq, 1))

  # Two file sinks for the output
  fsink1 = gr.file_sink (gr.sizeof_gr_complex, output+"_acq")
  fsink2 = gr.file_sink (gr.sizeof_gr_complex, output+"_complex")
  fsink3 = gr.file_sink (gr.sizeof_gr_complex, output+"_mfilter")
  fg.connect((acq, 0), fsink1)
  fg.connect((acq, 1), fsink2)
  fg.connect(mfilter, fsink3)

  return fg

def main (args):
  nargs = len (args)
  if nargs == 5:
      input = args[0]
      output = args[1]
      coeffs = args[2]
      sync_thresh = int(args[3])
      sync_window = int(args[4])
  else:
      sys.stderr.write ("usage: ./zigbee_demod.py input output coeffs sync_thresh sync_window\n")
      sys.exit (1)

  fg = build_graph (input, output, coeffs, sync_thresh, sync_window)
  fg.run()

if __name__ == '__main__':
  main (sys.argv[1:])

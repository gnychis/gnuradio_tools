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

def build_graph (input, output, coeffs):

    # Initialize empty flow graph
    fg = gr.flow_graph ()

    # Set up file source
    src = gr.file_source (gr.sizeof_gr_complex, input)

    # Read coefficients for the matched filter
    dfile = open(coeffs, 'r')
    data = []
    for line in dfile:
      data.append(complex(*map(float,line.strip().strip("()").split(" "))).conjugate())
    dfile.close()
    data.reverse()
    mfilter = gr.fir_filter_ccc(1, data)

    # Connect the flow graph
    dst = gr.file_sink (gr.sizeof_gr_complex, output)
    fg.connect(src, mfilter, dst)

    return fg

def main (args):
    nargs = len (args)
    if nargs == 3:
        input = args[0]
        output = args[1]
        coeffs = args[2]
    else:
        sys.stderr.write ("usage: ./matched_filter.py input output coeffs\n")
        sys.exit (1)

    fg = build_graph (input, output, coeffs)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])

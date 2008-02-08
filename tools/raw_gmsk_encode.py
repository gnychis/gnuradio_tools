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

import sys
import array
import numpy
sys.path.append('../phys/')

from gnuradio import gr
from gnuradio import modulation_utils
from gmsk     import gmsk_mod
from gnuradio.eng_option import eng_option

def build_graph (input, raw, amp):

    # Initialize empty flow graph
    fg = gr.flow_graph ()

    # Set up file source
    src = gr.file_source (1, input)

    # Set up GMSK modulator, 2 samples per symbol
    mod = gmsk_mod(fg, 2)

    # Set up an amp
    amp = gr.multiply_const_cc(amp)

    # Connect the flow graph
    raw_dst = gr.file_sink (gr.sizeof_gr_complex, raw)
    fg.connect(src, mod.head)
    fg.connect(mod.tail, amp)
    fg.connect(amp, raw_dst)

    return fg

def main (args):
    nargs = len (args)
    if nargs == 3:
        input = args[0]
        raw = args[1]
        amp = int(args[2])
    else:
        sys.stderr.write ("usage: raw_encode input output amp\n")
        sys.exit (1)

    fg = build_graph (input, raw, amp)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])

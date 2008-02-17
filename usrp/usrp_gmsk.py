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
from gnuradio import usrp
from gnuradio import modulation_utils
from gmsk     import gmsk_mod
from gnuradio.eng_option import eng_option

def init_usrp(usrp_dst, freq, amp):
    usrp_dst.set_interp_rate(128)
    subdev_spec = usrp.pick_tx_subdevice(usrp_dst)
    usrp_dst.set_mux(usrp.determine_tx_mux_value(usrp_dst, subdev_spec))
    subdev = usrp.selected_subdev(usrp_dst, subdev_spec)
    subdev.set_gain(subdev.gain_range()[1])
    tx_amplitude = max(0.0, min(12000, 32767.0))
    amp.set_k(tx_amplitude)
    subdev.set_auto_tr(True)
    tune = usrp.tune(usrp_dst, 0, subdev, freq)

def build_graph (input, freq):

    # Initialize empty flow graph
    fg = gr.top_block ()

    # Set up file source
    src = gr.file_source (1, input, True)

    # Set up GMSK modulator, 2 samples per symbol
    mod = gmsk_mod(fg, 2)

    # USRP destination
    usrp_dst = usrp.sink_c(0)
    amp = gr.multiply_const_cc(1)
    init_usrp(usrp_dst, freq, amp)

    # Connect the flow graph
    fg.connect(src, mod.head)
    fg.connect(mod.tail, amp, usrp_dst)

    return fg

def main (args):
    nargs = len (args)
    if nargs == 2:
        input = args[0]
        freq = int(args[1])
    else:
        sys.stderr.write ("usage: gen_usrp input freq\n")
        sys.exit (1)

    fg = build_graph (input, freq)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])

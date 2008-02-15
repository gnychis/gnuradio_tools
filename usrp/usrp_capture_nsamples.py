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

from gnuradio import gr
from gnuradio import usrp
from gnuradio.eng_option import eng_option
import sys

def build_graph (filename, IF_freq, decim_rate, sample_count):

    # Initialize empty flow graph
    fg = gr.flow_graph ()

    # Pick USRP 0 and set the decimation rate
    src = usrp.source_c (0)
    src.set_decim_rate(decim_rate)

    # Select side-A of the board, set the mux, get a handle
    # to the board, and then tune it to the specified freq
    subdev_spec = (0,0)
    src.set_mux(usrp.determine_rx_mux_value(src, subdev_spec))
    subdev = usrp.selected_subdev(src, subdev_spec)
    usrp.tune(src, 0, subdev, IF_freq)

    # Connect the flow graph
    dst = gr.file_sink (gr.sizeof_gr_complex, filename)
    head = gr.head(gr.sizeof_gr_complex, sample_count)
    fg.connect(src, head, dst)

    return fg

def main (args):
    nargs = len (args)
    if nargs == 4:
        filename = args[0]
        IF_freq_hz = int(args[1])
        decim_rate = int (args[2])
        samples = int(args[3])
    else:
        sys.stderr.write ("usage: usrp_capture_nsamples.py file_name IF_freq_hz decim_rate num_samples\n")
        sys.exit (1)

    print "Capturing ", samples, " samples"

    fg = build_graph (filename, IF_freq_hz, decim_rate, samples)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])


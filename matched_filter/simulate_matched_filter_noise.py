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
sys.path.append('../phys/')

from gnuradio import gr
from gnuradio import usrp
from gnuradio import modulation_utils
from gmsk     import gmsk_mod
from gnuradio.eng_option import eng_option

def build_graph (input, raw, snr, freq_offset, coeffs, mag):

    # Initialize empty flow graph
    fg = gr.top_block ()

    # Set up file source
    src = gr.file_source (1, input)

    # Set up GMSK modulator, 2 samples per symbol
    mod = gmsk_mod(2)

    # Amplify the signal
    tx_amp = 1
    amp = gr.multiply_const_cc(1)
    amp.set_k(tx_amp)

    # Compute proper noise voltage based on SNR
    SNR = 10.0**(snr/10.0)
    power_in_signal = abs(tx_amp)**2
    noise_power = power_in_signal/SNR
    noise_voltage = math.sqrt(noise_power)

    # Generate noise
    rseed = int(time.time())
    noise = gr.noise_source_c(gr.GR_GAUSSIAN, noise_voltage, rseed)
    adder = gr.add_cc()
    fg.connect(noise, (adder, 1))
    
    # Create the frequency offset, 0 for now
    offset = gr.sig_source_c(1, gr.GR_SIN_WAVE, freq_offset, 1.0, 0.0)
    mixer = gr.multiply_cc()
    fg.connect(offset, (mixer, 1))

    # Pass the noisy data to the matched filter
    dfile = open(coeffs, 'r')
    data = []
    for line in dfile:
      data.append(complex(*map(float,line.strip().strip("()").split(" "))).conjugate())
    dfile.close()
    data.reverse()
    mfilter = gr.fir_filter_ccc(1, data)


    # Connect the flow graph
    raw_dst = gr.file_sink (gr.sizeof_float, raw)
    fg.connect(src, mod)
    fg.connect(mod, (mixer, 0))
    fg.connect(mixer, (adder, 0))

    if mag:
      magnitude = gr.complex_to_mag(1)
      fg.connect(adder, mfilter, magnitude, raw_dst)
    else:
      fg.connect(adder, mfilter, raw_dst)

    print "SNR(db): " + str(snr)
    print "Frequency Offset: " + str(freq_offset)

    return fg

def main (args):
    nargs = len (args)
    mag = False
    if nargs >= 5:
        input = args[0]
        raw = args[1]
        snr = int(args[2])
        freq_offset = int(args[3])
        coeffs = args[4]
        if nargs == 6:
          mag = True
    else:
        sys.stderr.write ("usage: matched_filter_noise.py input raw_out SNR(db) freq_offset coeffs mag?\n")
        sys.exit (1)

    fg = build_graph (input, raw, snr, freq_offset, coeffs, mag)
    fg.run()

if __name__ == '__main__':
    main (sys.argv[1:])

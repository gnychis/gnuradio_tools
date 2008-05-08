#!/bin/bash
../tools/read_binary_complex /tmp/outfile_acq | awk '{print $1}' > /tmp/ascii_acq
../tools/read_binary_float /tmp/outfile_power > /tmp/ascii_power

#!/usr/bin/env python
from gnuradio import usrp
import gnuradio.gr.gr_threading as _threading
from gnuradio import cmusdrg
import sys, time

def run(freq, args):

  # Now make a mblock_bootstrap
  mblock_bootstrap = cmusdrg.mblock_bootstrap("cmac_tx_file", args)
  mblock_bootstrap.start()

def main (args):
  nargs = len(args)
  if nargs >= 4:
    freq = int(args[0])
    filename = args[1]
    saddr = int(args[2])
    daddr = int(args[3])
  else:
    sys.stderr.write ("usage: ./run_cmac_tx_file.py if_freq input_file src_addr dst_addr\n")
    sys.exit (1)

  run(freq, sys.argv[2:])

if __name__ == '__main__':
  main(sys.argv[1:])

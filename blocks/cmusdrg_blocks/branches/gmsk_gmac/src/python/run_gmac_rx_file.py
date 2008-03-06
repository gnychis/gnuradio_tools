#!/usr/bin/env python
from gnuradio import usrp
import gnuradio.gr.gr_threading as _threading
from gnuradio import cmusdrg
import sys

# Ideally, this is a Python thread that will be used to give control to C++
# while keeping the Python alive
class cpp_thread(_threading.Thread):
    def __init__(self, mblock_bootstrap):
        _threading.Thread.__init__(self)
        self.mblock_bootstrap = mblock_bootstrap
        self.keep_running = True

    def run(self):
        self.mblock_bootstrap.start()
        while self.keep_running:
            self.mblock_bootstrap.packet()

# DEBUG
def DEBUG(s):
    print s
    sys.stdout.flush()

def setup_usrp(freq):

  # Constants
  interp = 128
  decim = 64
  
  # Make USRP instances to TX and RX
  utx = usrp.sink_c(fpga_filename="std_inband.rbf")
  urx = usrp.source_c(fpga_filename="std_inband.rbf")

  # Set decim and interp rates
  utx.set_interp_rate(interp)
  urx.set_decim_rate(decim)

  # Pick subdevice
  subdev_spec_tx = usrp.pick_tx_subdevice(utx)
  subdev_spec_rx = usrp.pick_rx_subdevice(urx)

  # Set up mux
  mux_tx = usrp.determine_tx_mux_value(utx, subdev_spec_tx)
  mux_rx = usrp.determine_rx_mux_value(urx, subdev_spec_rx)
  utx.set_mux(mux_tx)
  urx.set_mux(mux_rx)

  # pick d'board
  subdev_tx = usrp.selected_subdev(utx, subdev_spec_tx)
  subdev_rx = usrp.selected_subdev(urx, subdev_spec_rx)
  DEBUG( "Using TX d'board %s" %(subdev_tx.side_and_name()))
  DEBUG( "Using RX d'board %s" %(subdev_rx.side_and_name()))

  # Gain
  subdev_tx.set_gain((subdev_tx.gain_range()[0] + subdev_tx.gain_range()[1]) / 2)
  subdev_rx.set_gain((subdev_rx.gain_range()[0] + subdev_rx.gain_range()[1]) / 2)

  # Tune
  if not utx.tune(subdev_tx._which, subdev_tx, freq):
      DEBUG( "error tuning TX")
  if not urx.tune(subdev_rx._which, subdev_rx, freq):
      DEBUG( "error tuning RX")

  # Power on
  subdev_tx.set_enable(True)
  subdev_rx.set_enable(True)
  DEBUG("USRP is on!")
  sys.stdout.flush()

  return utx, urx

def run(freq, args):

  (utx, urx) = setup_usrp(freq)

  # First, get the current USRP
  usrp_tx = utx.get_usrp()
  usrp_rx = urx.get_usrp()

  # Now make a mblock_bootstrap
  mblock_bootstrap = cmusdrg.mblock_bootstrap(usrp_tx, usrp_rx, "gmac_rx_file", len(args), args)
  DEBUG("Got USRP_ref object")

  # Now start a new thread for it
  DEBUG("Creating mblock_bootstrap_thread")
  mblock_bootstrap_thread = cpp_thread(mblock_bootstrap)

  # Start the thread
  DEBUG("Starting mblock_bootstrap_thread")
  mblock_bootstrap_thread.start()
  DEBUG("\t.. started")

  try:
      while True:
          time.slep(1);
          pass
  except KeyboardInterrupt:
      mblock_bootstrap_thread.keep_running = False
      DEBUG("Stopping")


def main (args):
  nargs = len(args)
  if nargs >= 4:
    freq = int(args[0])
    filename = args[1]
    saddr = int(args[2])
    daddr = int(args[3])
  else:
    sys.stderr.write ("usage: ./run_gmac_rx_file.py if_freq output_file src_addr dst_addr\n")
    sys.exit (1)

  run(freq, sys.argv[2:])

if __name__ == '__main__':
  main(sys.argv[1:])

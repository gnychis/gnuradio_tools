#!/usr/bin/env python
from gnuradio import usrp
import gnuradio.gr.gr_threading as _threading
from gnuradio import dhalperi
import sys

#############################################################################
#
# Ideally, this is a Python thread that will be used to give control to C++
# while keeping the Python alive
#
######
#
class cpp_thread(_threading.Thread):
    def __init__(self, usrp_ref):
        _threading.Thread.__init__(self)
        self.usrp_ref = usrp_ref
        self.keep_running = True

    def run(self):
        self.usrp_ref.start()
        while self.keep_running:
            self.usrp_ref.packet()
#############################################################################

#############################################################################
#
# DEBUG
#
#######
def DEBUG(s):
    print s
    sys.stdout.flush()

#############################################################################

############################################################################
#
# Normal stuff -- setup USRP
#
######
#
# Constants
interp = 16
freq = 2.425e9
# Make USRP, set interp
u = usrp.sink_c(fpga_filename="std_inband.rbf")
u.set_interp_rate(interp)
# Pick subdevice
subdev_spec = usrp.pick_tx_subdevice(u)
# Set up mux
mux = usrp.determine_tx_mux_value(u, subdev_spec)
u.set_mux(mux)
# pick d'board
subdev = usrp.selected_subdev(u, subdev_spec)
DEBUG( "Using TX d'board %s" %(subdev.side_and_name()))
# Gain
subdev.set_gain((subdev.gain_range()[0] + subdev.gain_range()[1]) / 2)
# Tune
if not u.tune(subdev._which, subdev, freq):
    DEBUG( "error tuning")
# Power on
subdev.set_enable(True)
DEBUG("USRP is on!")
sys.stdout.flush()
############################################################################

############################################################################
#
# Here is where life gets crazy!
#
######
#
# First, get the current USRP
usrp = u.get_usrp()
# Now make a usrp_ref
usrp_ref = dhalperi.usrp_ref(usrp)
DEBUG("Got USRP_ref object")
# Now start a new thread for it
DEBUG("Creating usrp_ref_thread")
usrp_ref_thread = cpp_thread(usrp_ref)
DEBUG("Starting usrp_ref_thread")
usrp_ref_thread.start()
DEBUG("\t.. started")
try:
    while True:
        time.slep(1);
        pass
except KeyboardInterrupt:
    usrp_ref_thread.keep_running = False
    DEBUG("Stopping")

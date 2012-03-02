#!/usr/bin/env python

from gnuradio import gr
from gnuradio import audio

class my_top_block(gr.top_block):
    def __init__(self):
        gr.top_block.__init__(self)

        sample_rate = 32000
        ampl = 0.1

        self._fft_length=96
        
        win = [] 
        win2 = [1 for i in range(self._fft_length)]

        # Constructing a sine source and the fft blocks
        ##src0 = gr.sig_source_c (sample_rate, gr.GR_SIN_WAVE, 350, ampl)
	src0 = gr.file_source(gr.sizeof_gr_complex*self._fft_length, "symbols_src.dat")
        ifft = gr.fft_vcc(self._fft_length, False, win, True)
        fft_demod = gr.fft_vcc(self._fft_length, True, win2, True)
        
        # Some output data files
        trans_output = gr.file_sink(gr.sizeof_gr_complex, "trans_output.dat")
        ##reg_output = gr.file_sink(gr.sizeof_gr_complex, "reg_output.dat")

        # Connect the blocks
        ##self.connect(src0, reg_output)

	# just compare the <symbols_src.dat> and <trans_output.dat> #
        self.connect(src0, fft_demod, ifft, trans_output)

if __name__ == '__main__':
    try:
        my_top_block().run()
    except [[KeyboardInterrupt]]:
        pass

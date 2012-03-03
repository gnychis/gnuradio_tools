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
        #win = [1 for i in range(self._fft_length)]
        win2 = [1 for i in range(self._fft_length)]

        # Constructing a sine source and the fft blocks
        src0 = gr.sig_source_c (sample_rate, gr.GR_SIN_WAVE, 350, ampl)
        ss2v = gr.stream_to_vector(gr.sizeof_gr_complex, self._fft_length)
        sv2s = gr.vector_to_stream(gr.sizeof_gr_complex, self._fft_length)
        fft_demod = gr.fft_vcc(self._fft_length, True, win2, False)
        ifft = gr.fft_vcc(self._fft_length, False, win, False)
        scale = gr.multiply_const_cc(1.0 / self._fft_length)
        
        # Some output data files
        trans_output = gr.file_sink(gr.sizeof_gr_complex, "trans_output.dat")
        reg_output = gr.file_sink(gr.sizeof_gr_complex, "reg_output.dat")

        # make the connections #
        self.connect(src0, ss2v, fft_demod, ifft, sv2s, scale, trans_output)
        self.connect(src0, reg_output)

if __name__ == '__main__':
    try:
        my_top_block().run()
    except [[KeyboardInterrupt]]:
        pass

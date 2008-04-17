/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "cmusdrg_acquisition_filter_ccc.h"
#include <stdexcept>
%}

// ----------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(cmusdrg,acquisition_filter_ccc);

cmusdrg_acquisition_filter_ccc_sptr cmusdrg_make_acquisition_filter_ccc (long threshold, long window);

class cmusdrg_acquisition_filter_ccc : public gr_block
{
private:
  cmusdrg_acquisition_filter_ccc (long threshold, long window);
};

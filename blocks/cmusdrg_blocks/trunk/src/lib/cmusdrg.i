/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "mfilteropt_ccc.h"
#include <stdexcept>
%}

// ----------------------------------------------------------------

/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access mfilteropt_ccc from python as cmusdrg.mfilteropt_ccc
 */
GR_SWIG_BLOCK_MAGIC(cmusdrg,mfilteropt_ccc);

mfilteropt_ccc_sptr cmusdrg_make_mfilteropt_ccc ();

class mfilteropt_ccc : public gr_block
{
private:
  mfilteropt_ccc ();
};

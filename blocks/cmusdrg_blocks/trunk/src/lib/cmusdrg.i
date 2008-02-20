/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "cmusdrg_mfilteropt_ccc.h"
#include <stdexcept>
%}

// ----------------------------------------------------------------

/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access cmusdrg_mfilteropt_ccc from python as cmusdrg.mfilteropt_ccc
 */
GR_SWIG_BLOCK_MAGIC(cmusdrg,mfilteropt_ccc);

cmusdrg_mfilteropt_ccc_sptr cmusdrg_make_mfilteropt_ccc ();

class cmusdrg_mfilteropt_ccc : public gr_block
{
private:
  cmusdrg_mfilteropt_ccc ();
};

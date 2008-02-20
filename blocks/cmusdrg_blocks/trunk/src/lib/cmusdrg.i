/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
//#include "cmusdrg_mfilteropt_ccc.h"
#include <stdexcept>
%}

// ----------------------------------------------------------------

//GR_SWIG_BLOCK_MAGIC(cmusdrg,mfilteropt_ccc);
//
//cmusdrg_mfilteropt_ccc_sptr cmusdrg_make_mfilteropt_ccc ();
//
//class cmusdrg_mfilteropt_ccc : public gr_block
//{
//private:
//  cmusdrg_mfilteropt_ccc ();
//};

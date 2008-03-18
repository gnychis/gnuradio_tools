/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "cmusdrg_mblock_bootstrap.h"
#include <stdexcept>
%}

%include "cmusdrg_mblock_bootstrap.i"

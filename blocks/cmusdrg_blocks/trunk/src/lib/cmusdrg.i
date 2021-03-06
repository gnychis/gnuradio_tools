/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix
#include "cmusdrg_acquisition_filter_ccc.h"
#include "cmusdrg_mf_sync_ccf.h"
#include "cmusdrg_print_samples_cc.h"
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

// ----------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(cmusdrg,mf_sync_ccf);

cmusdrg_mf_sync_ccf_sptr cmusdrg_make_mf_sync_ccf (const std::vector<gr_complex> &coeffs);

class cmusdrg_mf_sync_ccf : public gr_block
{
private:
  cmusdrg_mf_sync_ccf (const std::vector<gr_complex> &coeffs);
};

// ----------------------------------------------------------------

GR_SWIG_BLOCK_MAGIC(cmusdrg,print_samples_cc);

cmusdrg_print_samples_cc_sptr cmusdrg_make_print_samples_cc ();

class cmusdrg_print_samples_cc : public gr_block
{
private:
  cmusdrg_print_samples_cc ();
};


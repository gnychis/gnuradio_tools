#
# Copyright 2004,2005,2006,2008 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 51 Franklin Street,
# Boston, MA 02110-1301, USA.
# 

include $(top_srcdir)/Makefile.common

# Install this stuff so that it ends up as the gnuradio.cmusdrg module
# This usually ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/gnuradio

ourpythondir = $(grpythondir)
ourlibdir    = $(grpyexecdir)

INCLUDES = $(STD_DEFINES_AND_INCLUDES) $(PYTHON_CPPFLAGS) $(WITH_INCLUDES)

SWIGPYTHONARGS = $(SWIGPYTHONFLAGS) $(SWIGGRFLAGS) $(WITH_SWIG_INCLUDES) \
	$(WITH_INCLUDES)

ALL_IFILES = 				\
	$(LOCAL_IFILES)			\
	$(NON_LOCAL_IFILES)		

NON_LOCAL_IFILES =			\
	$(GNURADIO_CORE_INCLUDEDIR)/swig/gnuradio.i


LOCAL_IFILES = 				\
	$(top_srcdir)/src/lib/cmusdrg.i				

EXTRA_DIST = 		\
	cmac.mbh

#GUILE_LOAD_PATH="../scheme/pmt:../scheme/mblock" /usr/bin/guile -e main -s ../scheme/mblock/gnuradio/compile-mbh.scm ./cmac.mbh cmac_mbh.cc

GUILE_LOAD_PATH=GUILE_LOAD_PATH="$(top_srcdir)/src/scheme/pmt:$(top_srcdir)/src/scheme/mblock"
GUILE=/usr/bin/guile -e main -s $(top_srcdir)/src/scheme/mblock/gnuradio/compile-mbh.scm

# These files are built by SWIG.  The first is the C++ glue.
# The second is the python wrapper that loads the _cmusdrg shared library
# and knows how to call our extensions.

BUILT_SOURCES = 			\
	cmusdrg.cc			\
	cmusdrg.py			\
	cmac_mbh.cc

cmac_mbh.cc : cmac.mbh
	$(GUILE_LOAD_PATH) $(GUILE) $(srcdir)/cmac.mbh $(srcdir)/cmac_mbh.cc

# This gets cmusdrg.py installed in the right place
ourpython_PYTHON =			\
	cmusdrg.py

ourlib_LTLIBRARIES = _cmusdrg.la

# These are the source files that go into the shared library
_cmusdrg_la_SOURCES = 			\
	cmusdrg.cc	\
	cmusdrg_mblock_bootstrap.cc	\
	mac.cc \
	cmac.cc	\
	gmsk.cc	\
	gmsk_framer.cc \
	cmac_mbh.cc	\
	gmsk_mbh.cc	\
	cmac_tx_file.cc	\
	cmac_rx_file.cc

# magic flags
_cmusdrg_la_LDFLAGS = $(NO_UNDEFINED) -module -avoid-version

# link the library against some comon swig runtime code and the 
# c++ standard library
_cmusdrg_la_LIBADD = 			\
	$(PYTHON_LDFLAGS)		\
	$(USRP_LA)	\
	$(GNURADIO_CORE_LA)	\
	-lstdc++	\
	-lusrp	\
	-lusrp_inband	\
	-lmblock

cmusdrg.cc cmusdrg.py: $(LOCAL_IFILES) $(ALL_IFILES)
	$(SWIG) $(SWIGPYTHONARGS) -module cmusdrg -o cmusdrg.cc $(LOCAL_IFILES)

# These headers get installed in ${prefix}/include/gnuradio
grinclude_HEADERS =			\
	cmusdrg_mblock_bootstrap.h	\
	mac.h \
	cmac.h	\
	gmsk.h	\
	gmsk_framer.h


# These swig headers get installed in ${prefix}/include/gnuradio/swig
swiginclude_HEADERS = 			\
	$(LOCAL_IFILES)	\
	cmusdrg_mblock_bootstrap.i


MOSTLYCLEANFILES = $(BUILT_SOURCES) *.pyc

# Don't distribute output of swig
dist-hook:
	@for file in $(BUILT_SOURCES); do echo $(RM) $(distdir)/$$file; done
	@for file in $(BUILT_SOURCES); do $(RM) $(distdir)/$$file; done

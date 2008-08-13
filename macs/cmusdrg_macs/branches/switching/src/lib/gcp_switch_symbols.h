/* -*- c++ -*- */
/*
 * Copyright 2007 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#ifndef INCLUDED_SWITCH_SYMBOLS_H
#define INCLUDED_SWITCH_SYMBOLS_H

#include <pmt.h>

static pmt_t s_cmd_connect_macs = pmt_intern("cmd-connect-macs");
static pmt_t s_response_connect_macs = pmt_intern("response-connect-macs");

static pmt_t s_cmd_switch_mac = pmt_intern("cmd-switch-mac");
static pmt_t s_response_switch_mac = pmt_intern("response-switch-mac");

static pmt_t s_cmd_change_mac_parameters = pmt_intern("cmd-change-mac-parameters");
static pmt_t s_response_change_mac_parameters = pmt_intern("response-change-mac-parameters");

#endif

                              1 	.include "../common/_startup.a51"
                              1 ;;; -*- asm -*-
                              2 ;;;
                              3 ;;; Copyright 2003,2004 Free Software Foundation, Inc.
                              4 ;;; 
                              5 ;;; This file is part of GNU Radio
                              6 ;;; 
                              7 ;;; GNU Radio is free software; you can redistribute it and/or modify
                              8 ;;; it under the terms of the GNU General Public License as published by
                              9 ;;; the Free Software Foundation; either version 3, or (at your option)
                             10 ;;; any later version.
                             11 ;;; 
                             12 ;;; GNU Radio is distributed in the hope that it will be useful,
                             13 ;;; but WITHOUT ANY WARRANTY; without even the implied warranty of
                             14 ;;; MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
                             15 ;;; GNU General Public License for more details.
                             16 ;;; 
                             17 ;;; You should have received a copy of the GNU General Public License
                             18 ;;; along with GNU Radio; see the file COPYING.  If not, write to
                             19 ;;; the Free Software Foundation, Inc., 51 Franklin Street,
                             20 ;;; Boston, MA 02110-1301, USA.
                             21 
                             22     
                             23 ;;; The default external memory initialization provided by sdcc is not
                             24 ;;; appropriate to the FX2.  This is derived from the sdcc code, but uses 
                             25 ;;; the FX2 specific _MPAGE sfr.
                             26 
                             27 
                             28 	;; .area XISEG   (XDATA)  ; the initialized external data area
                             29 	;; .area XINIT   (CODE)	  ; the code space consts to init XISEG
                             30 	.area XSEG    (XDATA)	  ; zero initialized xdata
                             31 	.area USBDESCSEG (XDATA)  ; usb descriptors
                             32 
                             33 	
                             34 	.area CSEG    (CODE)
                             35 
                             36 	;; sfr that sets upper address byte of MOVX using @r0 or @r1
                    0092     37 	_MPAGE	=	0x0092
                             38 
   0A34                      39 __sdcc_external_startup::
                             40 	;; This system is now compiled with the --no-xinit-opt 
                             41 	;; which means that any initialized XDATA is handled
                             42 	;; inline by code in the GSINIT segs emitted for each file.
                             43 	;; 
                             44 	;; We zero XSEG and all of the internal ram to ensure 
                             45 	;; a known good state for uninitialized variables.
                             46 
                             47 ;	_mcs51_genRAMCLEAR() start
   0A34 78 0F                48 	mov	r0,#l_XSEG
   0A36 E8                   49 	mov	a,r0
   0A37 44 00                50 	orl	a,#(l_XSEG >> 8)
   0A39 60 0C                51 	jz	00002$
   0A3B 79 01                52 	mov	r1,#((l_XSEG + 255) >> 8)
   0A3D 90 18 00             53 	mov	dptr,#s_XSEG
   0A40 E4                   54 	clr     a
                             55 	
   0A41 F0                   56 00001$:	movx	@dptr,a
   0A42 A3                   57 	inc	dptr
   0A43 D8 FC                58 	djnz	r0,00001$
   0A45 D9 FA                59 	djnz	r1,00001$
                             60 	
                             61 	;; We're about to clear internal memory.  This will overwrite
                             62 	;; the stack which contains our return address.
                             63 	;; Pop our return address into DPH, DPL
   0A47 D0 83                64 00002$:	pop	dph
   0A49 D0 82                65 	pop	dpl
                             66 	
                             67 	;; R0 and A contain 0.  This loop will execute 256 times.
                             68 	;; 
                             69 	;; FWIW the first iteration writes direct address 0x00,
                             70 	;; which is the location of r0.  We get lucky, we're 
                             71 	;; writing the correct value (0)
                             72 	
   0A4B F6                   73 00003$:	mov	@r0,a
   0A4C D8 FD                74 	djnz	r0,00003$
                             75 
   0A4E C0 82                76 	push	dpl		; restore our return address
   0A50 C0 83                77 	push	dph
                             78 
   0A52 75 82 00             79 	mov	dpl,#0		; indicate that data init is still required
   0A55 22                   80 	ret

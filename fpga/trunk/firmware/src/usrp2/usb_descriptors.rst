                              1 ;;; -*- asm -*-
                              2 ;;;
                              3 ;;; Copyright 2003 Free Software Foundation, Inc.
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
                             21 ;;;
                             22 	
                             23 ;;; USB Descriptor table for the USRP
                             24 ;;; 
                             25 ;;; We're a high-speed only device (480 Mb/sec) with 1 configuration
                             26 ;;; and 3 interfaces.  
                             27 ;;; 
                             28 ;;;	interface 0:	command and status (ep0 COMMAND)
                             29 ;;;	interface 1:	Transmit path (ep2 OUT BULK)
                             30 ;;;	interface 2:	Receive path (ep6 IN BULK)
                             31 
                             32 	.module usb_descriptors
                             33 	
                    FFFE     34 	VID_FREE	 = 0xfffe	; Free Software Folks
                    0002     35 	PID_USRP	 = 0x0002	; USRP
                             36 
                             37 	;; We distinguish configured from unconfigured USRPs using the Device ID.
                             38 	;; If the MSB of the DID is 0, the device is unconfigured.
                             39 	;; The LSB of the DID is reserved for hardware revs.
                             40 	
                    0100     41 	DID_USRP	 = 0x0100	; Device ID (bcd)
                             42 
                             43 	
                    0001     44 	DSCR_DEVICE	 =   1	; Descriptor type: Device
                    0002     45 	DSCR_CONFIG	 =   2	; Descriptor type: Configuration
                    0003     46 	DSCR_STRING	 =   3	; Descriptor type: String
                    0004     47 	DSCR_INTRFC	 =   4	; Descriptor type: Interface
                    0005     48 	DSCR_ENDPNT	 =   5	; Descriptor type: Endpoint
                    0006     49 	DSCR_DEVQUAL	 =   6	; Descriptor type: Device Qualifier
                             50 	
                    0012     51 	DSCR_DEVICE_LEN	 =  18
                    0009     52 	DSCR_CONFIG_LEN  =   9
                    0009     53 	DSCR_INTRFC_LEN  =   9
                    0007     54 	DSCR_ENDPNT_LEN  =   7
                    000A     55 	DSCR_DEVQUAL_LEN =  10
                             56 	
                    0000     57 	ET_CONTROL	 =   0	; Endpoint type: Control
                    0001     58 	ET_ISO		 =   1	; Endpoint type: Isochronous
                    0002     59 	ET_BULK		 =   2	; Endpoint type: Bulk
                    0003     60 	ET_INT		 =   3	; Endpoint type: Interrupt
                             61 	
                             62 	
                             63 	;; configuration attributes
                    0040     64 	bmSELF_POWERED	=	1 << 6
                             65 
                             66 ;;; --------------------------------------------------------
                             67 ;;;	external ram data
                             68 ;;;--------------------------------------------------------
                             69 	
                             70 	.area USBDESCSEG    (XDATA)
                             71 	
                             72 ;;; ----------------------------------------------------------------
                             73 ;;; descriptors used when operating at high speed (480Mb/sec)
                             74 ;;; ----------------------------------------------------------------
                             75 	
   E000                      76 	.even	; descriptors must be 2-byte aligned for SUDPTR{H,L} to work
                             77 
                             78 	;; The .even directive isn't really honored by the linker.  Bummer!
                             79 	;; (There's no way to specify an alignment requirement for a given area,
                             80 	;; hence when they're concatenated together, even doesn't work.)
                             81 	;; 
                             82 	;; We work around this by telling the linker to put USBDESCSEG
                             83 	;; at 0xE000 absolute.  This means that the maximimum length of this
                             84 	;; segment is 480 bytes, leaving room for the two hash slots 
                             85 	;; at 0xE1EO to 0xE1FF.  
                             86 	;; 
                             87 	;; As of July 7, 2004, this segment is 326 bytes long
                             88 	
   E000                      89 _high_speed_device_descr::
   E000 12                   90 	.db	DSCR_DEVICE_LEN
   E001 01                   91 	.db	DSCR_DEVICE
   E002 00                   92 	.db	<0x0200		; Specification version (LSB)
   E003 02                   93 	.db	>0x0200		; Specification version (MSB)
   E004 FF                   94 	.db	0xff		; device class (vendor specific)
   E005 FF                   95 	.db	0xff		; device subclass (vendor specific)
   E006 FF                   96 	.db	0xff		; device protocol (vendor specific)
   E007 40                   97 	.db	64		; bMaxPacketSize0 for endpoint 0
   E008 FE                   98 	.db	<VID_FREE	; idVendor
   E009 FF                   99 	.db	>VID_FREE	; idVendor
   E00A 02                  100 	.db	<PID_USRP	; idProduct
   E00B 00                  101 	.db	>PID_USRP	; idProduct
   E00C                     102 _usb_desc_hw_rev_binary_patch_location_0::
   E00C 00                  103 	.db	<DID_USRP	; bcdDevice
   E00D 01                  104 	.db	>DID_USRP	; bcdDevice
   E00E 01                  105 	.db	SI_VENDOR	; iManufacturer (string index)
   E00F 02                  106 	.db	SI_PRODUCT	; iProduct (string index)
   E010 06                  107 	.db	SI_SERIAL	; iSerial number (string index)
   E011 01                  108 	.db	1		; bNumConfigurations
                            109 	
                            110 ;;; describes the other speed (12Mb/sec)
   E012                     111 	.even
   E012                     112 _high_speed_devqual_descr::
   E012 0A                  113 	.db	DSCR_DEVQUAL_LEN
   E013 06                  114 	.db	DSCR_DEVQUAL
   E014 00                  115 	.db	<0x0200		; bcdUSB (LSB)
   E015 02                  116 	.db	>0x0200		; bcdUSB (MSB)
   E016 FF                  117 	.db	0xff		; bDeviceClass
   E017 FF                  118 	.db	0xff		; bDeviceSubClass
   E018 FF                  119 	.db	0xff		; bDeviceProtocol
   E019 40                  120 	.db	64		; bMaxPacketSize0
   E01A 01                  121 	.db	1		; bNumConfigurations (one config at 12Mb/sec)
   E01B 00                  122 	.db	0		; bReserved
                            123 	
   E01C                     124 	.even
   E01C                     125 _high_speed_config_descr::	
   E01C 09                  126 	.db	DSCR_CONFIG_LEN
   E01D 02                  127 	.db	DSCR_CONFIG
   E01E 32                  128 	.db	<(_high_speed_config_descr_end - _high_speed_config_descr) ; LSB
   E01F 00                  129 	.db	>(_high_speed_config_descr_end - _high_speed_config_descr) ; MSB
   E020 03                  130 	.db	3		; bNumInterfaces
   E021 01                  131 	.db	1		; bConfigurationValue
   E022 00                  132 	.db	0		; iConfiguration
   E023 C0                  133 	.db	0x80 | bmSELF_POWERED ; bmAttributes
   E024 00                  134 	.db	0		; bMaxPower
                            135 
                            136 	;; interface descriptor 0 (command & status, ep0 COMMAND)
                            137 	
   E025 09                  138 	.db	DSCR_INTRFC_LEN
   E026 04                  139 	.db	DSCR_INTRFC
   E027 00                  140 	.db	0		; bInterfaceNumber (zero based)
   E028 00                  141 	.db	0		; bAlternateSetting
   E029 00                  142 	.db	0		; bNumEndpoints
   E02A FF                  143 	.db	0xff		; bInterfaceClass (vendor specific)
   E02B FF                  144 	.db	0xff		; bInterfaceSubClass (vendor specific)
   E02C FF                  145 	.db	0xff		; bInterfaceProtocol (vendor specific)
   E02D 03                  146 	.db	SI_COMMAND_AND_STATUS	; iInterface (description)
                            147 
                            148 	;; interface descriptor 1 (transmit path, ep2 OUT BULK)
                            149 	
   E02E 09                  150 	.db	DSCR_INTRFC_LEN
   E02F 04                  151 	.db	DSCR_INTRFC
   E030 01                  152 	.db	1		; bInterfaceNumber (zero based)
   E031 00                  153 	.db	0		; bAlternateSetting
   E032 01                  154 	.db	1		; bNumEndpoints
   E033 FF                  155 	.db	0xff		; bInterfaceClass (vendor specific)
   E034 FF                  156 	.db	0xff		; bInterfaceSubClass (vendor specific)
   E035 FF                  157 	.db	0xff		; bInterfaceProtocol (vendor specific)
   E036 04                  158 	.db	SI_TX_PATH	; iInterface (description)
                            159 
                            160 	;; interface 1's end point
                            161 
   E037 07                  162 	.db	DSCR_ENDPNT_LEN
   E038 05                  163 	.db	DSCR_ENDPNT
   E039 02                  164 	.db	0x02		; bEndpointAddress (ep 2 OUT)
   E03A 02                  165 	.db	ET_BULK		; bmAttributes
   E03B 00                  166 	.db	<512		; wMaxPacketSize (LSB)
   E03C 02                  167 	.db	>512		; wMaxPacketSize (MSB)
   E03D 00                  168 	.db	0		; bInterval (iso only)
                            169 
                            170 	;; interface descriptor 2 (receive path, ep6 IN BULK)
                            171 	
   E03E 09                  172 	.db	DSCR_INTRFC_LEN
   E03F 04                  173 	.db	DSCR_INTRFC
   E040 02                  174 	.db	2		; bInterfaceNumber (zero based)
   E041 00                  175 	.db	0		; bAlternateSetting
   E042 01                  176 	.db	1		; bNumEndpoints
   E043 FF                  177 	.db	0xff		; bInterfaceClass (vendor specific)
   E044 FF                  178 	.db	0xff		; bInterfaceSubClass (vendor specific)
   E045 FF                  179 	.db	0xff		; bInterfaceProtocol (vendor specific)
   E046 05                  180 	.db	SI_RX_PATH	; iInterface (description)
                            181 
                            182 	;; interface 2's end point
                            183 
   E047 07                  184 	.db	DSCR_ENDPNT_LEN
   E048 05                  185 	.db	DSCR_ENDPNT
   E049 86                  186 	.db	0x86		; bEndpointAddress (ep 6 IN)
   E04A 02                  187 	.db	ET_BULK		; bmAttributes
   E04B 00                  188 	.db	<512		; wMaxPacketSize (LSB)
   E04C 02                  189 	.db	>512		; wMaxPacketSize (MSB)
   E04D 00                  190 	.db	0		; bInterval (iso only)
                            191 
   E04E                     192 _high_speed_config_descr_end:		
                            193 
                            194 ;;; ----------------------------------------------------------------
                            195 ;;; descriptors used when operating at full speed (12Mb/sec)
                            196 ;;; ----------------------------------------------------------------
                            197 
   E04E                     198 	.even
   E04E                     199 _full_speed_device_descr::	
   E04E 12                  200 	.db	DSCR_DEVICE_LEN
   E04F 01                  201 	.db	DSCR_DEVICE
   E050 00                  202 	.db	<0x0200		; Specification version (LSB)
   E051 02                  203 	.db	>0x0200		; Specification version (MSB)
   E052 FF                  204 	.db	0xff		; device class (vendor specific)
   E053 FF                  205 	.db	0xff		; device subclass (vendor specific)
   E054 FF                  206 	.db	0xff		; device protocol (vendor specific)
   E055 40                  207 	.db	64		; bMaxPacketSize0 for endpoint 0
   E056 FE                  208 	.db	<VID_FREE	; idVendor
   E057 FF                  209 	.db	>VID_FREE	; idVendor
   E058 02                  210 	.db	<PID_USRP	; idProduct
   E059 00                  211 	.db	>PID_USRP	; idProduct
   E05A                     212 _usb_desc_hw_rev_binary_patch_location_1::
   E05A 00                  213 	.db	<DID_USRP	; bcdDevice
   E05B 01                  214 	.db	>DID_USRP	; bcdDevice
   E05C 01                  215 	.db	SI_VENDOR	; iManufacturer (string index)
   E05D 02                  216 	.db	SI_PRODUCT	; iProduct (string index)
   E05E 00                  217 	.db	SI_NONE		; iSerial number (None)
   E05F 01                  218 	.db	1		; bNumConfigurations
                            219 	
                            220 	
                            221 ;;; describes the other speed (480Mb/sec)
   E060                     222 	.even
   E060                     223 _full_speed_devqual_descr::
   E060 0A                  224 	.db	DSCR_DEVQUAL_LEN
   E061 06                  225 	.db	DSCR_DEVQUAL
   E062 00                  226 	.db	<0x0200		; bcdUSB
   E063 02                  227 	.db	>0x0200		; bcdUSB
   E064 FF                  228 	.db	0xff		; bDeviceClass
   E065 FF                  229 	.db	0xff		; bDeviceSubClass
   E066 FF                  230 	.db	0xff		; bDeviceProtocol
   E067 40                  231 	.db	64		; bMaxPacketSize0
   E068 01                  232 	.db	1		; bNumConfigurations (one config at 480Mb/sec)
   E069 00                  233 	.db	0		; bReserved
                            234 	
   E06A                     235 	.even
   E06A                     236 _full_speed_config_descr::	
   E06A 09                  237 	.db	DSCR_CONFIG_LEN
   E06B 02                  238 	.db	DSCR_CONFIG
   E06C 12                  239 	.db	<(_full_speed_config_descr_end - _full_speed_config_descr) ; LSB
   E06D 00                  240 	.db	>(_full_speed_config_descr_end - _full_speed_config_descr) ; MSB
   E06E 01                  241 	.db	1		; bNumInterfaces
   E06F 01                  242 	.db	1		; bConfigurationValue
   E070 00                  243 	.db	0		; iConfiguration
   E071 C0                  244 	.db	0x80 | bmSELF_POWERED ; bmAttributes
   E072 00                  245 	.db	0		; bMaxPower
                            246 
                            247 	;; interface descriptor 0 (command & status, ep0 COMMAND)
                            248 	
   E073 09                  249 	.db	DSCR_INTRFC_LEN
   E074 04                  250 	.db	DSCR_INTRFC
   E075 00                  251 	.db	0		; bInterfaceNumber (zero based)
   E076 00                  252 	.db	0		; bAlternateSetting
   E077 00                  253 	.db	0		; bNumEndpoints
   E078 FF                  254 	.db	0xff		; bInterfaceClass (vendor specific)
   E079 FF                  255 	.db	0xff		; bInterfaceSubClass (vendor specific)
   E07A FF                  256 	.db	0xff		; bInterfaceProtocol (vendor specific)
   E07B 03                  257 	.db	SI_COMMAND_AND_STATUS	; iInterface (description)
                            258 	
   E07C                     259 _full_speed_config_descr_end:	
                            260 	
                            261 ;;; ----------------------------------------------------------------
                            262 ;;;			string descriptors
                            263 ;;; ----------------------------------------------------------------
                            264 
   E07C                     265 _nstring_descriptors::
   E07C 07                  266 	.db	(_string_descriptors_end - _string_descriptors) / 2
                            267 
   E07D                     268 _string_descriptors::
   E07D 8C E0               269 	.db	<str0, >str0
   E07F 92 E0               270 	.db	<str1, >str1
   E081 BA E0               271 	.db	<str2, >str2
   E083 D0 E0               272 	.db	<str3, >str3
   E085 F2 E0               273 	.db	<str4, >str4
   E087 0E E1               274 	.db	<str5, >str5
   E089 28 E1               275 	.db	<str6, >str6
   E08B                     276 _string_descriptors_end:
                            277 
                    0000    278 	SI_NONE = 0
                            279 	;; str0 contains the language ID's.
   E08C                     280 	.even
   E08C 06                  281 str0:	.db	str0_end - str0
   E08D 03                  282 	.db	DSCR_STRING
   E08E 00                  283 	.db	0
   E08F 00                  284 	.db	0
   E090 09                  285 	.db	<0x0409		; magic code for US English (LSB)
   E091 04                  286 	.db	>0x0409		; magic code for US English (MSB)
   E092                     287 str0_end:
                            288 
                    0001    289 	SI_VENDOR = 1
   E092                     290 	.even
   E092 28                  291 str1:	.db	str1_end - str1
   E093 03                  292 	.db	DSCR_STRING
   E094 46 00               293 	.db	'F, 0		; 16-bit unicode
   E096 72 00               294 	.db	'r, 0
   E098 65 00               295 	.db	'e, 0
   E09A 65 00               296 	.db	'e, 0
   E09C 20 00               297 	.db	' , 0
   E09E 53 00               298 	.db	'S, 0
   E0A0 6F 00               299 	.db	'o, 0
   E0A2 66 00               300 	.db	'f, 0
   E0A4 74 00               301 	.db	't, 0
   E0A6 77 00               302 	.db	'w, 0
   E0A8 61 00               303 	.db	'a, 0
   E0AA 72 00               304 	.db	'r, 0
   E0AC 65 00               305 	.db	'e, 0
   E0AE 20 00               306 	.db	' , 0
   E0B0 46 00               307 	.db	'F, 0
   E0B2 6F 00               308 	.db	'o, 0
   E0B4 6C 00               309 	.db	'l, 0
   E0B6 6B 00               310 	.db	'k, 0
   E0B8 73 00               311 	.db	's, 0
   E0BA                     312 str1_end:
                            313 
                    0002    314 	SI_PRODUCT = 2
   E0BA                     315 	.even
   E0BA 16                  316 str2:	.db	str2_end - str2
   E0BB 03                  317 	.db	DSCR_STRING
   E0BC 55 00               318 	.db	'U, 0
   E0BE 53 00               319 	.db	'S, 0
   E0C0 52 00               320 	.db	'R, 0
   E0C2 50 00               321 	.db	'P, 0
   E0C4 20 00               322 	.db	' , 0
   E0C6 52 00               323 	.db	'R, 0
   E0C8 65 00               324 	.db	'e, 0
   E0CA 76 00               325 	.db	'v, 0
   E0CC 20 00               326 	.db	' , 0
   E0CE                     327 _usb_desc_hw_rev_ascii_patch_location_0::
   E0CE 3F 00               328 	.db	'?, 0
   E0D0                     329 str2_end:
                            330 
                    0003    331 	SI_COMMAND_AND_STATUS = 3
   E0D0                     332 	.even
   E0D0 22                  333 str3:	.db	str3_end - str3
   E0D1 03                  334 	.db	DSCR_STRING
   E0D2 43 00               335 	.db	'C, 0
   E0D4 6F 00               336 	.db	'o, 0
   E0D6 6D 00               337 	.db	'm, 0
   E0D8 6D 00               338 	.db	'm, 0
   E0DA 61 00               339 	.db	'a, 0
   E0DC 6E 00               340 	.db	'n, 0
   E0DE 64 00               341 	.db	'd, 0
   E0E0 20 00               342 	.db	' , 0
   E0E2 26 00               343 	.db	'&, 0
   E0E4 20 00               344 	.db	' , 0
   E0E6 53 00               345 	.db	'S, 0
   E0E8 74 00               346 	.db	't, 0
   E0EA 61 00               347 	.db	'a, 0
   E0EC 74 00               348 	.db	't, 0
   E0EE 75 00               349 	.db	'u, 0
   E0F0 73 00               350 	.db	's, 0
   E0F2                     351 str3_end:
                            352 
                    0004    353 	SI_TX_PATH = 4
   E0F2                     354 	.even
   E0F2 1C                  355 str4:	.db	str4_end - str4
   E0F3 03                  356 	.db	DSCR_STRING
   E0F4 54 00               357 	.db	'T, 0
   E0F6 72 00               358 	.db	'r, 0
   E0F8 61 00               359 	.db	'a, 0
   E0FA 6E 00               360 	.db	'n, 0
   E0FC 73 00               361 	.db	's, 0
   E0FE 6D 00               362 	.db	'm, 0
   E100 69 00               363 	.db	'i, 0
   E102 74 00               364 	.db	't, 0
   E104 20 00               365 	.db	' , 0
   E106 50 00               366 	.db	'P, 0
   E108 61 00               367 	.db	'a, 0
   E10A 74 00               368 	.db	't, 0
   E10C 68 00               369 	.db	'h, 0
   E10E                     370 str4_end:
                            371 
                    0005    372 	SI_RX_PATH = 5
   E10E                     373 	.even
   E10E 1A                  374 str5:	.db	str5_end - str5
   E10F 03                  375 	.db	DSCR_STRING
   E110 52 00               376 	.db	'R, 0
   E112 65 00               377 	.db	'e, 0
   E114 63 00               378 	.db	'c, 0
   E116 65 00               379 	.db	'e, 0
   E118 69 00               380 	.db	'i, 0
   E11A 76 00               381 	.db	'v, 0
   E11C 65 00               382 	.db	'e, 0
   E11E 20 00               383 	.db	' , 0
   E120 50 00               384 	.db	'P, 0
   E122 61 00               385 	.db	'a, 0
   E124 74 00               386 	.db	't, 0
   E126 68 00               387 	.db	'h, 0
   E128                     388 str5_end:
                            389 
                    0006    390 	SI_SERIAL = 6
   E128                     391 	.even
   E128 12                  392 str6:	.db	str6_end - str6
   E129 03                  393 	.db	DSCR_STRING
   E12A                     394 _usb_desc_serial_number_ascii::
   E12A 33 00               395 	.db	'3, 0
   E12C 2E 00               396 	.db	'., 0
   E12E 31 00               397 	.db	'1, 0
   E130 34 00               398 	.db	'4, 0
   E132 31 00               399 	.db	'1, 0
   E134 35 00               400 	.db	'5, 0
   E136 39 00               401 	.db	'9, 0
   E138 33 00               402 	.db	'3, 0
   E13A                     403 str6_end:
                            404 

                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Nov 10 2006)
                              4 ; This file generated Wed Jan 23 16:41:20 2008
                              5 ;--------------------------------------------------------
                              6 	.module usrp_main
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _main
                             13 	.globl _patch_usb_descriptors
                             14 	.globl _isr_tick
                             15 	.globl _bitALTERA_DCLK
                             16 	.globl _bitALTERA_DATA0
                             17 	.globl _bitS_IN
                             18 	.globl _bitS_OUT
                             19 	.globl _bitS_CLK
                             20 	.globl _EIPX6
                             21 	.globl _EIPX5
                             22 	.globl _EIPX4
                             23 	.globl _PI2C
                             24 	.globl _PUSB
                             25 	.globl _EIEX6
                             26 	.globl _EIEX5
                             27 	.globl _EIEX4
                             28 	.globl _EI2C
                             29 	.globl _EIUSB
                             30 	.globl _SMOD1
                             31 	.globl _ERESI
                             32 	.globl _RESI
                             33 	.globl _INT6
                             34 	.globl _CY
                             35 	.globl _AC
                             36 	.globl _F0
                             37 	.globl _RS1
                             38 	.globl _RS0
                             39 	.globl _OV
                             40 	.globl _FL
                             41 	.globl _P
                             42 	.globl _TF2
                             43 	.globl _EXF2
                             44 	.globl _RCLK
                             45 	.globl _TCLK
                             46 	.globl _EXEN2
                             47 	.globl _TR2
                             48 	.globl _C_T2
                             49 	.globl _CP_RL2
                             50 	.globl _SM01
                             51 	.globl _SM11
                             52 	.globl _SM21
                             53 	.globl _REN1
                             54 	.globl _TB81
                             55 	.globl _RB81
                             56 	.globl _TI1
                             57 	.globl _RI1
                             58 	.globl _PS1
                             59 	.globl _PT2
                             60 	.globl _PS0
                             61 	.globl _PT1
                             62 	.globl _PX1
                             63 	.globl _PT0
                             64 	.globl _PX0
                             65 	.globl _EA
                             66 	.globl _ES1
                             67 	.globl _ET2
                             68 	.globl _ES0
                             69 	.globl _ET1
                             70 	.globl _EX1
                             71 	.globl _ET0
                             72 	.globl _EX0
                             73 	.globl _SM0
                             74 	.globl _SM1
                             75 	.globl _SM2
                             76 	.globl _REN
                             77 	.globl _TB8
                             78 	.globl _RB8
                             79 	.globl _TI
                             80 	.globl _RI
                             81 	.globl _TF1
                             82 	.globl _TR1
                             83 	.globl _TF0
                             84 	.globl _TR0
                             85 	.globl _IE1
                             86 	.globl _IT1
                             87 	.globl _IE0
                             88 	.globl _IT0
                             89 	.globl _SEL
                             90 	.globl _EIP
                             91 	.globl _B
                             92 	.globl _EIE
                             93 	.globl _ACC
                             94 	.globl _EICON
                             95 	.globl _PSW
                             96 	.globl _TH2
                             97 	.globl _TL2
                             98 	.globl _RCAP2H
                             99 	.globl _RCAP2L
                            100 	.globl _T2CON
                            101 	.globl _SBUF1
                            102 	.globl _SCON1
                            103 	.globl _GPIFSGLDATLNOX
                            104 	.globl _GPIFSGLDATLX
                            105 	.globl _GPIFSGLDATH
                            106 	.globl _GPIFTRIG
                            107 	.globl _EP01STAT
                            108 	.globl _IP
                            109 	.globl _OEE
                            110 	.globl _OED
                            111 	.globl _OEC
                            112 	.globl _OEB
                            113 	.globl _OEA
                            114 	.globl _IOE
                            115 	.globl _IOD
                            116 	.globl _AUTOPTRSETUP
                            117 	.globl _EP68FIFOFLGS
                            118 	.globl _EP24FIFOFLGS
                            119 	.globl _EP2468STAT
                            120 	.globl _IE
                            121 	.globl _INT4CLR
                            122 	.globl _INT2CLR
                            123 	.globl _IOC
                            124 	.globl _AUTODAT2
                            125 	.globl _AUTOPTRL2
                            126 	.globl _AUTOPTRH2
                            127 	.globl _AUTODAT1
                            128 	.globl _APTR1L
                            129 	.globl _APTR1H
                            130 	.globl _SBUF0
                            131 	.globl _SCON0
                            132 	.globl _MPAGE
                            133 	.globl _EXIF
                            134 	.globl _IOB
                            135 	.globl _CKCON
                            136 	.globl _TH1
                            137 	.globl _TH0
                            138 	.globl _TL1
                            139 	.globl _TL0
                            140 	.globl _TMOD
                            141 	.globl _TCON
                            142 	.globl _PCON
                            143 	.globl _DPS
                            144 	.globl _DPH1
                            145 	.globl _DPL1
                            146 	.globl _DPH
                            147 	.globl _DPL
                            148 	.globl _SP
                            149 	.globl _IOA
                            150 	.globl _hash1
                            151 	.globl _EP8FIFOBUF
                            152 	.globl _EP6FIFOBUF
                            153 	.globl _EP4FIFOBUF
                            154 	.globl _EP2FIFOBUF
                            155 	.globl _EP1INBUF
                            156 	.globl _EP1OUTBUF
                            157 	.globl _EP0BUF
                            158 	.globl _CT4
                            159 	.globl _CT3
                            160 	.globl _CT2
                            161 	.globl _CT1
                            162 	.globl _USBTEST
                            163 	.globl _TESTCFG
                            164 	.globl _DBUG
                            165 	.globl _UDMACRCQUAL
                            166 	.globl _UDMACRCL
                            167 	.globl _UDMACRCH
                            168 	.globl _GPIFHOLDAMOUNT
                            169 	.globl _FLOWSTBHPERIOD
                            170 	.globl _FLOWSTBEDGE
                            171 	.globl _FLOWSTB
                            172 	.globl _FLOWHOLDOFF
                            173 	.globl _FLOWEQ1CTL
                            174 	.globl _FLOWEQ0CTL
                            175 	.globl _FLOWLOGIC
                            176 	.globl _FLOWSTATE
                            177 	.globl _GPIFABORT
                            178 	.globl _GPIFREADYSTAT
                            179 	.globl _GPIFREADYCFG
                            180 	.globl _XGPIFSGLDATLNOX
                            181 	.globl _XGPIFSGLDATLX
                            182 	.globl _XGPIFSGLDATH
                            183 	.globl _EP8GPIFTRIG
                            184 	.globl _EP8GPIFPFSTOP
                            185 	.globl _EP8GPIFFLGSEL
                            186 	.globl _EP6GPIFTRIG
                            187 	.globl _EP6GPIFPFSTOP
                            188 	.globl _EP6GPIFFLGSEL
                            189 	.globl _EP4GPIFTRIG
                            190 	.globl _EP4GPIFPFSTOP
                            191 	.globl _EP4GPIFFLGSEL
                            192 	.globl _EP2GPIFTRIG
                            193 	.globl _EP2GPIFPFSTOP
                            194 	.globl _EP2GPIFFLGSEL
                            195 	.globl _GPIFTCB0
                            196 	.globl _GPIFTCB1
                            197 	.globl _GPIFTCB2
                            198 	.globl _GPIFTCB3
                            199 	.globl _GPIFADRL
                            200 	.globl _GPIFADRH
                            201 	.globl _GPIFCTLCFG
                            202 	.globl _GPIFIDLECTL
                            203 	.globl _GPIFIDLECS
                            204 	.globl _GPIFWFSELECT
                            205 	.globl _SETUPDAT
                            206 	.globl _SUDPTRCTL
                            207 	.globl _SUDPTRL
                            208 	.globl _SUDPTRH
                            209 	.globl _EP8FIFOBCL
                            210 	.globl _EP8FIFOBCH
                            211 	.globl _EP6FIFOBCL
                            212 	.globl _EP6FIFOBCH
                            213 	.globl _EP4FIFOBCL
                            214 	.globl _EP4FIFOBCH
                            215 	.globl _EP2FIFOBCL
                            216 	.globl _EP2FIFOBCH
                            217 	.globl _EP8FIFOFLGS
                            218 	.globl _EP6FIFOFLGS
                            219 	.globl _EP4FIFOFLGS
                            220 	.globl _EP2FIFOFLGS
                            221 	.globl _EP8CS
                            222 	.globl _EP6CS
                            223 	.globl _EP4CS
                            224 	.globl _EP2CS
                            225 	.globl _EP1INCS
                            226 	.globl _EP1OUTCS
                            227 	.globl _EP0CS
                            228 	.globl _EP8BCL
                            229 	.globl _EP8BCH
                            230 	.globl _EP6BCL
                            231 	.globl _EP6BCH
                            232 	.globl _EP4BCL
                            233 	.globl _EP4BCH
                            234 	.globl _EP2BCL
                            235 	.globl _EP2BCH
                            236 	.globl _EP1INBC
                            237 	.globl _EP1OUTBC
                            238 	.globl _EP0BCL
                            239 	.globl _EP0BCH
                            240 	.globl _FNADDR
                            241 	.globl _MICROFRAME
                            242 	.globl _USBFRAMEL
                            243 	.globl _USBFRAMEH
                            244 	.globl _TOGCTL
                            245 	.globl _WAKEUPCS
                            246 	.globl _SUSPEND
                            247 	.globl _USBCS
                            248 	.globl _XAUTODAT2
                            249 	.globl _XAUTODAT1
                            250 	.globl _I2CTL
                            251 	.globl _I2DAT
                            252 	.globl _I2CS
                            253 	.globl _PORTECFG
                            254 	.globl _PORTCCFG
                            255 	.globl _PORTACFG
                            256 	.globl _INTSETUP
                            257 	.globl _INT4IVEC
                            258 	.globl _INT2IVEC
                            259 	.globl _CLRERRCNT
                            260 	.globl _ERRCNTLIM
                            261 	.globl _USBERRIRQ
                            262 	.globl _USBERRIE
                            263 	.globl _GPIFIRQ
                            264 	.globl _GPIFIE
                            265 	.globl _EPIRQ
                            266 	.globl _EPIE
                            267 	.globl _USBIRQ
                            268 	.globl _USBIE
                            269 	.globl _NAKIRQ
                            270 	.globl _NAKIE
                            271 	.globl _IBNIRQ
                            272 	.globl _IBNIE
                            273 	.globl _EP8FIFOIRQ
                            274 	.globl _EP8FIFOIE
                            275 	.globl _EP6FIFOIRQ
                            276 	.globl _EP6FIFOIE
                            277 	.globl _EP4FIFOIRQ
                            278 	.globl _EP4FIFOIE
                            279 	.globl _EP2FIFOIRQ
                            280 	.globl _EP2FIFOIE
                            281 	.globl _OUTPKTEND
                            282 	.globl _INPKTEND
                            283 	.globl _EP8ISOINPKTS
                            284 	.globl _EP6ISOINPKTS
                            285 	.globl _EP4ISOINPKTS
                            286 	.globl _EP2ISOINPKTS
                            287 	.globl _EP8FIFOPFL
                            288 	.globl _EP8FIFOPFH
                            289 	.globl _EP6FIFOPFL
                            290 	.globl _EP6FIFOPFH
                            291 	.globl _EP4FIFOPFL
                            292 	.globl _EP4FIFOPFH
                            293 	.globl _EP2FIFOPFL
                            294 	.globl _EP2FIFOPFH
                            295 	.globl _EP8AUTOINLENL
                            296 	.globl _EP8AUTOINLENH
                            297 	.globl _EP6AUTOINLENL
                            298 	.globl _EP6AUTOINLENH
                            299 	.globl _EP4AUTOINLENL
                            300 	.globl _EP4AUTOINLENH
                            301 	.globl _EP2AUTOINLENL
                            302 	.globl _EP2AUTOINLENH
                            303 	.globl _EP8FIFOCFG
                            304 	.globl _EP6FIFOCFG
                            305 	.globl _EP4FIFOCFG
                            306 	.globl _EP2FIFOCFG
                            307 	.globl _EP8CFG
                            308 	.globl _EP6CFG
                            309 	.globl _EP4CFG
                            310 	.globl _EP2CFG
                            311 	.globl _EP1INCFG
                            312 	.globl _EP1OUTCFG
                            313 	.globl _REVCTL
                            314 	.globl _REVID
                            315 	.globl _FIFOPINPOLAR
                            316 	.globl _UART230
                            317 	.globl _BPADDRL
                            318 	.globl _BPADDRH
                            319 	.globl _BREAKPT
                            320 	.globl _FIFORESET
                            321 	.globl _PINFLAGSCD
                            322 	.globl _PINFLAGSAB
                            323 	.globl _IFCONFIG
                            324 	.globl _CPUCS
                            325 	.globl _RES_WAVEDATA_END
                            326 	.globl _GPIF_WAVE_DATA
                            327 	.globl _g_tx_underrun
                            328 	.globl _g_rx_overrun
                            329 	.globl _g_rx_enable
                            330 	.globl _g_tx_enable
                            331 	.globl _app_vendor_cmd
                            332 ;--------------------------------------------------------
                            333 ; special function registers
                            334 ;--------------------------------------------------------
                            335 	.area RSEG    (DATA)
                    0080    336 _IOA	=	0x0080
                    0081    337 _SP	=	0x0081
                    0082    338 _DPL	=	0x0082
                    0083    339 _DPH	=	0x0083
                    0084    340 _DPL1	=	0x0084
                    0085    341 _DPH1	=	0x0085
                    0086    342 _DPS	=	0x0086
                    0087    343 _PCON	=	0x0087
                    0088    344 _TCON	=	0x0088
                    0089    345 _TMOD	=	0x0089
                    008A    346 _TL0	=	0x008a
                    008B    347 _TL1	=	0x008b
                    008C    348 _TH0	=	0x008c
                    008D    349 _TH1	=	0x008d
                    008E    350 _CKCON	=	0x008e
                    0090    351 _IOB	=	0x0090
                    0091    352 _EXIF	=	0x0091
                    0092    353 _MPAGE	=	0x0092
                    0098    354 _SCON0	=	0x0098
                    0099    355 _SBUF0	=	0x0099
                    009A    356 _APTR1H	=	0x009a
                    009B    357 _APTR1L	=	0x009b
                    009C    358 _AUTODAT1	=	0x009c
                    009D    359 _AUTOPTRH2	=	0x009d
                    009E    360 _AUTOPTRL2	=	0x009e
                    009F    361 _AUTODAT2	=	0x009f
                    00A0    362 _IOC	=	0x00a0
                    00A1    363 _INT2CLR	=	0x00a1
                    00A2    364 _INT4CLR	=	0x00a2
                    00A8    365 _IE	=	0x00a8
                    00AA    366 _EP2468STAT	=	0x00aa
                    00AB    367 _EP24FIFOFLGS	=	0x00ab
                    00AC    368 _EP68FIFOFLGS	=	0x00ac
                    00AF    369 _AUTOPTRSETUP	=	0x00af
                    00B0    370 _IOD	=	0x00b0
                    00B1    371 _IOE	=	0x00b1
                    00B2    372 _OEA	=	0x00b2
                    00B3    373 _OEB	=	0x00b3
                    00B4    374 _OEC	=	0x00b4
                    00B5    375 _OED	=	0x00b5
                    00B6    376 _OEE	=	0x00b6
                    00B8    377 _IP	=	0x00b8
                    00BA    378 _EP01STAT	=	0x00ba
                    00BB    379 _GPIFTRIG	=	0x00bb
                    00BD    380 _GPIFSGLDATH	=	0x00bd
                    00BE    381 _GPIFSGLDATLX	=	0x00be
                    00BF    382 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    383 _SCON1	=	0x00c0
                    00C1    384 _SBUF1	=	0x00c1
                    00C8    385 _T2CON	=	0x00c8
                    00CA    386 _RCAP2L	=	0x00ca
                    00CB    387 _RCAP2H	=	0x00cb
                    00CC    388 _TL2	=	0x00cc
                    00CD    389 _TH2	=	0x00cd
                    00D0    390 _PSW	=	0x00d0
                    00D8    391 _EICON	=	0x00d8
                    00E0    392 _ACC	=	0x00e0
                    00E8    393 _EIE	=	0x00e8
                    00F0    394 _B	=	0x00f0
                    00F8    395 _EIP	=	0x00f8
                            396 ;--------------------------------------------------------
                            397 ; special function bits
                            398 ;--------------------------------------------------------
                            399 	.area RSEG    (DATA)
                    0086    400 _SEL	=	0x0086
                    0088    401 _IT0	=	0x0088
                    0089    402 _IE0	=	0x0089
                    008A    403 _IT1	=	0x008a
                    008B    404 _IE1	=	0x008b
                    008C    405 _TR0	=	0x008c
                    008D    406 _TF0	=	0x008d
                    008E    407 _TR1	=	0x008e
                    008F    408 _TF1	=	0x008f
                    0098    409 _RI	=	0x0098
                    0099    410 _TI	=	0x0099
                    009A    411 _RB8	=	0x009a
                    009B    412 _TB8	=	0x009b
                    009C    413 _REN	=	0x009c
                    009D    414 _SM2	=	0x009d
                    009E    415 _SM1	=	0x009e
                    009F    416 _SM0	=	0x009f
                    00A8    417 _EX0	=	0x00a8
                    00A9    418 _ET0	=	0x00a9
                    00AA    419 _EX1	=	0x00aa
                    00AB    420 _ET1	=	0x00ab
                    00AC    421 _ES0	=	0x00ac
                    00AD    422 _ET2	=	0x00ad
                    00AE    423 _ES1	=	0x00ae
                    00AF    424 _EA	=	0x00af
                    00B8    425 _PX0	=	0x00b8
                    00B9    426 _PT0	=	0x00b9
                    00BA    427 _PX1	=	0x00ba
                    00BB    428 _PT1	=	0x00bb
                    00BC    429 _PS0	=	0x00bc
                    00BD    430 _PT2	=	0x00bd
                    00BE    431 _PS1	=	0x00be
                    00C0    432 _RI1	=	0x00c0
                    00C1    433 _TI1	=	0x00c1
                    00C2    434 _RB81	=	0x00c2
                    00C3    435 _TB81	=	0x00c3
                    00C4    436 _REN1	=	0x00c4
                    00C5    437 _SM21	=	0x00c5
                    00C6    438 _SM11	=	0x00c6
                    00C7    439 _SM01	=	0x00c7
                    00C8    440 _CP_RL2	=	0x00c8
                    00C9    441 _C_T2	=	0x00c9
                    00CA    442 _TR2	=	0x00ca
                    00CB    443 _EXEN2	=	0x00cb
                    00CC    444 _TCLK	=	0x00cc
                    00CD    445 _RCLK	=	0x00cd
                    00CE    446 _EXF2	=	0x00ce
                    00CF    447 _TF2	=	0x00cf
                    00D0    448 _P	=	0x00d0
                    00D1    449 _FL	=	0x00d1
                    00D2    450 _OV	=	0x00d2
                    00D3    451 _RS0	=	0x00d3
                    00D4    452 _RS1	=	0x00d4
                    00D5    453 _F0	=	0x00d5
                    00D6    454 _AC	=	0x00d6
                    00D7    455 _CY	=	0x00d7
                    00DB    456 _INT6	=	0x00db
                    00DC    457 _RESI	=	0x00dc
                    00DD    458 _ERESI	=	0x00dd
                    00DF    459 _SMOD1	=	0x00df
                    00E8    460 _EIUSB	=	0x00e8
                    00E9    461 _EI2C	=	0x00e9
                    00EA    462 _EIEX4	=	0x00ea
                    00EB    463 _EIEX5	=	0x00eb
                    00EC    464 _EIEX6	=	0x00ec
                    00F8    465 _PUSB	=	0x00f8
                    00F9    466 _PI2C	=	0x00f9
                    00FA    467 _EIPX4	=	0x00fa
                    00FB    468 _EIPX5	=	0x00fb
                    00FC    469 _EIPX6	=	0x00fc
                    0080    470 _bitS_CLK	=	0x0080
                    0081    471 _bitS_OUT	=	0x0081
                    0082    472 _bitS_IN	=	0x0082
                    00A1    473 _bitALTERA_DATA0	=	0x00a1
                    00A3    474 _bitALTERA_DCLK	=	0x00a3
                            475 ;--------------------------------------------------------
                            476 ; overlayable register banks
                            477 ;--------------------------------------------------------
                            478 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     479 	.ds 8
                            480 ;--------------------------------------------------------
                            481 ; internal ram data
                            482 ;--------------------------------------------------------
                            483 	.area DSEG    (DATA)
   0008                     484 _g_tx_enable::
   0008                     485 	.ds 1
   0009                     486 _g_rx_enable::
   0009                     487 	.ds 1
   000A                     488 _g_rx_overrun::
   000A                     489 	.ds 1
   000B                     490 _g_tx_underrun::
   000B                     491 	.ds 1
   000C                     492 _isr_tick_count_1_1:
   000C                     493 	.ds 1
                            494 ;--------------------------------------------------------
                            495 ; overlayable items in internal ram 
                            496 ;--------------------------------------------------------
                            497 	.area OSEG    (OVR,DATA)
                            498 ;--------------------------------------------------------
                            499 ; Stack segment in internal ram 
                            500 ;--------------------------------------------------------
                            501 	.area	SSEG	(DATA)
   003F                     502 __start__stack:
   003F                     503 	.ds	1
                            504 
                            505 ;--------------------------------------------------------
                            506 ; indirectly addressable internal ram data
                            507 ;--------------------------------------------------------
                            508 	.area ISEG    (DATA)
                            509 ;--------------------------------------------------------
                            510 ; bit data
                            511 ;--------------------------------------------------------
                            512 	.area BSEG    (BIT)
                            513 ;--------------------------------------------------------
                            514 ; paged external ram data
                            515 ;--------------------------------------------------------
                            516 	.area PSEG    (PAG,XDATA)
                            517 ;--------------------------------------------------------
                            518 ; external ram data
                            519 ;--------------------------------------------------------
                            520 	.area XSEG    (XDATA)
                    E400    521 _GPIF_WAVE_DATA	=	0xe400
                    E480    522 _RES_WAVEDATA_END	=	0xe480
                    E600    523 _CPUCS	=	0xe600
                    E601    524 _IFCONFIG	=	0xe601
                    E602    525 _PINFLAGSAB	=	0xe602
                    E603    526 _PINFLAGSCD	=	0xe603
                    E604    527 _FIFORESET	=	0xe604
                    E605    528 _BREAKPT	=	0xe605
                    E606    529 _BPADDRH	=	0xe606
                    E607    530 _BPADDRL	=	0xe607
                    E608    531 _UART230	=	0xe608
                    E609    532 _FIFOPINPOLAR	=	0xe609
                    E60A    533 _REVID	=	0xe60a
                    E60B    534 _REVCTL	=	0xe60b
                    E610    535 _EP1OUTCFG	=	0xe610
                    E611    536 _EP1INCFG	=	0xe611
                    E612    537 _EP2CFG	=	0xe612
                    E613    538 _EP4CFG	=	0xe613
                    E614    539 _EP6CFG	=	0xe614
                    E615    540 _EP8CFG	=	0xe615
                    E618    541 _EP2FIFOCFG	=	0xe618
                    E619    542 _EP4FIFOCFG	=	0xe619
                    E61A    543 _EP6FIFOCFG	=	0xe61a
                    E61B    544 _EP8FIFOCFG	=	0xe61b
                    E620    545 _EP2AUTOINLENH	=	0xe620
                    E621    546 _EP2AUTOINLENL	=	0xe621
                    E622    547 _EP4AUTOINLENH	=	0xe622
                    E623    548 _EP4AUTOINLENL	=	0xe623
                    E624    549 _EP6AUTOINLENH	=	0xe624
                    E625    550 _EP6AUTOINLENL	=	0xe625
                    E626    551 _EP8AUTOINLENH	=	0xe626
                    E627    552 _EP8AUTOINLENL	=	0xe627
                    E630    553 _EP2FIFOPFH	=	0xe630
                    E631    554 _EP2FIFOPFL	=	0xe631
                    E632    555 _EP4FIFOPFH	=	0xe632
                    E633    556 _EP4FIFOPFL	=	0xe633
                    E634    557 _EP6FIFOPFH	=	0xe634
                    E635    558 _EP6FIFOPFL	=	0xe635
                    E636    559 _EP8FIFOPFH	=	0xe636
                    E637    560 _EP8FIFOPFL	=	0xe637
                    E640    561 _EP2ISOINPKTS	=	0xe640
                    E641    562 _EP4ISOINPKTS	=	0xe641
                    E642    563 _EP6ISOINPKTS	=	0xe642
                    E643    564 _EP8ISOINPKTS	=	0xe643
                    E648    565 _INPKTEND	=	0xe648
                    E649    566 _OUTPKTEND	=	0xe649
                    E650    567 _EP2FIFOIE	=	0xe650
                    E651    568 _EP2FIFOIRQ	=	0xe651
                    E652    569 _EP4FIFOIE	=	0xe652
                    E653    570 _EP4FIFOIRQ	=	0xe653
                    E654    571 _EP6FIFOIE	=	0xe654
                    E655    572 _EP6FIFOIRQ	=	0xe655
                    E656    573 _EP8FIFOIE	=	0xe656
                    E657    574 _EP8FIFOIRQ	=	0xe657
                    E658    575 _IBNIE	=	0xe658
                    E659    576 _IBNIRQ	=	0xe659
                    E65A    577 _NAKIE	=	0xe65a
                    E65B    578 _NAKIRQ	=	0xe65b
                    E65C    579 _USBIE	=	0xe65c
                    E65D    580 _USBIRQ	=	0xe65d
                    E65E    581 _EPIE	=	0xe65e
                    E65F    582 _EPIRQ	=	0xe65f
                    E660    583 _GPIFIE	=	0xe660
                    E661    584 _GPIFIRQ	=	0xe661
                    E662    585 _USBERRIE	=	0xe662
                    E663    586 _USBERRIRQ	=	0xe663
                    E664    587 _ERRCNTLIM	=	0xe664
                    E665    588 _CLRERRCNT	=	0xe665
                    E666    589 _INT2IVEC	=	0xe666
                    E667    590 _INT4IVEC	=	0xe667
                    E668    591 _INTSETUP	=	0xe668
                    E670    592 _PORTACFG	=	0xe670
                    E671    593 _PORTCCFG	=	0xe671
                    E672    594 _PORTECFG	=	0xe672
                    E678    595 _I2CS	=	0xe678
                    E679    596 _I2DAT	=	0xe679
                    E67A    597 _I2CTL	=	0xe67a
                    E67B    598 _XAUTODAT1	=	0xe67b
                    E67C    599 _XAUTODAT2	=	0xe67c
                    E680    600 _USBCS	=	0xe680
                    E681    601 _SUSPEND	=	0xe681
                    E682    602 _WAKEUPCS	=	0xe682
                    E683    603 _TOGCTL	=	0xe683
                    E684    604 _USBFRAMEH	=	0xe684
                    E685    605 _USBFRAMEL	=	0xe685
                    E686    606 _MICROFRAME	=	0xe686
                    E687    607 _FNADDR	=	0xe687
                    E68A    608 _EP0BCH	=	0xe68a
                    E68B    609 _EP0BCL	=	0xe68b
                    E68D    610 _EP1OUTBC	=	0xe68d
                    E68F    611 _EP1INBC	=	0xe68f
                    E690    612 _EP2BCH	=	0xe690
                    E691    613 _EP2BCL	=	0xe691
                    E694    614 _EP4BCH	=	0xe694
                    E695    615 _EP4BCL	=	0xe695
                    E698    616 _EP6BCH	=	0xe698
                    E699    617 _EP6BCL	=	0xe699
                    E69C    618 _EP8BCH	=	0xe69c
                    E69D    619 _EP8BCL	=	0xe69d
                    E6A0    620 _EP0CS	=	0xe6a0
                    E6A1    621 _EP1OUTCS	=	0xe6a1
                    E6A2    622 _EP1INCS	=	0xe6a2
                    E6A3    623 _EP2CS	=	0xe6a3
                    E6A4    624 _EP4CS	=	0xe6a4
                    E6A5    625 _EP6CS	=	0xe6a5
                    E6A6    626 _EP8CS	=	0xe6a6
                    E6A7    627 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    628 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    629 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    630 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    631 _EP2FIFOBCH	=	0xe6ab
                    E6AC    632 _EP2FIFOBCL	=	0xe6ac
                    E6AD    633 _EP4FIFOBCH	=	0xe6ad
                    E6AE    634 _EP4FIFOBCL	=	0xe6ae
                    E6AF    635 _EP6FIFOBCH	=	0xe6af
                    E6B0    636 _EP6FIFOBCL	=	0xe6b0
                    E6B1    637 _EP8FIFOBCH	=	0xe6b1
                    E6B2    638 _EP8FIFOBCL	=	0xe6b2
                    E6B3    639 _SUDPTRH	=	0xe6b3
                    E6B4    640 _SUDPTRL	=	0xe6b4
                    E6B5    641 _SUDPTRCTL	=	0xe6b5
                    E6B8    642 _SETUPDAT	=	0xe6b8
                    E6C0    643 _GPIFWFSELECT	=	0xe6c0
                    E6C1    644 _GPIFIDLECS	=	0xe6c1
                    E6C2    645 _GPIFIDLECTL	=	0xe6c2
                    E6C3    646 _GPIFCTLCFG	=	0xe6c3
                    E6C4    647 _GPIFADRH	=	0xe6c4
                    E6C5    648 _GPIFADRL	=	0xe6c5
                    E6CE    649 _GPIFTCB3	=	0xe6ce
                    E6CF    650 _GPIFTCB2	=	0xe6cf
                    E6D0    651 _GPIFTCB1	=	0xe6d0
                    E6D1    652 _GPIFTCB0	=	0xe6d1
                    E6D2    653 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    654 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    655 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    656 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    657 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    658 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    659 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    660 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    661 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    662 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    663 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    664 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    665 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    666 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    667 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    668 _GPIFREADYCFG	=	0xe6f3
                    E6F4    669 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    670 _GPIFABORT	=	0xe6f5
                    E6C6    671 _FLOWSTATE	=	0xe6c6
                    E6C7    672 _FLOWLOGIC	=	0xe6c7
                    E6C8    673 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    674 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    675 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    676 _FLOWSTB	=	0xe6cb
                    E6CC    677 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    678 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    679 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    680 _UDMACRCH	=	0xe67d
                    E67E    681 _UDMACRCL	=	0xe67e
                    E67F    682 _UDMACRCQUAL	=	0xe67f
                    E6F8    683 _DBUG	=	0xe6f8
                    E6F9    684 _TESTCFG	=	0xe6f9
                    E6FA    685 _USBTEST	=	0xe6fa
                    E6FB    686 _CT1	=	0xe6fb
                    E6FC    687 _CT2	=	0xe6fc
                    E6FD    688 _CT3	=	0xe6fd
                    E6FE    689 _CT4	=	0xe6fe
                    E740    690 _EP0BUF	=	0xe740
                    E780    691 _EP1OUTBUF	=	0xe780
                    E7C0    692 _EP1INBUF	=	0xe7c0
                    F000    693 _EP2FIFOBUF	=	0xf000
                    F400    694 _EP4FIFOBUF	=	0xf400
                    F800    695 _EP6FIFOBUF	=	0xf800
                    FC00    696 _EP8FIFOBUF	=	0xfc00
                    E1F0    697 _hash1	=	0xe1f0
   1800                     698 _patch_usb_descriptors_hw_rev_1_1:
   1800                     699 	.ds 1
   1801                     700 _patch_usb_descriptors_serial_no_1_1:
   1801                     701 	.ds 8
                            702 ;--------------------------------------------------------
                            703 ; external initialized ram data
                            704 ;--------------------------------------------------------
                            705 	.area HOME    (CODE)
                            706 	.area GSINIT0 (CODE)
                            707 	.area GSINIT1 (CODE)
                            708 	.area GSINIT2 (CODE)
                            709 	.area GSINIT3 (CODE)
                            710 	.area GSINIT4 (CODE)
                            711 	.area GSINIT5 (CODE)
                            712 	.area GSINIT  (CODE)
                            713 	.area GSFINAL (CODE)
                            714 	.area CSEG    (CODE)
                            715 ;--------------------------------------------------------
                            716 ; interrupt vector 
                            717 ;--------------------------------------------------------
                            718 	.area HOME    (CODE)
   1285                     719 __interrupt_vect:
   1285 02 12 88            720 	ljmp	__sdcc_gsinit_startup
                            721 ;--------------------------------------------------------
                            722 ; global & static initialisations
                            723 ;--------------------------------------------------------
                            724 	.area HOME    (CODE)
                            725 	.area GSINIT  (CODE)
                            726 	.area GSFINAL (CODE)
                            727 	.area GSINIT  (CODE)
                            728 	.globl __sdcc_gsinit_startup
                            729 	.globl __sdcc_program_startup
                            730 	.globl __start__stack
                            731 	.globl __mcs51_genRAMCLEAR
                            732 ;------------------------------------------------------------
                            733 ;Allocation info for local variables in function 'isr_tick'
                            734 ;------------------------------------------------------------
                            735 ;count                     Allocated with name '_isr_tick_count_1_1'
                            736 ;------------------------------------------------------------
                            737 ;	usrp_main.c:309: static unsigned char	count = 1;
                            738 ;	genAssign
   1259 75 0C 01            739 	mov	_isr_tick_count_1_1,#0x01
                            740 ;	usrp_main.c:55: unsigned char g_tx_enable = 0;
                            741 ;	genAssign
   125C 75 08 00            742 	mov	_g_tx_enable,#0x00
                            743 ;	usrp_main.c:56: unsigned char g_rx_enable = 0;
                            744 ;	genAssign
   125F 75 09 00            745 	mov	_g_rx_enable,#0x00
                            746 ;	usrp_main.c:57: unsigned char g_rx_overrun = 0;
                            747 ;	genAssign
   1262 75 0A 00            748 	mov	_g_rx_overrun,#0x00
                            749 ;	usrp_main.c:58: unsigned char g_tx_underrun = 0;
                            750 ;	genAssign
   1265 75 0B 00            751 	mov	_g_tx_underrun,#0x00
                            752 	.area GSFINAL (CODE)
   129B 02 01 80            753 	ljmp	__sdcc_program_startup
                            754 ;--------------------------------------------------------
                            755 ; Home
                            756 ;--------------------------------------------------------
                            757 	.area HOME    (CODE)
                            758 	.area CSEG    (CODE)
   0180                     759 __sdcc_program_startup:
   0180 12 04 E0            760 	lcall	_main
                            761 ;	return from main will lock up
   0183 80 FE               762 	sjmp .
                            763 ;--------------------------------------------------------
                            764 ; code
                            765 ;--------------------------------------------------------
                            766 	.area CSEG    (CODE)
                            767 ;------------------------------------------------------------
                            768 ;Allocation info for local variables in function 'get_ep0_data'
                            769 ;------------------------------------------------------------
                            770 ;------------------------------------------------------------
                            771 ;	usrp_main.c:68: get_ep0_data (void)
                            772 ;	-----------------------------------------
                            773 ;	 function get_ep0_data
                            774 ;	-----------------------------------------
   0185                     775 _get_ep0_data:
                    0002    776 	ar2 = 0x02
                    0003    777 	ar3 = 0x03
                    0004    778 	ar4 = 0x04
                    0005    779 	ar5 = 0x05
                    0006    780 	ar6 = 0x06
                    0007    781 	ar7 = 0x07
                    0000    782 	ar0 = 0x00
                    0001    783 	ar1 = 0x01
                            784 ;	usrp_main.c:70: EP0BCL = 0;			// arm EP0 for OUT xfer.  This sets the busy bit
                            785 ;	genAssign
   0185 90 E6 8B            786 	mov	dptr,#_EP0BCL
                            787 ;	Peephole 181	changed mov to clr
   0188 E4                  788 	clr	a
   0189 F0                  789 	movx	@dptr,a
                            790 ;	usrp_main.c:72: while (EP0CS & bmEPBUSY)	// wait for busy to clear
   018A                     791 00101$:
                            792 ;	genAssign
   018A 90 E6 A0            793 	mov	dptr,#_EP0CS
   018D E0                  794 	movx	a,@dptr
                            795 ;	genAnd
   018E FA                  796 	mov	r2,a
                            797 ;	Peephole 105	removed redundant mov
                            798 ;	genIfxJump
                            799 ;	Peephole 108.e	removed ljmp by inverse jump logic
   018F 20 E1 F8            800 	jb	acc.1,00101$
                            801 ;	Peephole 300	removed redundant label 00107$
                            802 ;	Peephole 300	removed redundant label 00104$
   0192 22                  803 	ret
                            804 ;------------------------------------------------------------
                            805 ;Allocation info for local variables in function 'app_vendor_cmd'
                            806 ;------------------------------------------------------------
                            807 ;------------------------------------------------------------
                            808 ;	usrp_main.c:81: app_vendor_cmd (void)
                            809 ;	-----------------------------------------
                            810 ;	 function app_vendor_cmd
                            811 ;	-----------------------------------------
   0193                     812 _app_vendor_cmd:
                            813 ;	usrp_main.c:83: if (bRequestType == VRT_VENDOR_IN){
                            814 ;	genPointerGet
                            815 ;	genFarPointerGet
   0193 90 E6 B8            816 	mov	dptr,#_SETUPDAT
   0196 E0                  817 	movx	a,@dptr
   0197 FA                  818 	mov	r2,a
                            819 ;	genCmpEq
                            820 ;	gencjneshort
   0198 BA C0 02            821 	cjne	r2,#0xC0,00163$
   019B 80 03               822 	sjmp	00164$
   019D                     823 00163$:
   019D 02 02 68            824 	ljmp	00142$
   01A0                     825 00164$:
                            826 ;	usrp_main.c:89: switch (bRequest){
                            827 ;	genPointerGet
                            828 ;	genFarPointerGet
   01A0 90 E6 B9            829 	mov	dptr,#(_SETUPDAT + 0x0001)
   01A3 E0                  830 	movx	a,@dptr
   01A4 FA                  831 	mov	r2,a
                            832 ;	genCmpEq
                            833 ;	gencjneshort
   01A5 BA 80 02            834 	cjne	r2,#0x80,00165$
                            835 ;	Peephole 112.b	changed ljmp to sjmp
   01A8 80 0E               836 	sjmp	00101$
   01AA                     837 00165$:
                            838 ;	genCmpEq
                            839 ;	gencjneshort
   01AA BA 81 02            840 	cjne	r2,#0x81,00166$
                            841 ;	Peephole 112.b	changed ljmp to sjmp
   01AD 80 47               842 	sjmp	00106$
   01AF                     843 00166$:
                            844 ;	genCmpEq
                            845 ;	gencjneshort
   01AF BA 82 03            846 	cjne	r2,#0x82,00167$
   01B2 02 02 24            847 	ljmp	00109$
   01B5                     848 00167$:
   01B5 02 02 64            849 	ljmp	00112$
                            850 ;	usrp_main.c:91: case VRQ_GET_STATUS:
   01B8                     851 00101$:
                            852 ;	usrp_main.c:92: switch (wIndexL){
                            853 ;	genPointerGet
                            854 ;	genFarPointerGet
   01B8 90 E6 BC            855 	mov	dptr,#(_SETUPDAT + 0x0004)
   01BB E0                  856 	movx	a,@dptr
                            857 ;	genCmpEq
                            858 ;	gencjneshort
                            859 ;	Peephole 112.b	changed ljmp to sjmp
   01BC FA                  860 	mov	r2,a
                            861 ;	Peephole 115.b	jump optimization
   01BD 60 05               862 	jz	00102$
                            863 ;	Peephole 300	removed redundant label 00168$
                            864 ;	genCmpEq
                            865 ;	gencjneshort
                            866 ;	Peephole 112.b	changed ljmp to sjmp
                            867 ;	usrp_main.c:94: case GS_TX_UNDERRUN:
                            868 ;	Peephole 112.b	changed ljmp to sjmp
                            869 ;	Peephole 198.b	optimized misc jump sequence
   01BF BA 01 30            870 	cjne	r2,#0x01,00104$
   01C2 80 17               871 	sjmp	00103$
                            872 ;	Peephole 300	removed redundant label 00169$
   01C4                     873 00102$:
                            874 ;	usrp_main.c:95: EP0BUF[0] = g_tx_underrun;
                            875 ;	genPointerSet
                            876 ;     genFarPointerSet
   01C4 90 E7 40            877 	mov	dptr,#_EP0BUF
   01C7 E5 0B               878 	mov	a,_g_tx_underrun
   01C9 F0                  879 	movx	@dptr,a
                            880 ;	usrp_main.c:96: g_tx_underrun = 0;
                            881 ;	genAssign
   01CA 75 0B 00            882 	mov	_g_tx_underrun,#0x00
                            883 ;	usrp_main.c:97: EP0BCH = 0;
                            884 ;	genAssign
   01CD 90 E6 8A            885 	mov	dptr,#_EP0BCH
                            886 ;	Peephole 181	changed mov to clr
   01D0 E4                  887 	clr	a
   01D1 F0                  888 	movx	@dptr,a
                            889 ;	usrp_main.c:98: EP0BCL = 1;
                            890 ;	genAssign
   01D2 90 E6 8B            891 	mov	dptr,#_EP0BCL
   01D5 74 01               892 	mov	a,#0x01
   01D7 F0                  893 	movx	@dptr,a
                            894 ;	usrp_main.c:99: break;
   01D8 02 03 99            895 	ljmp	00143$
                            896 ;	usrp_main.c:101: case GS_RX_OVERRUN:
   01DB                     897 00103$:
                            898 ;	usrp_main.c:102: EP0BUF[0] = g_rx_overrun;
                            899 ;	genPointerSet
                            900 ;     genFarPointerSet
   01DB 90 E7 40            901 	mov	dptr,#_EP0BUF
   01DE E5 0A               902 	mov	a,_g_rx_overrun
   01E0 F0                  903 	movx	@dptr,a
                            904 ;	usrp_main.c:103: g_rx_overrun = 0;
                            905 ;	genAssign
   01E1 75 0A 00            906 	mov	_g_rx_overrun,#0x00
                            907 ;	usrp_main.c:104: EP0BCH = 0;
                            908 ;	genAssign
   01E4 90 E6 8A            909 	mov	dptr,#_EP0BCH
                            910 ;	Peephole 181	changed mov to clr
   01E7 E4                  911 	clr	a
   01E8 F0                  912 	movx	@dptr,a
                            913 ;	usrp_main.c:105: EP0BCL = 1;
                            914 ;	genAssign
   01E9 90 E6 8B            915 	mov	dptr,#_EP0BCL
   01EC 74 01               916 	mov	a,#0x01
   01EE F0                  917 	movx	@dptr,a
                            918 ;	usrp_main.c:106: break;
   01EF 02 03 99            919 	ljmp	00143$
                            920 ;	usrp_main.c:108: default:
   01F2                     921 00104$:
                            922 ;	usrp_main.c:109: return 0;
                            923 ;	genRet
   01F2 75 82 00            924 	mov	dpl,#0x00
                            925 ;	Peephole 251.a	replaced ljmp to ret with ret
   01F5 22                  926 	ret
                            927 ;	usrp_main.c:113: case VRQ_I2C_READ:
   01F6                     928 00106$:
                            929 ;	usrp_main.c:114: if (!i2c_read (wValueL, EP0BUF, wLengthL))
                            930 ;	genPointerGet
                            931 ;	genFarPointerGet
   01F6 90 E6 BA            932 	mov	dptr,#(_SETUPDAT + 0x0002)
   01F9 E0                  933 	movx	a,@dptr
   01FA FA                  934 	mov	r2,a
                            935 ;	genAddrOf
   01FB 75 1B 40            936 	mov	_i2c_read_PARM_2,#_EP0BUF
   01FE 75 1C E7            937 	mov	(_i2c_read_PARM_2 + 1),#(_EP0BUF >> 8)
                            938 ;	genPointerGet
                            939 ;	genFarPointerGet
   0201 90 E6 BE            940 	mov	dptr,#(_SETUPDAT + 0x0006)
   0204 E0                  941 	movx	a,@dptr
   0205 F5 1D               942 	mov	_i2c_read_PARM_3,a
                            943 ;	genCall
   0207 8A 82               944 	mov	dpl,r2
   0209 12 0A A1            945 	lcall	_i2c_read
   020C E5 82               946 	mov	a,dpl
                            947 ;	genIfx
                            948 ;	genIfxJump
                            949 ;	Peephole 108.b	removed ljmp by inverse jump logic
                            950 ;	usrp_main.c:115: return 0;
                            951 ;	genRet
   020E 70 03               952 	jnz	00108$
                            953 ;	Peephole 300	removed redundant label 00170$
                            954 ;	Peephole 256.c	loading dpl with zero from a
   0210 F5 82               955 	mov	dpl,a
                            956 ;	Peephole 251.a	replaced ljmp to ret with ret
   0212 22                  957 	ret
   0213                     958 00108$:
                            959 ;	usrp_main.c:117: EP0BCH = 0;
                            960 ;	genAssign
   0213 90 E6 8A            961 	mov	dptr,#_EP0BCH
                            962 ;	Peephole 181	changed mov to clr
   0216 E4                  963 	clr	a
   0217 F0                  964 	movx	@dptr,a
                            965 ;	usrp_main.c:118: EP0BCL = wLengthL;
                            966 ;	genPointerGet
                            967 ;	genFarPointerGet
   0218 90 E6 BE            968 	mov	dptr,#(_SETUPDAT + 0x0006)
   021B E0                  969 	movx	a,@dptr
                            970 ;	genAssign
   021C FA                  971 	mov	r2,a
   021D 90 E6 8B            972 	mov	dptr,#_EP0BCL
                            973 ;	Peephole 100	removed redundant mov
   0220 F0                  974 	movx	@dptr,a
                            975 ;	usrp_main.c:119: break;
   0221 02 03 99            976 	ljmp	00143$
                            977 ;	usrp_main.c:121: case VRQ_SPI_READ:
   0224                     978 00109$:
                            979 ;	usrp_main.c:122: if (!spi_read (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, wLengthL))
                            980 ;	genPointerGet
                            981 ;	genFarPointerGet
   0224 90 E6 BB            982 	mov	dptr,#(_SETUPDAT + 0x0003)
   0227 E0                  983 	movx	a,@dptr
   0228 FA                  984 	mov	r2,a
                            985 ;	genPointerGet
                            986 ;	genFarPointerGet
   0229 90 E6 BA            987 	mov	dptr,#(_SETUPDAT + 0x0002)
   022C E0                  988 	movx	a,@dptr
   022D F5 21               989 	mov	_spi_read_PARM_2,a
                            990 ;	genPointerGet
                            991 ;	genFarPointerGet
   022F 90 E6 BD            992 	mov	dptr,#(_SETUPDAT + 0x0005)
   0232 E0                  993 	movx	a,@dptr
   0233 F5 22               994 	mov	_spi_read_PARM_3,a
                            995 ;	genPointerGet
                            996 ;	genFarPointerGet
   0235 90 E6 BC            997 	mov	dptr,#(_SETUPDAT + 0x0004)
   0238 E0                  998 	movx	a,@dptr
   0239 F5 23               999 	mov	_spi_read_PARM_4,a
                           1000 ;	genAddrOf
   023B 75 24 40           1001 	mov	_spi_read_PARM_5,#_EP0BUF
   023E 75 25 E7           1002 	mov	(_spi_read_PARM_5 + 1),#(_EP0BUF >> 8)
                           1003 ;	genPointerGet
                           1004 ;	genFarPointerGet
   0241 90 E6 BE           1005 	mov	dptr,#(_SETUPDAT + 0x0006)
   0244 E0                 1006 	movx	a,@dptr
   0245 F5 26              1007 	mov	_spi_read_PARM_6,a
                           1008 ;	genCall
   0247 8A 82              1009 	mov	dpl,r2
   0249 12 08 65           1010 	lcall	_spi_read
   024C E5 82              1011 	mov	a,dpl
                           1012 ;	genIfx
                           1013 ;	genIfxJump
                           1014 ;	Peephole 108.b	removed ljmp by inverse jump logic
                           1015 ;	usrp_main.c:123: return 0;
                           1016 ;	genRet
   024E 70 03              1017 	jnz	00111$
                           1018 ;	Peephole 300	removed redundant label 00171$
                           1019 ;	Peephole 256.c	loading dpl with zero from a
   0250 F5 82              1020 	mov	dpl,a
                           1021 ;	Peephole 251.a	replaced ljmp to ret with ret
   0252 22                 1022 	ret
   0253                    1023 00111$:
                           1024 ;	usrp_main.c:125: EP0BCH = 0;
                           1025 ;	genAssign
   0253 90 E6 8A           1026 	mov	dptr,#_EP0BCH
                           1027 ;	Peephole 181	changed mov to clr
   0256 E4                 1028 	clr	a
   0257 F0                 1029 	movx	@dptr,a
                           1030 ;	usrp_main.c:126: EP0BCL = wLengthL;
                           1031 ;	genPointerGet
                           1032 ;	genFarPointerGet
   0258 90 E6 BE           1033 	mov	dptr,#(_SETUPDAT + 0x0006)
   025B E0                 1034 	movx	a,@dptr
                           1035 ;	genAssign
   025C FA                 1036 	mov	r2,a
   025D 90 E6 8B           1037 	mov	dptr,#_EP0BCL
                           1038 ;	Peephole 100	removed redundant mov
   0260 F0                 1039 	movx	@dptr,a
                           1040 ;	usrp_main.c:127: break;
   0261 02 03 99           1041 	ljmp	00143$
                           1042 ;	usrp_main.c:129: default:
   0264                    1043 00112$:
                           1044 ;	usrp_main.c:130: return 0;
                           1045 ;	genRet
   0264 75 82 00           1046 	mov	dpl,#0x00
                           1047 ;	Peephole 251.a	replaced ljmp to ret with ret
   0267 22                 1048 	ret
                           1049 ;	usrp_main.c:131: }
   0268                    1050 00142$:
                           1051 ;	usrp_main.c:134: else if (bRequestType == VRT_VENDOR_OUT){
                           1052 ;	genPointerGet
                           1053 ;	genFarPointerGet
   0268 90 E6 B8           1054 	mov	dptr,#_SETUPDAT
   026B E0                 1055 	movx	a,@dptr
   026C FA                 1056 	mov	r2,a
                           1057 ;	genCmpEq
                           1058 ;	gencjneshort
   026D BA 40 02           1059 	cjne	r2,#0x40,00172$
   0270 80 03              1060 	sjmp	00173$
   0272                    1061 00172$:
   0272 02 03 95           1062 	ljmp	00139$
   0275                    1063 00173$:
                           1064 ;	usrp_main.c:140: switch (bRequest){
                           1065 ;	genPointerGet
                           1066 ;	genFarPointerGet
   0275 90 E6 B9           1067 	mov	dptr,#(_SETUPDAT + 0x0001)
   0278 E0                 1068 	movx	a,@dptr
                           1069 ;	genCmpGt
                           1070 ;	genCmp
                           1071 ;	genIfxJump
                           1072 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   0279 FA                 1073 	mov  r2,a
                           1074 ;	Peephole 177.a	removed redundant mov
   027A 24 F4              1075 	add	a,#0xff - 0x0B
   027C 50 03              1076 	jnc	00174$
   027E 02 03 91           1077 	ljmp	00136$
   0281                    1078 00174$:
                           1079 ;	genJumpTab
   0281 EA                 1080 	mov	a,r2
                           1081 ;	Peephole 254	optimized left shift
   0282 2A                 1082 	add	a,r2
   0283 2A                 1083 	add	a,r2
   0284 90 02 88           1084 	mov	dptr,#00175$
   0287 73                 1085 	jmp	@a+dptr
   0288                    1086 00175$:
   0288 02 03 91           1087 	ljmp	00136$
   028B 02 02 AC           1088 	ljmp	00114$
   028E 02 02 D6           1089 	ljmp	00119$
   0291 02 03 91           1090 	ljmp	00136$
   0294 02 03 00           1091 	ljmp	00125$
   0297 02 03 0D           1092 	ljmp	00126$
   029A 02 03 1A           1093 	ljmp	00127$
   029D 02 03 91           1094 	ljmp	00136$
   02A0 02 03 3F           1095 	ljmp	00130$
   02A3 02 03 5F           1096 	ljmp	00133$
   02A6 02 03 27           1097 	ljmp	00128$
   02A9 02 03 33           1098 	ljmp	00129$
                           1099 ;	usrp_main.c:142: case VRQ_SET_LED:
   02AC                    1100 00114$:
                           1101 ;	usrp_main.c:143: switch (wIndexL){
                           1102 ;	genPointerGet
                           1103 ;	genFarPointerGet
   02AC 90 E6 BC           1104 	mov	dptr,#(_SETUPDAT + 0x0004)
   02AF E0                 1105 	movx	a,@dptr
                           1106 ;	genCmpEq
                           1107 ;	gencjneshort
                           1108 ;	Peephole 112.b	changed ljmp to sjmp
   02B0 FA                 1109 	mov	r2,a
                           1110 ;	Peephole 115.b	jump optimization
   02B1 60 05              1111 	jz	00115$
                           1112 ;	Peephole 300	removed redundant label 00176$
                           1113 ;	genCmpEq
                           1114 ;	gencjneshort
                           1115 ;	Peephole 112.b	changed ljmp to sjmp
                           1116 ;	usrp_main.c:144: case 0:
                           1117 ;	Peephole 112.b	changed ljmp to sjmp
                           1118 ;	Peephole 198.b	optimized misc jump sequence
   02B3 BA 01 1C           1119 	cjne	r2,#0x01,00117$
   02B6 80 0D              1120 	sjmp	00116$
                           1121 ;	Peephole 300	removed redundant label 00177$
   02B8                    1122 00115$:
                           1123 ;	usrp_main.c:145: set_led_0 (wValueL);
                           1124 ;	genPointerGet
                           1125 ;	genFarPointerGet
   02B8 90 E6 BA           1126 	mov	dptr,#(_SETUPDAT + 0x0002)
   02BB E0                 1127 	movx	a,@dptr
                           1128 ;	genCall
   02BC FA                 1129 	mov	r2,a
                           1130 ;	Peephole 244.c	loading dpl from a instead of r2
   02BD F5 82              1131 	mov	dpl,a
   02BF 12 05 D0           1132 	lcall	_set_led_0
                           1133 ;	usrp_main.c:146: break;
   02C2 02 03 99           1134 	ljmp	00143$
                           1135 ;	usrp_main.c:148: case 1:
   02C5                    1136 00116$:
                           1137 ;	usrp_main.c:149: set_led_1 (wValueL);
                           1138 ;	genPointerGet
                           1139 ;	genFarPointerGet
   02C5 90 E6 BA           1140 	mov	dptr,#(_SETUPDAT + 0x0002)
   02C8 E0                 1141 	movx	a,@dptr
                           1142 ;	genCall
   02C9 FA                 1143 	mov	r2,a
                           1144 ;	Peephole 244.c	loading dpl from a instead of r2
   02CA F5 82              1145 	mov	dpl,a
   02CC 12 05 DD           1146 	lcall	_set_led_1
                           1147 ;	usrp_main.c:150: break;
   02CF 02 03 99           1148 	ljmp	00143$
                           1149 ;	usrp_main.c:152: default:
   02D2                    1150 00117$:
                           1151 ;	usrp_main.c:153: return 0;
                           1152 ;	genRet
   02D2 75 82 00           1153 	mov	dpl,#0x00
                           1154 ;	Peephole 251.a	replaced ljmp to ret with ret
   02D5 22                 1155 	ret
                           1156 ;	usrp_main.c:157: case VRQ_FPGA_LOAD:
   02D6                    1157 00119$:
                           1158 ;	usrp_main.c:158: switch (wIndexL){			// sub-command
                           1159 ;	genPointerGet
                           1160 ;	genFarPointerGet
   02D6 90 E6 BC           1161 	mov	dptr,#(_SETUPDAT + 0x0004)
   02D9 E0                 1162 	movx	a,@dptr
                           1163 ;	genCmpEq
                           1164 ;	gencjneshort
                           1165 ;	Peephole 112.b	changed ljmp to sjmp
   02DA FA                 1166 	mov	r2,a
                           1167 ;	Peephole 115.b	jump optimization
   02DB 60 0A              1168 	jz	00120$
                           1169 ;	Peephole 300	removed redundant label 00178$
                           1170 ;	genCmpEq
                           1171 ;	gencjneshort
   02DD BA 01 02           1172 	cjne	r2,#0x01,00179$
                           1173 ;	Peephole 112.b	changed ljmp to sjmp
   02E0 80 08              1174 	sjmp	00121$
   02E2                    1175 00179$:
                           1176 ;	genCmpEq
                           1177 ;	gencjneshort
                           1178 ;	Peephole 112.b	changed ljmp to sjmp
                           1179 ;	usrp_main.c:159: case FL_BEGIN:
                           1180 ;	Peephole 112.b	changed ljmp to sjmp
                           1181 ;	Peephole 198.b	optimized misc jump sequence
   02E2 BA 02 17           1182 	cjne	r2,#0x02,00123$
   02E5 80 12              1183 	sjmp	00122$
                           1184 ;	Peephole 300	removed redundant label 00180$
   02E7                    1185 00120$:
                           1186 ;	usrp_main.c:160: return fpga_load_begin ();
                           1187 ;	genCall
                           1188 ;	genRet
                           1189 ;	Peephole 251.a	replaced ljmp to ret with ret
                           1190 ;	Peephole 253.a	replaced lcall/ret with ljmp
   02E7 02 06 72           1191 	ljmp	_fpga_load_begin
                           1192 ;	usrp_main.c:162: case FL_XFER:
   02EA                    1193 00121$:
                           1194 ;	usrp_main.c:163: get_ep0_data ();
                           1195 ;	genCall
   02EA 12 01 85           1196 	lcall	_get_ep0_data
                           1197 ;	usrp_main.c:164: return fpga_load_xfer (EP0BUF, EP0BCL);
                           1198 ;	genAssign
   02ED 90 E6 8B           1199 	mov	dptr,#_EP0BCL
   02F0 E0                 1200 	movx	a,@dptr
   02F1 F5 12              1201 	mov	_fpga_load_xfer_PARM_2,a
                           1202 ;	genCall
                           1203 ;	Peephole 182.a	used 16 bit load of DPTR
   02F3 90 E7 40           1204 	mov	dptr,#_EP0BUF
                           1205 ;	genRet
                           1206 ;	Peephole 251.a	replaced ljmp to ret with ret
                           1207 ;	Peephole 253.a	replaced lcall/ret with ljmp
   02F6 02 06 E1           1208 	ljmp	_fpga_load_xfer
                           1209 ;	usrp_main.c:166: case FL_END:
   02F9                    1210 00122$:
                           1211 ;	usrp_main.c:167: return fpga_load_end ();
                           1212 ;	genCall
                           1213 ;	genRet
                           1214 ;	Peephole 251.a	replaced ljmp to ret with ret
                           1215 ;	Peephole 253.a	replaced lcall/ret with ljmp
   02F9 02 06 F1           1216 	ljmp	_fpga_load_end
                           1217 ;	usrp_main.c:169: default:
   02FC                    1218 00123$:
                           1219 ;	usrp_main.c:170: return 0;
                           1220 ;	genRet
   02FC 75 82 00           1221 	mov	dpl,#0x00
                           1222 ;	Peephole 251.a	replaced ljmp to ret with ret
   02FF 22                 1223 	ret
                           1224 ;	usrp_main.c:175: case VRQ_FPGA_SET_RESET:
   0300                    1225 00125$:
                           1226 ;	usrp_main.c:176: fpga_set_reset (wValueL);
                           1227 ;	genPointerGet
                           1228 ;	genFarPointerGet
   0300 90 E6 BA           1229 	mov	dptr,#(_SETUPDAT + 0x0002)
   0303 E0                 1230 	movx	a,@dptr
                           1231 ;	genCall
   0304 FA                 1232 	mov	r2,a
                           1233 ;	Peephole 244.c	loading dpl from a instead of r2
   0305 F5 82              1234 	mov	dpl,a
   0307 12 07 53           1235 	lcall	_fpga_set_reset
                           1236 ;	usrp_main.c:177: break;
   030A 02 03 99           1237 	ljmp	00143$
                           1238 ;	usrp_main.c:179: case VRQ_FPGA_SET_TX_ENABLE:
   030D                    1239 00126$:
                           1240 ;	usrp_main.c:180: fpga_set_tx_enable (wValueL);
                           1241 ;	genPointerGet
                           1242 ;	genFarPointerGet
   030D 90 E6 BA           1243 	mov	dptr,#(_SETUPDAT + 0x0002)
   0310 E0                 1244 	movx	a,@dptr
                           1245 ;	genCall
   0311 FA                 1246 	mov	r2,a
                           1247 ;	Peephole 244.c	loading dpl from a instead of r2
   0312 F5 82              1248 	mov	dpl,a
   0314 12 07 6E           1249 	lcall	_fpga_set_tx_enable
                           1250 ;	usrp_main.c:181: break;
   0317 02 03 99           1251 	ljmp	00143$
                           1252 ;	usrp_main.c:183: case VRQ_FPGA_SET_RX_ENABLE:
   031A                    1253 00127$:
                           1254 ;	usrp_main.c:184: fpga_set_rx_enable (wValueL);
                           1255 ;	genPointerGet
                           1256 ;	genFarPointerGet
   031A 90 E6 BA           1257 	mov	dptr,#(_SETUPDAT + 0x0002)
   031D E0                 1258 	movx	a,@dptr
                           1259 ;	genCall
   031E FA                 1260 	mov	r2,a
                           1261 ;	Peephole 244.c	loading dpl from a instead of r2
   031F F5 82              1262 	mov	dpl,a
   0321 12 07 89           1263 	lcall	_fpga_set_rx_enable
                           1264 ;	usrp_main.c:185: break;
   0324 02 03 99           1265 	ljmp	00143$
                           1266 ;	usrp_main.c:187: case VRQ_FPGA_SET_TX_RESET:
   0327                    1267 00128$:
                           1268 ;	usrp_main.c:188: fpga_set_tx_reset (wValueL);
                           1269 ;	genPointerGet
                           1270 ;	genFarPointerGet
   0327 90 E6 BA           1271 	mov	dptr,#(_SETUPDAT + 0x0002)
   032A E0                 1272 	movx	a,@dptr
                           1273 ;	genCall
   032B FA                 1274 	mov	r2,a
                           1275 ;	Peephole 244.c	loading dpl from a instead of r2
   032C F5 82              1276 	mov	dpl,a
   032E 12 07 A4           1277 	lcall	_fpga_set_tx_reset
                           1278 ;	usrp_main.c:189: break;
                           1279 ;	usrp_main.c:191: case VRQ_FPGA_SET_RX_RESET:
                           1280 ;	Peephole 112.b	changed ljmp to sjmp
   0331 80 66              1281 	sjmp	00143$
   0333                    1282 00129$:
                           1283 ;	usrp_main.c:192: fpga_set_rx_reset (wValueL);
                           1284 ;	genPointerGet
                           1285 ;	genFarPointerGet
   0333 90 E6 BA           1286 	mov	dptr,#(_SETUPDAT + 0x0002)
   0336 E0                 1287 	movx	a,@dptr
                           1288 ;	genCall
   0337 FA                 1289 	mov	r2,a
                           1290 ;	Peephole 244.c	loading dpl from a instead of r2
   0338 F5 82              1291 	mov	dpl,a
   033A 12 07 AE           1292 	lcall	_fpga_set_rx_reset
                           1293 ;	usrp_main.c:193: break;
                           1294 ;	usrp_main.c:195: case VRQ_I2C_WRITE:
                           1295 ;	Peephole 112.b	changed ljmp to sjmp
   033D 80 5A              1296 	sjmp	00143$
   033F                    1297 00130$:
                           1298 ;	usrp_main.c:196: get_ep0_data ();
                           1299 ;	genCall
   033F 12 01 85           1300 	lcall	_get_ep0_data
                           1301 ;	usrp_main.c:197: if (!i2c_write (wValueL, EP0BUF, EP0BCL))
                           1302 ;	genPointerGet
                           1303 ;	genFarPointerGet
   0342 90 E6 BA           1304 	mov	dptr,#(_SETUPDAT + 0x0002)
   0345 E0                 1305 	movx	a,@dptr
   0346 FA                 1306 	mov	r2,a
                           1307 ;	genAddrOf
   0347 75 1B 40           1308 	mov	_i2c_write_PARM_2,#_EP0BUF
   034A 75 1C E7           1309 	mov	(_i2c_write_PARM_2 + 1),#(_EP0BUF >> 8)
                           1310 ;	genAssign
   034D 90 E6 8B           1311 	mov	dptr,#_EP0BCL
   0350 E0                 1312 	movx	a,@dptr
   0351 F5 1D              1313 	mov	_i2c_write_PARM_3,a
                           1314 ;	genCall
   0353 8A 82              1315 	mov	dpl,r2
   0355 12 0B 64           1316 	lcall	_i2c_write
   0358 E5 82              1317 	mov	a,dpl
                           1318 ;	genIfx
                           1319 ;	genIfxJump
                           1320 ;	Peephole 108.b	removed ljmp by inverse jump logic
                           1321 ;	usrp_main.c:198: return 0;
                           1322 ;	genRet
   035A 70 3D              1323 	jnz	00143$
                           1324 ;	Peephole 300	removed redundant label 00181$
                           1325 ;	Peephole 256.c	loading dpl with zero from a
   035C F5 82              1326 	mov	dpl,a
                           1327 ;	usrp_main.c:201: case VRQ_SPI_WRITE:
                           1328 ;	Peephole 112.b	changed ljmp to sjmp
                           1329 ;	Peephole 251.b	replaced sjmp to ret with ret
   035E 22                 1330 	ret
   035F                    1331 00133$:
                           1332 ;	usrp_main.c:202: get_ep0_data ();
                           1333 ;	genCall
   035F 12 01 85           1334 	lcall	_get_ep0_data
                           1335 ;	usrp_main.c:203: if (!spi_write (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, EP0BCL))
                           1336 ;	genPointerGet
                           1337 ;	genFarPointerGet
   0362 90 E6 BB           1338 	mov	dptr,#(_SETUPDAT + 0x0003)
   0365 E0                 1339 	movx	a,@dptr
   0366 FA                 1340 	mov	r2,a
                           1341 ;	genPointerGet
                           1342 ;	genFarPointerGet
   0367 90 E6 BA           1343 	mov	dptr,#(_SETUPDAT + 0x0002)
   036A E0                 1344 	movx	a,@dptr
   036B F5 27              1345 	mov	_spi_write_PARM_2,a
                           1346 ;	genPointerGet
                           1347 ;	genFarPointerGet
   036D 90 E6 BD           1348 	mov	dptr,#(_SETUPDAT + 0x0005)
   0370 E0                 1349 	movx	a,@dptr
   0371 F5 28              1350 	mov	_spi_write_PARM_3,a
                           1351 ;	genPointerGet
                           1352 ;	genFarPointerGet
   0373 90 E6 BC           1353 	mov	dptr,#(_SETUPDAT + 0x0004)
   0376 E0                 1354 	movx	a,@dptr
   0377 F5 29              1355 	mov	_spi_write_PARM_4,a
                           1356 ;	genAddrOf
   0379 75 2A 40           1357 	mov	_spi_write_PARM_5,#_EP0BUF
   037C 75 2B E7           1358 	mov	(_spi_write_PARM_5 + 1),#(_EP0BUF >> 8)
                           1359 ;	genAssign
   037F 90 E6 8B           1360 	mov	dptr,#_EP0BCL
   0382 E0                 1361 	movx	a,@dptr
   0383 F5 2C              1362 	mov	_spi_write_PARM_6,a
                           1363 ;	genCall
   0385 8A 82              1364 	mov	dpl,r2
   0387 12 08 D3           1365 	lcall	_spi_write
   038A E5 82              1366 	mov	a,dpl
                           1367 ;	genIfx
                           1368 ;	genIfxJump
                           1369 ;	Peephole 108.b	removed ljmp by inverse jump logic
                           1370 ;	usrp_main.c:204: return 0;
                           1371 ;	genRet
   038C 70 0B              1372 	jnz	00143$
                           1373 ;	Peephole 300	removed redundant label 00182$
                           1374 ;	Peephole 256.c	loading dpl with zero from a
   038E F5 82              1375 	mov	dpl,a
                           1376 ;	usrp_main.c:207: default:
                           1377 ;	Peephole 112.b	changed ljmp to sjmp
                           1378 ;	Peephole 251.b	replaced sjmp to ret with ret
   0390 22                 1379 	ret
   0391                    1380 00136$:
                           1381 ;	usrp_main.c:208: return 0;
                           1382 ;	genRet
   0391 75 82 00           1383 	mov	dpl,#0x00
                           1384 ;	usrp_main.c:209: }
                           1385 ;	Peephole 112.b	changed ljmp to sjmp
                           1386 ;	Peephole 251.b	replaced sjmp to ret with ret
   0394 22                 1387 	ret
   0395                    1388 00139$:
                           1389 ;	usrp_main.c:213: return 0;    // invalid bRequestType
                           1390 ;	genRet
   0395 75 82 00           1391 	mov	dpl,#0x00
                           1392 ;	Peephole 112.b	changed ljmp to sjmp
                           1393 ;	usrp_main.c:215: return 1;
                           1394 ;	genRet
                           1395 ;	Peephole 237.a	removed sjmp to ret
   0398 22                 1396 	ret
   0399                    1397 00143$:
   0399 75 82 01           1398 	mov	dpl,#0x01
                           1399 ;	Peephole 300	removed redundant label 00144$
   039C 22                 1400 	ret
                           1401 ;------------------------------------------------------------
                           1402 ;Allocation info for local variables in function 'main_loop'
                           1403 ;------------------------------------------------------------
                           1404 ;------------------------------------------------------------
                           1405 ;	usrp_main.c:221: main_loop (void)
                           1406 ;	-----------------------------------------
                           1407 ;	 function main_loop
                           1408 ;	-----------------------------------------
   039D                    1409 _main_loop:
                           1410 ;	usrp_main.c:223: setup_flowstate_common ();
                           1411 ;	genAssign
   039D 90 E6 C6           1412 	mov	dptr,#_FLOWSTATE
   03A0 74 81              1413 	mov	a,#0x81
   03A2 F0                 1414 	movx	@dptr,a
                           1415 ;	genAssign
   03A3 90 E6 C7           1416 	mov	dptr,#_FLOWLOGIC
   03A6 74 2D              1417 	mov	a,#0x2D
   03A8 F0                 1418 	movx	@dptr,a
                           1419 ;	genAssign
   03A9 90 E6 C8           1420 	mov	dptr,#_FLOWEQ0CTL
   03AC 74 26              1421 	mov	a,#0x26
   03AE F0                 1422 	movx	@dptr,a
                           1423 ;	genAssign
   03AF 90 E6 C9           1424 	mov	dptr,#_FLOWEQ1CTL
                           1425 ;	Peephole 181	changed mov to clr
   03B2 E4                 1426 	clr	a
   03B3 F0                 1427 	movx	@dptr,a
                           1428 ;	genAssign
   03B4 90 E6 CA           1429 	mov	dptr,#_FLOWHOLDOFF
   03B7 74 04              1430 	mov	a,#0x04
   03B9 F0                 1431 	movx	@dptr,a
                           1432 ;	genAssign
   03BA 90 E6 CB           1433 	mov	dptr,#_FLOWSTB
   03BD 74 04              1434 	mov	a,#0x04
   03BF F0                 1435 	movx	@dptr,a
                           1436 ;	genAssign
   03C0 90 E6 CC           1437 	mov	dptr,#_FLOWSTBEDGE
   03C3 74 03              1438 	mov	a,#0x03
   03C5 F0                 1439 	movx	@dptr,a
                           1440 ;	genAssign
   03C6 90 E6 CD           1441 	mov	dptr,#_FLOWSTBHPERIOD
   03C9 74 02              1442 	mov	a,#0x02
   03CB F0                 1443 	movx	@dptr,a
                           1444 ;	genAssign
   03CC 90 E6 0C           1445 	mov	dptr,#_GPIFHOLDAMOUNT
                           1446 ;	Peephole 181	changed mov to clr
   03CF E4                 1447 	clr	a
   03D0 F0                 1448 	movx	@dptr,a
                           1449 ;	usrp_main.c:225: while (1){
   03D1                    1450 00141$:
                           1451 ;	usrp_main.c:227: if (usb_setup_packet_avail ())
                           1452 ;	genIfx
                           1453 ;	genIfxJump
                           1454 ;	Peephole 108.d	removed ljmp by inverse jump logic
   03D1 30 00 03           1455 	jnb	__usb_got_SUDAV,00105$
                           1456 ;	Peephole 300	removed redundant label 00160$
                           1457 ;	usrp_main.c:228: usb_handle_setup_packet ();
                           1458 ;	genCall
   03D4 12 0D 76           1459 	lcall	_usb_handle_setup_packet
   03D7                    1460 00105$:
                           1461 ;	usrp_main.c:231: if (GPIFTRIG & bmGPIF_IDLE){
                           1462 ;	genAnd
   03D7 E5 BB              1463 	mov	a,_GPIFTRIG
                           1464 ;	genIfxJump
                           1465 ;	Peephole 108.d	removed ljmp by inverse jump logic
   03D9 30 E7 F5           1466 	jnb	acc.7,00141$
                           1467 ;	Peephole 300	removed redundant label 00161$
                           1468 ;	usrp_main.c:237: if (UC_BOARD_HAS_FPGA && (USRP_PA & (bmPA_TX_UNDERRUN | bmPA_RX_OVERRUN))){
                           1469 ;	genAnd
   03DC E5 80              1470 	mov	a,_IOA
   03DE 54 C0              1471 	anl	a,#0xC0
                           1472 ;	Peephole 108.c	removed ljmp by inverse jump logic
   03E0 60 16              1473 	jz	00114$
                           1474 ;	Peephole 300	removed redundant label 00162$
                           1475 ;	usrp_main.c:240: if (USRP_PA & bmPA_TX_UNDERRUN)
                           1476 ;	genAnd
   03E2 E5 80              1477 	mov	a,_IOA
                           1478 ;	genIfxJump
                           1479 ;	Peephole 108.d	removed ljmp by inverse jump logic
   03E4 30 E7 03           1480 	jnb	acc.7,00107$
                           1481 ;	Peephole 300	removed redundant label 00163$
                           1482 ;	usrp_main.c:241: g_tx_underrun = 1;
                           1483 ;	genAssign
   03E7 75 0B 01           1484 	mov	_g_tx_underrun,#0x01
   03EA                    1485 00107$:
                           1486 ;	usrp_main.c:243: if (USRP_PA & bmPA_RX_OVERRUN)
                           1487 ;	genAnd
   03EA E5 80              1488 	mov	a,_IOA
                           1489 ;	genIfxJump
                           1490 ;	Peephole 108.d	removed ljmp by inverse jump logic
   03EC 30 E6 03           1491 	jnb	acc.6,00110$
                           1492 ;	Peephole 300	removed redundant label 00164$
                           1493 ;	usrp_main.c:244: g_rx_overrun = 1;
                           1494 ;	genAssign
   03EF 75 0A 01           1495 	mov	_g_rx_overrun,#0x01
                           1496 ;	usrp_main.c:247: fpga_clear_flags ();
   03F2                    1497 00110$:
                           1498 ;	genOr
   03F2 43 B1 08           1499 	orl	_IOE,#0x08
                           1500 ;	genAnd
   03F5 53 B1 F7           1501 	anl	_IOE,#0xF7
   03F8                    1502 00114$:
                           1503 ;	usrp_main.c:253: if (g_tx_enable && !(EP24FIFOFLGS & 0x02)){  // USB end point fifo is not empty...
                           1504 ;	genIfx
   03F8 E5 08              1505 	mov	a,_g_tx_enable
                           1506 ;	genIfxJump
                           1507 ;	Peephole 108.c	removed ljmp by inverse jump logic
   03FA 60 2A              1508 	jz	00125$
                           1509 ;	Peephole 300	removed redundant label 00165$
                           1510 ;	genAnd
   03FC E5 AB              1511 	mov	a,_EP24FIFOFLGS
                           1512 ;	genIfxJump
                           1513 ;	Peephole 108.e	removed ljmp by inverse jump logic
   03FE 20 E1 25           1514 	jb	acc.1,00125$
                           1515 ;	Peephole 300	removed redundant label 00166$
                           1516 ;	usrp_main.c:255: if (fpga_has_room_for_packet ()){	   // ... and FPGA has room for packet
                           1517 ;	genAssign
   0401 90 E6 F4           1518 	mov	dptr,#_GPIFREADYSTAT
   0404 E0                 1519 	movx	a,@dptr
                           1520 ;	genAnd
   0405 FA                 1521 	mov	r2,a
                           1522 ;	Peephole 105	removed redundant mov
                           1523 ;	genIfxJump
                           1524 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0406 30 E0 1D           1525 	jnb	acc.0,00125$
                           1526 ;	Peephole 300	removed redundant label 00167$
                           1527 ;	usrp_main.c:257: GPIFTCB1 = 0x01;	SYNCDELAY;
                           1528 ;	genAssign
   0409 90 E6 D0           1529 	mov	dptr,#_GPIFTCB1
   040C 74 01              1530 	mov	a,#0x01
   040E F0                 1531 	movx	@dptr,a
                           1532 ;	genInline
   040F 00                 1533 	 nop; nop; nop; 
                           1534 ;	usrp_main.c:258: GPIFTCB0 = 0x00;	SYNCDELAY;
                           1535 ;	genAssign
   0410 90 E6 D1           1536 	mov	dptr,#_GPIFTCB0
                           1537 ;	Peephole 181	changed mov to clr
   0413 E4                 1538 	clr	a
   0414 F0                 1539 	movx	@dptr,a
                           1540 ;	genInline
   0415 00                 1541 	 nop; nop; nop; 
                           1542 ;	usrp_main.c:260: setup_flowstate_write ();
                           1543 ;	genAssign
   0416 90 E6 C8           1544 	mov	dptr,#_FLOWEQ0CTL
   0419 74 21              1545 	mov	a,#0x21
   041B F0                 1546 	movx	@dptr,a
                           1547 ;	usrp_main.c:262: SYNCDELAY;
                           1548 ;	genInline
   041C 00                 1549 	 nop; nop; nop; 
                           1550 ;	usrp_main.c:263: GPIFTRIG = bmGPIF_EP2_START | bmGPIF_WRITE; 	// start the xfer
                           1551 ;	genAssign
   041D 75 BB 00           1552 	mov	_GPIFTRIG,#0x00
                           1553 ;	usrp_main.c:264: SYNCDELAY;
                           1554 ;	genInline
   0420 00                 1555 	 nop; nop; nop; 
                           1556 ;	usrp_main.c:266: while (!(GPIFTRIG & bmGPIF_IDLE)){
   0421                    1557 00119$:
                           1558 ;	genAnd
   0421 E5 BB              1559 	mov	a,_GPIFTRIG
                           1560 ;	genIfxJump
                           1561 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0423 30 E7 FB           1562 	jnb	acc.7,00119$
                           1563 ;	Peephole 300	removed redundant label 00168$
   0426                    1564 00125$:
                           1565 ;	usrp_main.c:275: if (g_rx_enable && !(EP6CS & bmEPFULL)){	// USB end point fifo is not full...
                           1566 ;	genIfx
   0426 E5 09              1567 	mov	a,_g_rx_enable
                           1568 ;	genIfxJump
                           1569 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0428 60 A7              1570 	jz	00141$
                           1571 ;	Peephole 300	removed redundant label 00169$
                           1572 ;	genAssign
   042A 90 E6 A5           1573 	mov	dptr,#_EP6CS
   042D E0                 1574 	movx	a,@dptr
                           1575 ;	genAnd
   042E FA                 1576 	mov	r2,a
                           1577 ;	Peephole 105	removed redundant mov
                           1578 ;	genIfxJump
                           1579 ;	Peephole 108.e	removed ljmp by inverse jump logic
   042F 20 E3 9F           1580 	jb	acc.3,00141$
                           1581 ;	Peephole 300	removed redundant label 00170$
                           1582 ;	usrp_main.c:277: if (fpga_has_packet_avail ()){		// ... and FPGA has packet available
                           1583 ;	genAssign
   0432 90 E6 F4           1584 	mov	dptr,#_GPIFREADYSTAT
   0435 E0                 1585 	movx	a,@dptr
                           1586 ;	genAnd
   0436 FA                 1587 	mov	r2,a
                           1588 ;	Peephole 105	removed redundant mov
                           1589 ;	genIfxJump
                           1590 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0437 30 E1 97           1591 	jnb	acc.1,00141$
                           1592 ;	Peephole 300	removed redundant label 00171$
                           1593 ;	usrp_main.c:279: GPIFTCB1 = 0x01;	SYNCDELAY;
                           1594 ;	genAssign
   043A 90 E6 D0           1595 	mov	dptr,#_GPIFTCB1
   043D 74 01              1596 	mov	a,#0x01
   043F F0                 1597 	movx	@dptr,a
                           1598 ;	genInline
   0440 00                 1599 	 nop; nop; nop; 
                           1600 ;	usrp_main.c:280: GPIFTCB0 = 0x00;	SYNCDELAY;
                           1601 ;	genAssign
   0441 90 E6 D1           1602 	mov	dptr,#_GPIFTCB0
                           1603 ;	Peephole 181	changed mov to clr
   0444 E4                 1604 	clr	a
   0445 F0                 1605 	movx	@dptr,a
                           1606 ;	genInline
   0446 00                 1607 	 nop; nop; nop; 
                           1608 ;	usrp_main.c:282: setup_flowstate_read ();
                           1609 ;	genAssign
   0447 90 E6 C8           1610 	mov	dptr,#_FLOWEQ0CTL
   044A 74 26              1611 	mov	a,#0x26
   044C F0                 1612 	movx	@dptr,a
                           1613 ;	usrp_main.c:284: SYNCDELAY;
                           1614 ;	genInline
   044D 00                 1615 	 nop; nop; nop; 
                           1616 ;	usrp_main.c:285: GPIFTRIG = bmGPIF_EP6_START | bmGPIF_READ; 	// start the xfer
                           1617 ;	genAssign
   044E 75 BB 06           1618 	mov	_GPIFTRIG,#0x06
                           1619 ;	usrp_main.c:286: SYNCDELAY;
                           1620 ;	genInline
   0451 00                 1621 	 nop; nop; nop; 
                           1622 ;	usrp_main.c:288: while (!(GPIFTRIG & bmGPIF_IDLE)){
   0452                    1623 00130$:
                           1624 ;	genAnd
   0452 E5 BB              1625 	mov	a,_GPIFTRIG
                           1626 ;	genIfxJump
                           1627 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0454 30 E7 FB           1628 	jnb	acc.7,00130$
                           1629 ;	Peephole 300	removed redundant label 00172$
                           1630 ;	usrp_main.c:292: SYNCDELAY;
                           1631 ;	genInline
   0457 00                 1632 	 nop; nop; nop; 
                           1633 ;	usrp_main.c:293: INPKTEND = 6;	// tell USB we filled buffer (6 is our endpoint num)
                           1634 ;	genAssign
   0458 90 E6 48           1635 	mov	dptr,#_INPKTEND
   045B 74 06              1636 	mov	a,#0x06
   045D F0                 1637 	movx	@dptr,a
   045E 02 03 D1           1638 	ljmp	00141$
                           1639 ;	Peephole 259.b	removed redundant label 00143$ and ret
                           1640 ;
                           1641 ;------------------------------------------------------------
                           1642 ;Allocation info for local variables in function 'isr_tick'
                           1643 ;------------------------------------------------------------
                           1644 ;count                     Allocated with name '_isr_tick_count_1_1'
                           1645 ;------------------------------------------------------------
                           1646 ;	usrp_main.c:307: isr_tick (void) interrupt
                           1647 ;	-----------------------------------------
                           1648 ;	 function isr_tick
                           1649 ;	-----------------------------------------
   0461                    1650 _isr_tick:
   0461 C0 E0              1651 	push	acc
                           1652 ;	usrp_main.c:311: if (--count == 0){
                           1653 ;	genMinus
                           1654 ;	genMinusDec
   0463 15 0C              1655 	dec	_isr_tick_count_1_1
                           1656 ;	genIfx
   0465 E5 0C              1657 	mov	a,_isr_tick_count_1_1
                           1658 ;	genIfxJump
                           1659 ;	Peephole 108.b	removed ljmp by inverse jump logic
   0467 70 06              1660 	jnz	00102$
                           1661 ;	Peephole 300	removed redundant label 00106$
                           1662 ;	usrp_main.c:312: count = 50;
                           1663 ;	genAssign
   0469 75 0C 32           1664 	mov	_isr_tick_count_1_1,#0x32
                           1665 ;	usrp_main.c:313: USRP_LED_REG ^= bmLED0;
                           1666 ;	genXor
   046C 63 A0 40           1667 	xrl	_IOC,#0x40
   046F                    1668 00102$:
                           1669 ;	usrp_main.c:316: clear_timer_irq ();
                           1670 ;	genAssign
   046F C2 CF              1671 	clr	_TF2
                           1672 ;	Peephole 300	removed redundant label 00103$
   0471 D0 E0              1673 	pop	acc
   0473 32                 1674 	reti
                           1675 ;	eliminated unneeded push/pop psw
                           1676 ;	eliminated unneeded push/pop dpl
                           1677 ;	eliminated unneeded push/pop dph
                           1678 ;	eliminated unneeded push/pop b
                           1679 ;------------------------------------------------------------
                           1680 ;Allocation info for local variables in function 'patch_usb_descriptors'
                           1681 ;------------------------------------------------------------
                           1682 ;i                         Allocated to registers r2 
                           1683 ;ch                        Allocated to registers r3 
                           1684 ;hw_rev                    Allocated with name '_patch_usb_descriptors_hw_rev_1_1'
                           1685 ;serial_no                 Allocated with name '_patch_usb_descriptors_serial_no_1_1'
                           1686 ;------------------------------------------------------------
                           1687 ;	usrp_main.c:324: patch_usb_descriptors(void)
                           1688 ;	-----------------------------------------
                           1689 ;	 function patch_usb_descriptors
                           1690 ;	-----------------------------------------
   0474                    1691 _patch_usb_descriptors:
                           1692 ;	usrp_main.c:330: eeprom_read(I2C_ADDR_BOOT, HW_REV_OFFSET, &hw_rev, 1);	// LSB of device id
                           1693 ;	genAddrOf
   0474 75 18 00           1694 	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_hw_rev_1_1
   0477 75 19 18           1695 	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_hw_rev_1_1 >> 8)
                           1696 ;	genAssign
   047A 75 17 05           1697 	mov	_eeprom_read_PARM_2,#0x05
                           1698 ;	genAssign
   047D 75 1A 01           1699 	mov	_eeprom_read_PARM_4,#0x01
                           1700 ;	genCall
   0480 75 82 50           1701 	mov	dpl,#0x50
   0483 12 0A 05           1702 	lcall	_eeprom_read
                           1703 ;	usrp_main.c:331: usb_desc_hw_rev_binary_patch_location_0[0] = hw_rev;
                           1704 ;	genAssign
   0486 90 18 00           1705 	mov	dptr,#_patch_usb_descriptors_hw_rev_1_1
   0489 E0                 1706 	movx	a,@dptr
                           1707 ;	genPointerSet
                           1708 ;     genFarPointerSet
   048A FA                 1709 	mov	r2,a
   048B 90 E0 0C           1710 	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_0
                           1711 ;	Peephole 100	removed redundant mov
   048E F0                 1712 	movx	@dptr,a
                           1713 ;	usrp_main.c:332: usb_desc_hw_rev_binary_patch_location_1[0] = hw_rev;
                           1714 ;	genPointerSet
                           1715 ;     genFarPointerSet
   048F 90 E0 5A           1716 	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_1
   0492 EA                 1717 	mov	a,r2
   0493 F0                 1718 	movx	@dptr,a
                           1719 ;	usrp_main.c:333: usb_desc_hw_rev_ascii_patch_location_0[0] = hw_rev + '0';     // FIXME if we get > 9
                           1720 ;	genPlus
                           1721 ;     genPlusIncr
   0494 74 30              1722 	mov	a,#0x30
                           1723 ;	Peephole 236.a	used r2 instead of ar2
   0496 2A                 1724 	add	a,r2
                           1725 ;	genPointerSet
                           1726 ;     genFarPointerSet
   0497 FA                 1727 	mov	r2,a
   0498 90 E0 CE           1728 	mov	dptr,#_usb_desc_hw_rev_ascii_patch_location_0
                           1729 ;	Peephole 100	removed redundant mov
   049B F0                 1730 	movx	@dptr,a
                           1731 ;	usrp_main.c:335: eeprom_read(I2C_ADDR_BOOT, SERIAL_NO_OFFSET, serial_no, SERIAL_NO_LEN);
                           1732 ;	genAddrOf
   049C 75 18 01           1733 	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_serial_no_1_1
   049F 75 19 18           1734 	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_serial_no_1_1 >> 8)
                           1735 ;	genAssign
   04A2 75 17 F8           1736 	mov	_eeprom_read_PARM_2,#0xF8
                           1737 ;	genAssign
   04A5 75 1A 08           1738 	mov	_eeprom_read_PARM_4,#0x08
                           1739 ;	genCall
   04A8 75 82 50           1740 	mov	dpl,#0x50
   04AB 12 0A 05           1741 	lcall	_eeprom_read
                           1742 ;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
                           1743 ;	genAssign
   04AE 7A 00              1744 	mov	r2,#0x00
   04B0                    1745 00103$:
                           1746 ;	genCmpLt
                           1747 ;	genCmp
   04B0 BA 08 00           1748 	cjne	r2,#0x08,00113$
   04B3                    1749 00113$:
                           1750 ;	genIfxJump
                           1751 ;	Peephole 108.a	removed ljmp by inverse jump logic
   04B3 50 2A              1752 	jnc	00107$
                           1753 ;	Peephole 300	removed redundant label 00114$
                           1754 ;	usrp_main.c:338: unsigned char ch = serial_no[i];
                           1755 ;	genPlus
                           1756 ;	Peephole 236.g	used r2 instead of ar2
   04B5 EA                 1757 	mov	a,r2
   04B6 24 01              1758 	add	a,#_patch_usb_descriptors_serial_no_1_1
   04B8 F5 82              1759 	mov	dpl,a
                           1760 ;	Peephole 181	changed mov to clr
   04BA E4                 1761 	clr	a
   04BB 34 18              1762 	addc	a,#(_patch_usb_descriptors_serial_no_1_1 >> 8)
   04BD F5 83              1763 	mov	dph,a
                           1764 ;	genPointerGet
                           1765 ;	genFarPointerGet
   04BF E0                 1766 	movx	a,@dptr
   04C0 FB                 1767 	mov	r3,a
                           1768 ;	usrp_main.c:339: if (ch == 0xff)	// make unprogrammed EEPROM default to '0'
                           1769 ;	genCmpEq
                           1770 ;	gencjneshort
                           1771 ;	Peephole 112.b	changed ljmp to sjmp
                           1772 ;	Peephole 198.b	optimized misc jump sequence
   04C1 BB FF 02           1773 	cjne	r3,#0xFF,00102$
                           1774 ;	Peephole 200.b	removed redundant sjmp
                           1775 ;	Peephole 300	removed redundant label 00115$
                           1776 ;	Peephole 300	removed redundant label 00116$
                           1777 ;	usrp_main.c:340: ch = '0';
                           1778 ;	genAssign
   04C4 7B 30              1779 	mov	r3,#0x30
   04C6                    1780 00102$:
                           1781 ;	usrp_main.c:341: usb_desc_serial_number_ascii[i << 1] = ch;
                           1782 ;	genCast
   04C6 8A 04              1783 	mov	ar4,r2
                           1784 ;	genLeftShift
                           1785 ;	genLeftShiftLiteral
                           1786 ;	genlshTwo
                           1787 ;	peephole 177.g	optimized mov sequence
                           1788 ;	Peephole 181	changed mov to clr
   04C8 E4                 1789 	clr	a
   04C9 FD                 1790 	mov	r5,a
   04CA CC                 1791 	xch	a,r4
   04CB 25 E0              1792 	add	a,acc
   04CD CC                 1793 	xch	a,r4
   04CE 33                 1794 	rlc	a
   04CF FD                 1795 	mov	r5,a
                           1796 ;	genPlus
                           1797 ;	Peephole 236.g	used r4 instead of ar4
   04D0 EC                 1798 	mov	a,r4
   04D1 24 2A              1799 	add	a,#_usb_desc_serial_number_ascii
   04D3 F5 82              1800 	mov	dpl,a
                           1801 ;	Peephole 236.g	used r5 instead of ar5
   04D5 ED                 1802 	mov	a,r5
   04D6 34 E1              1803 	addc	a,#(_usb_desc_serial_number_ascii >> 8)
   04D8 F5 83              1804 	mov	dph,a
                           1805 ;	genPointerSet
                           1806 ;     genFarPointerSet
   04DA EB                 1807 	mov	a,r3
   04DB F0                 1808 	movx	@dptr,a
                           1809 ;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
                           1810 ;	genPlus
                           1811 ;     genPlusIncr
   04DC 0A                 1812 	inc	r2
                           1813 ;	Peephole 112.b	changed ljmp to sjmp
   04DD 80 D1              1814 	sjmp	00103$
   04DF                    1815 00107$:
   04DF 22                 1816 	ret
                           1817 ;------------------------------------------------------------
                           1818 ;Allocation info for local variables in function 'main'
                           1819 ;------------------------------------------------------------
                           1820 ;------------------------------------------------------------
                           1821 ;	usrp_main.c:346: main (void)
                           1822 ;	-----------------------------------------
                           1823 ;	 function main
                           1824 ;	-----------------------------------------
   04E0                    1825 _main:
                           1826 ;	usrp_main.c:355: memset (hash1, 0, USRP_HASH_SIZE);	// zero fpga bitstream hash.  This forces reload
                           1827 ;	genAssign
   04E0 75 39 00           1828 	mov	_memset_PARM_2,#0x00
                           1829 ;	genAssign
   04E3 75 3A 10           1830 	mov	_memset_PARM_3,#0x10
   04E6 E4                 1831 	clr	a
   04E7 F5 3B              1832 	mov	(_memset_PARM_3 + 1),a
                           1833 ;	genCall
                           1834 ;	Peephole 182.a	used 16 bit load of DPTR
   04E9 90 E1 F0           1835 	mov	dptr,#_hash1
   04EC 75 F0 00           1836 	mov	b,#0x00
   04EF 12 0B DF           1837 	lcall	_memset
                           1838 ;	usrp_main.c:357: init_usrp ();
                           1839 ;	genCall
   04F2 12 05 2C           1840 	lcall	_init_usrp
                           1841 ;	usrp_main.c:358: init_gpif ();
                           1842 ;	genCall
   04F5 12 07 B8           1843 	lcall	_init_gpif
                           1844 ;	usrp_main.c:361: IFCONFIG |= bmGSTATE;			// no conflict, start with it on
                           1845 ;	genAssign
                           1846 ;	genOr
   04F8 90 E6 01           1847 	mov	dptr,#_IFCONFIG
   04FB E0                 1848 	movx	a,@dptr
   04FC FA                 1849 	mov	r2,a
                           1850 ;	Peephole 248.a	optimized or to xdata
   04FD 44 04              1851 	orl	a,#0x04
   04FF F0                 1852 	movx	@dptr,a
                           1853 ;	usrp_main.c:363: set_led_0 (0);
                           1854 ;	genCall
   0500 75 82 00           1855 	mov	dpl,#0x00
   0503 12 05 D0           1856 	lcall	_set_led_0
                           1857 ;	usrp_main.c:364: set_led_1 (0);
                           1858 ;	genCall
   0506 75 82 00           1859 	mov	dpl,#0x00
   0509 12 05 DD           1860 	lcall	_set_led_1
                           1861 ;	usrp_main.c:366: EA = 0;		// disable all interrupts
                           1862 ;	genAssign
   050C C2 AF              1863 	clr	_EA
                           1864 ;	usrp_main.c:368: patch_usb_descriptors();
                           1865 ;	genCall
   050E 12 04 74           1866 	lcall	_patch_usb_descriptors
                           1867 ;	usrp_main.c:370: setup_autovectors ();
                           1868 ;	genCall
   0511 12 11 6E           1869 	lcall	_setup_autovectors
                           1870 ;	usrp_main.c:371: usb_install_handlers ();
                           1871 ;	genCall
   0514 12 0C E0           1872 	lcall	_usb_install_handlers
                           1873 ;	usrp_main.c:372: hook_timer_tick ((unsigned short) isr_tick);
                           1874 ;	genCast
   0517 7A 61              1875 	mov	r2,#_isr_tick
   0519 7B 04              1876 	mov	r3,#(_isr_tick >> 8)
                           1877 ;	genCall
   051B 8A 82              1878 	mov	dpl,r2
   051D 8B 83              1879 	mov	dph,r3
   051F 12 12 16           1880 	lcall	_hook_timer_tick
                           1881 ;	usrp_main.c:374: EIEX4 = 1;		// disable INT4 FIXME
                           1882 ;	genAssign
   0522 D2 EA              1883 	setb	_EIEX4
                           1884 ;	usrp_main.c:375: EA = 1;		// global interrupt enable
                           1885 ;	genAssign
   0524 D2 AF              1886 	setb	_EA
                           1887 ;	usrp_main.c:377: fx2_renumerate ();	// simulates disconnect / reconnect
                           1888 ;	genCall
   0526 12 0A 7B           1889 	lcall	_fx2_renumerate
                           1890 ;	usrp_main.c:379: main_loop ();
                           1891 ;	genCall
                           1892 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0529 02 03 9D           1893 	ljmp	_main_loop
                           1894 ;
                           1895 	.area CSEG    (CODE)
                           1896 	.area CONST   (CODE)

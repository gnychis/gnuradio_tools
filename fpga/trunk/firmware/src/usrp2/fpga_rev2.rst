                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Nov 10 2006)
                              4 ; This file generated Wed Jan 23 16:41:20 2008
                              5 ;--------------------------------------------------------
                              6 	.module fpga_rev2
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _fpga_write_reg
                             13 	.globl _bitALTERA_DCLK
                             14 	.globl _bitALTERA_DATA0
                             15 	.globl _bitS_IN
                             16 	.globl _bitS_OUT
                             17 	.globl _bitS_CLK
                             18 	.globl _EIPX6
                             19 	.globl _EIPX5
                             20 	.globl _EIPX4
                             21 	.globl _PI2C
                             22 	.globl _PUSB
                             23 	.globl _EIEX6
                             24 	.globl _EIEX5
                             25 	.globl _EIEX4
                             26 	.globl _EI2C
                             27 	.globl _EIUSB
                             28 	.globl _SMOD1
                             29 	.globl _ERESI
                             30 	.globl _RESI
                             31 	.globl _INT6
                             32 	.globl _CY
                             33 	.globl _AC
                             34 	.globl _F0
                             35 	.globl _RS1
                             36 	.globl _RS0
                             37 	.globl _OV
                             38 	.globl _FL
                             39 	.globl _P
                             40 	.globl _TF2
                             41 	.globl _EXF2
                             42 	.globl _RCLK
                             43 	.globl _TCLK
                             44 	.globl _EXEN2
                             45 	.globl _TR2
                             46 	.globl _C_T2
                             47 	.globl _CP_RL2
                             48 	.globl _SM01
                             49 	.globl _SM11
                             50 	.globl _SM21
                             51 	.globl _REN1
                             52 	.globl _TB81
                             53 	.globl _RB81
                             54 	.globl _TI1
                             55 	.globl _RI1
                             56 	.globl _PS1
                             57 	.globl _PT2
                             58 	.globl _PS0
                             59 	.globl _PT1
                             60 	.globl _PX1
                             61 	.globl _PT0
                             62 	.globl _PX0
                             63 	.globl _EA
                             64 	.globl _ES1
                             65 	.globl _ET2
                             66 	.globl _ES0
                             67 	.globl _ET1
                             68 	.globl _EX1
                             69 	.globl _ET0
                             70 	.globl _EX0
                             71 	.globl _SM0
                             72 	.globl _SM1
                             73 	.globl _SM2
                             74 	.globl _REN
                             75 	.globl _TB8
                             76 	.globl _RB8
                             77 	.globl _TI
                             78 	.globl _RI
                             79 	.globl _TF1
                             80 	.globl _TR1
                             81 	.globl _TF0
                             82 	.globl _TR0
                             83 	.globl _IE1
                             84 	.globl _IT1
                             85 	.globl _IE0
                             86 	.globl _IT0
                             87 	.globl _SEL
                             88 	.globl _EIP
                             89 	.globl _B
                             90 	.globl _EIE
                             91 	.globl _ACC
                             92 	.globl _EICON
                             93 	.globl _PSW
                             94 	.globl _TH2
                             95 	.globl _TL2
                             96 	.globl _RCAP2H
                             97 	.globl _RCAP2L
                             98 	.globl _T2CON
                             99 	.globl _SBUF1
                            100 	.globl _SCON1
                            101 	.globl _GPIFSGLDATLNOX
                            102 	.globl _GPIFSGLDATLX
                            103 	.globl _GPIFSGLDATH
                            104 	.globl _GPIFTRIG
                            105 	.globl _EP01STAT
                            106 	.globl _IP
                            107 	.globl _OEE
                            108 	.globl _OED
                            109 	.globl _OEC
                            110 	.globl _OEB
                            111 	.globl _OEA
                            112 	.globl _IOE
                            113 	.globl _IOD
                            114 	.globl _AUTOPTRSETUP
                            115 	.globl _EP68FIFOFLGS
                            116 	.globl _EP24FIFOFLGS
                            117 	.globl _EP2468STAT
                            118 	.globl _IE
                            119 	.globl _INT4CLR
                            120 	.globl _INT2CLR
                            121 	.globl _IOC
                            122 	.globl _AUTODAT2
                            123 	.globl _AUTOPTRL2
                            124 	.globl _AUTOPTRH2
                            125 	.globl _AUTODAT1
                            126 	.globl _APTR1L
                            127 	.globl _APTR1H
                            128 	.globl _SBUF0
                            129 	.globl _SCON0
                            130 	.globl _MPAGE
                            131 	.globl _EXIF
                            132 	.globl _IOB
                            133 	.globl _CKCON
                            134 	.globl _TH1
                            135 	.globl _TH0
                            136 	.globl _TL1
                            137 	.globl _TL0
                            138 	.globl _TMOD
                            139 	.globl _TCON
                            140 	.globl _PCON
                            141 	.globl _DPS
                            142 	.globl _DPH1
                            143 	.globl _DPL1
                            144 	.globl _DPH
                            145 	.globl _DPL
                            146 	.globl _SP
                            147 	.globl _IOA
                            148 	.globl _EP8FIFOBUF
                            149 	.globl _EP6FIFOBUF
                            150 	.globl _EP4FIFOBUF
                            151 	.globl _EP2FIFOBUF
                            152 	.globl _EP1INBUF
                            153 	.globl _EP1OUTBUF
                            154 	.globl _EP0BUF
                            155 	.globl _CT4
                            156 	.globl _CT3
                            157 	.globl _CT2
                            158 	.globl _CT1
                            159 	.globl _USBTEST
                            160 	.globl _TESTCFG
                            161 	.globl _DBUG
                            162 	.globl _UDMACRCQUAL
                            163 	.globl _UDMACRCL
                            164 	.globl _UDMACRCH
                            165 	.globl _GPIFHOLDAMOUNT
                            166 	.globl _FLOWSTBHPERIOD
                            167 	.globl _FLOWSTBEDGE
                            168 	.globl _FLOWSTB
                            169 	.globl _FLOWHOLDOFF
                            170 	.globl _FLOWEQ1CTL
                            171 	.globl _FLOWEQ0CTL
                            172 	.globl _FLOWLOGIC
                            173 	.globl _FLOWSTATE
                            174 	.globl _GPIFABORT
                            175 	.globl _GPIFREADYSTAT
                            176 	.globl _GPIFREADYCFG
                            177 	.globl _XGPIFSGLDATLNOX
                            178 	.globl _XGPIFSGLDATLX
                            179 	.globl _XGPIFSGLDATH
                            180 	.globl _EP8GPIFTRIG
                            181 	.globl _EP8GPIFPFSTOP
                            182 	.globl _EP8GPIFFLGSEL
                            183 	.globl _EP6GPIFTRIG
                            184 	.globl _EP6GPIFPFSTOP
                            185 	.globl _EP6GPIFFLGSEL
                            186 	.globl _EP4GPIFTRIG
                            187 	.globl _EP4GPIFPFSTOP
                            188 	.globl _EP4GPIFFLGSEL
                            189 	.globl _EP2GPIFTRIG
                            190 	.globl _EP2GPIFPFSTOP
                            191 	.globl _EP2GPIFFLGSEL
                            192 	.globl _GPIFTCB0
                            193 	.globl _GPIFTCB1
                            194 	.globl _GPIFTCB2
                            195 	.globl _GPIFTCB3
                            196 	.globl _GPIFADRL
                            197 	.globl _GPIFADRH
                            198 	.globl _GPIFCTLCFG
                            199 	.globl _GPIFIDLECTL
                            200 	.globl _GPIFIDLECS
                            201 	.globl _GPIFWFSELECT
                            202 	.globl _SETUPDAT
                            203 	.globl _SUDPTRCTL
                            204 	.globl _SUDPTRL
                            205 	.globl _SUDPTRH
                            206 	.globl _EP8FIFOBCL
                            207 	.globl _EP8FIFOBCH
                            208 	.globl _EP6FIFOBCL
                            209 	.globl _EP6FIFOBCH
                            210 	.globl _EP4FIFOBCL
                            211 	.globl _EP4FIFOBCH
                            212 	.globl _EP2FIFOBCL
                            213 	.globl _EP2FIFOBCH
                            214 	.globl _EP8FIFOFLGS
                            215 	.globl _EP6FIFOFLGS
                            216 	.globl _EP4FIFOFLGS
                            217 	.globl _EP2FIFOFLGS
                            218 	.globl _EP8CS
                            219 	.globl _EP6CS
                            220 	.globl _EP4CS
                            221 	.globl _EP2CS
                            222 	.globl _EP1INCS
                            223 	.globl _EP1OUTCS
                            224 	.globl _EP0CS
                            225 	.globl _EP8BCL
                            226 	.globl _EP8BCH
                            227 	.globl _EP6BCL
                            228 	.globl _EP6BCH
                            229 	.globl _EP4BCL
                            230 	.globl _EP4BCH
                            231 	.globl _EP2BCL
                            232 	.globl _EP2BCH
                            233 	.globl _EP1INBC
                            234 	.globl _EP1OUTBC
                            235 	.globl _EP0BCL
                            236 	.globl _EP0BCH
                            237 	.globl _FNADDR
                            238 	.globl _MICROFRAME
                            239 	.globl _USBFRAMEL
                            240 	.globl _USBFRAMEH
                            241 	.globl _TOGCTL
                            242 	.globl _WAKEUPCS
                            243 	.globl _SUSPEND
                            244 	.globl _USBCS
                            245 	.globl _XAUTODAT2
                            246 	.globl _XAUTODAT1
                            247 	.globl _I2CTL
                            248 	.globl _I2DAT
                            249 	.globl _I2CS
                            250 	.globl _PORTECFG
                            251 	.globl _PORTCCFG
                            252 	.globl _PORTACFG
                            253 	.globl _INTSETUP
                            254 	.globl _INT4IVEC
                            255 	.globl _INT2IVEC
                            256 	.globl _CLRERRCNT
                            257 	.globl _ERRCNTLIM
                            258 	.globl _USBERRIRQ
                            259 	.globl _USBERRIE
                            260 	.globl _GPIFIRQ
                            261 	.globl _GPIFIE
                            262 	.globl _EPIRQ
                            263 	.globl _EPIE
                            264 	.globl _USBIRQ
                            265 	.globl _USBIE
                            266 	.globl _NAKIRQ
                            267 	.globl _NAKIE
                            268 	.globl _IBNIRQ
                            269 	.globl _IBNIE
                            270 	.globl _EP8FIFOIRQ
                            271 	.globl _EP8FIFOIE
                            272 	.globl _EP6FIFOIRQ
                            273 	.globl _EP6FIFOIE
                            274 	.globl _EP4FIFOIRQ
                            275 	.globl _EP4FIFOIE
                            276 	.globl _EP2FIFOIRQ
                            277 	.globl _EP2FIFOIE
                            278 	.globl _OUTPKTEND
                            279 	.globl _INPKTEND
                            280 	.globl _EP8ISOINPKTS
                            281 	.globl _EP6ISOINPKTS
                            282 	.globl _EP4ISOINPKTS
                            283 	.globl _EP2ISOINPKTS
                            284 	.globl _EP8FIFOPFL
                            285 	.globl _EP8FIFOPFH
                            286 	.globl _EP6FIFOPFL
                            287 	.globl _EP6FIFOPFH
                            288 	.globl _EP4FIFOPFL
                            289 	.globl _EP4FIFOPFH
                            290 	.globl _EP2FIFOPFL
                            291 	.globl _EP2FIFOPFH
                            292 	.globl _EP8AUTOINLENL
                            293 	.globl _EP8AUTOINLENH
                            294 	.globl _EP6AUTOINLENL
                            295 	.globl _EP6AUTOINLENH
                            296 	.globl _EP4AUTOINLENL
                            297 	.globl _EP4AUTOINLENH
                            298 	.globl _EP2AUTOINLENL
                            299 	.globl _EP2AUTOINLENH
                            300 	.globl _EP8FIFOCFG
                            301 	.globl _EP6FIFOCFG
                            302 	.globl _EP4FIFOCFG
                            303 	.globl _EP2FIFOCFG
                            304 	.globl _EP8CFG
                            305 	.globl _EP6CFG
                            306 	.globl _EP4CFG
                            307 	.globl _EP2CFG
                            308 	.globl _EP1INCFG
                            309 	.globl _EP1OUTCFG
                            310 	.globl _REVCTL
                            311 	.globl _REVID
                            312 	.globl _FIFOPINPOLAR
                            313 	.globl _UART230
                            314 	.globl _BPADDRL
                            315 	.globl _BPADDRH
                            316 	.globl _BREAKPT
                            317 	.globl _FIFORESET
                            318 	.globl _PINFLAGSCD
                            319 	.globl _PINFLAGSAB
                            320 	.globl _IFCONFIG
                            321 	.globl _CPUCS
                            322 	.globl _RES_WAVEDATA_END
                            323 	.globl _GPIF_WAVE_DATA
                            324 	.globl _fpga_write_reg_PARM_2
                            325 	.globl _g_rx_reset
                            326 	.globl _g_tx_reset
                            327 	.globl _fpga_set_reset
                            328 	.globl _fpga_set_tx_enable
                            329 	.globl _fpga_set_rx_enable
                            330 	.globl _fpga_set_tx_reset
                            331 	.globl _fpga_set_rx_reset
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
   0013                     484 _g_tx_reset::
   0013                     485 	.ds 1
   0014                     486 _g_rx_reset::
   0014                     487 	.ds 1
   0015                     488 _fpga_write_reg_PARM_2:
   0015                     489 	.ds 2
                            490 ;--------------------------------------------------------
                            491 ; overlayable items in internal ram 
                            492 ;--------------------------------------------------------
                            493 	.area	OSEG    (OVR,DATA)
                            494 ;--------------------------------------------------------
                            495 ; indirectly addressable internal ram data
                            496 ;--------------------------------------------------------
                            497 	.area ISEG    (DATA)
                            498 ;--------------------------------------------------------
                            499 ; bit data
                            500 ;--------------------------------------------------------
                            501 	.area BSEG    (BIT)
                            502 ;--------------------------------------------------------
                            503 ; paged external ram data
                            504 ;--------------------------------------------------------
                            505 	.area PSEG    (PAG,XDATA)
                            506 ;--------------------------------------------------------
                            507 ; external ram data
                            508 ;--------------------------------------------------------
                            509 	.area XSEG    (XDATA)
                    E400    510 _GPIF_WAVE_DATA	=	0xe400
                    E480    511 _RES_WAVEDATA_END	=	0xe480
                    E600    512 _CPUCS	=	0xe600
                    E601    513 _IFCONFIG	=	0xe601
                    E602    514 _PINFLAGSAB	=	0xe602
                    E603    515 _PINFLAGSCD	=	0xe603
                    E604    516 _FIFORESET	=	0xe604
                    E605    517 _BREAKPT	=	0xe605
                    E606    518 _BPADDRH	=	0xe606
                    E607    519 _BPADDRL	=	0xe607
                    E608    520 _UART230	=	0xe608
                    E609    521 _FIFOPINPOLAR	=	0xe609
                    E60A    522 _REVID	=	0xe60a
                    E60B    523 _REVCTL	=	0xe60b
                    E610    524 _EP1OUTCFG	=	0xe610
                    E611    525 _EP1INCFG	=	0xe611
                    E612    526 _EP2CFG	=	0xe612
                    E613    527 _EP4CFG	=	0xe613
                    E614    528 _EP6CFG	=	0xe614
                    E615    529 _EP8CFG	=	0xe615
                    E618    530 _EP2FIFOCFG	=	0xe618
                    E619    531 _EP4FIFOCFG	=	0xe619
                    E61A    532 _EP6FIFOCFG	=	0xe61a
                    E61B    533 _EP8FIFOCFG	=	0xe61b
                    E620    534 _EP2AUTOINLENH	=	0xe620
                    E621    535 _EP2AUTOINLENL	=	0xe621
                    E622    536 _EP4AUTOINLENH	=	0xe622
                    E623    537 _EP4AUTOINLENL	=	0xe623
                    E624    538 _EP6AUTOINLENH	=	0xe624
                    E625    539 _EP6AUTOINLENL	=	0xe625
                    E626    540 _EP8AUTOINLENH	=	0xe626
                    E627    541 _EP8AUTOINLENL	=	0xe627
                    E630    542 _EP2FIFOPFH	=	0xe630
                    E631    543 _EP2FIFOPFL	=	0xe631
                    E632    544 _EP4FIFOPFH	=	0xe632
                    E633    545 _EP4FIFOPFL	=	0xe633
                    E634    546 _EP6FIFOPFH	=	0xe634
                    E635    547 _EP6FIFOPFL	=	0xe635
                    E636    548 _EP8FIFOPFH	=	0xe636
                    E637    549 _EP8FIFOPFL	=	0xe637
                    E640    550 _EP2ISOINPKTS	=	0xe640
                    E641    551 _EP4ISOINPKTS	=	0xe641
                    E642    552 _EP6ISOINPKTS	=	0xe642
                    E643    553 _EP8ISOINPKTS	=	0xe643
                    E648    554 _INPKTEND	=	0xe648
                    E649    555 _OUTPKTEND	=	0xe649
                    E650    556 _EP2FIFOIE	=	0xe650
                    E651    557 _EP2FIFOIRQ	=	0xe651
                    E652    558 _EP4FIFOIE	=	0xe652
                    E653    559 _EP4FIFOIRQ	=	0xe653
                    E654    560 _EP6FIFOIE	=	0xe654
                    E655    561 _EP6FIFOIRQ	=	0xe655
                    E656    562 _EP8FIFOIE	=	0xe656
                    E657    563 _EP8FIFOIRQ	=	0xe657
                    E658    564 _IBNIE	=	0xe658
                    E659    565 _IBNIRQ	=	0xe659
                    E65A    566 _NAKIE	=	0xe65a
                    E65B    567 _NAKIRQ	=	0xe65b
                    E65C    568 _USBIE	=	0xe65c
                    E65D    569 _USBIRQ	=	0xe65d
                    E65E    570 _EPIE	=	0xe65e
                    E65F    571 _EPIRQ	=	0xe65f
                    E660    572 _GPIFIE	=	0xe660
                    E661    573 _GPIFIRQ	=	0xe661
                    E662    574 _USBERRIE	=	0xe662
                    E663    575 _USBERRIRQ	=	0xe663
                    E664    576 _ERRCNTLIM	=	0xe664
                    E665    577 _CLRERRCNT	=	0xe665
                    E666    578 _INT2IVEC	=	0xe666
                    E667    579 _INT4IVEC	=	0xe667
                    E668    580 _INTSETUP	=	0xe668
                    E670    581 _PORTACFG	=	0xe670
                    E671    582 _PORTCCFG	=	0xe671
                    E672    583 _PORTECFG	=	0xe672
                    E678    584 _I2CS	=	0xe678
                    E679    585 _I2DAT	=	0xe679
                    E67A    586 _I2CTL	=	0xe67a
                    E67B    587 _XAUTODAT1	=	0xe67b
                    E67C    588 _XAUTODAT2	=	0xe67c
                    E680    589 _USBCS	=	0xe680
                    E681    590 _SUSPEND	=	0xe681
                    E682    591 _WAKEUPCS	=	0xe682
                    E683    592 _TOGCTL	=	0xe683
                    E684    593 _USBFRAMEH	=	0xe684
                    E685    594 _USBFRAMEL	=	0xe685
                    E686    595 _MICROFRAME	=	0xe686
                    E687    596 _FNADDR	=	0xe687
                    E68A    597 _EP0BCH	=	0xe68a
                    E68B    598 _EP0BCL	=	0xe68b
                    E68D    599 _EP1OUTBC	=	0xe68d
                    E68F    600 _EP1INBC	=	0xe68f
                    E690    601 _EP2BCH	=	0xe690
                    E691    602 _EP2BCL	=	0xe691
                    E694    603 _EP4BCH	=	0xe694
                    E695    604 _EP4BCL	=	0xe695
                    E698    605 _EP6BCH	=	0xe698
                    E699    606 _EP6BCL	=	0xe699
                    E69C    607 _EP8BCH	=	0xe69c
                    E69D    608 _EP8BCL	=	0xe69d
                    E6A0    609 _EP0CS	=	0xe6a0
                    E6A1    610 _EP1OUTCS	=	0xe6a1
                    E6A2    611 _EP1INCS	=	0xe6a2
                    E6A3    612 _EP2CS	=	0xe6a3
                    E6A4    613 _EP4CS	=	0xe6a4
                    E6A5    614 _EP6CS	=	0xe6a5
                    E6A6    615 _EP8CS	=	0xe6a6
                    E6A7    616 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    617 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    618 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    619 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    620 _EP2FIFOBCH	=	0xe6ab
                    E6AC    621 _EP2FIFOBCL	=	0xe6ac
                    E6AD    622 _EP4FIFOBCH	=	0xe6ad
                    E6AE    623 _EP4FIFOBCL	=	0xe6ae
                    E6AF    624 _EP6FIFOBCH	=	0xe6af
                    E6B0    625 _EP6FIFOBCL	=	0xe6b0
                    E6B1    626 _EP8FIFOBCH	=	0xe6b1
                    E6B2    627 _EP8FIFOBCL	=	0xe6b2
                    E6B3    628 _SUDPTRH	=	0xe6b3
                    E6B4    629 _SUDPTRL	=	0xe6b4
                    E6B5    630 _SUDPTRCTL	=	0xe6b5
                    E6B8    631 _SETUPDAT	=	0xe6b8
                    E6C0    632 _GPIFWFSELECT	=	0xe6c0
                    E6C1    633 _GPIFIDLECS	=	0xe6c1
                    E6C2    634 _GPIFIDLECTL	=	0xe6c2
                    E6C3    635 _GPIFCTLCFG	=	0xe6c3
                    E6C4    636 _GPIFADRH	=	0xe6c4
                    E6C5    637 _GPIFADRL	=	0xe6c5
                    E6CE    638 _GPIFTCB3	=	0xe6ce
                    E6CF    639 _GPIFTCB2	=	0xe6cf
                    E6D0    640 _GPIFTCB1	=	0xe6d0
                    E6D1    641 _GPIFTCB0	=	0xe6d1
                    E6D2    642 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    643 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    644 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    645 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    646 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    647 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    648 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    649 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    650 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    651 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    652 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    653 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    654 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    655 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    656 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    657 _GPIFREADYCFG	=	0xe6f3
                    E6F4    658 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    659 _GPIFABORT	=	0xe6f5
                    E6C6    660 _FLOWSTATE	=	0xe6c6
                    E6C7    661 _FLOWLOGIC	=	0xe6c7
                    E6C8    662 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    663 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    664 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    665 _FLOWSTB	=	0xe6cb
                    E6CC    666 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    667 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    668 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    669 _UDMACRCH	=	0xe67d
                    E67E    670 _UDMACRCL	=	0xe67e
                    E67F    671 _UDMACRCQUAL	=	0xe67f
                    E6F8    672 _DBUG	=	0xe6f8
                    E6F9    673 _TESTCFG	=	0xe6f9
                    E6FA    674 _USBTEST	=	0xe6fa
                    E6FB    675 _CT1	=	0xe6fb
                    E6FC    676 _CT2	=	0xe6fc
                    E6FD    677 _CT3	=	0xe6fd
                    E6FE    678 _CT4	=	0xe6fe
                    E740    679 _EP0BUF	=	0xe740
                    E780    680 _EP1OUTBUF	=	0xe780
                    E7C0    681 _EP1INBUF	=	0xe7c0
                    F000    682 _EP2FIFOBUF	=	0xf000
                    F400    683 _EP4FIFOBUF	=	0xf400
                    F800    684 _EP6FIFOBUF	=	0xf800
                    FC00    685 _EP8FIFOBUF	=	0xfc00
   180A                     686 _regval:
   180A                     687 	.ds 4
                            688 ;--------------------------------------------------------
                            689 ; external initialized ram data
                            690 ;--------------------------------------------------------
                            691 	.area HOME    (CODE)
                            692 	.area GSINIT0 (CODE)
                            693 	.area GSINIT1 (CODE)
                            694 	.area GSINIT2 (CODE)
                            695 	.area GSINIT3 (CODE)
                            696 	.area GSINIT4 (CODE)
                            697 	.area GSINIT5 (CODE)
                            698 	.area GSINIT  (CODE)
                            699 	.area GSFINAL (CODE)
                            700 	.area CSEG    (CODE)
                            701 ;--------------------------------------------------------
                            702 ; global & static initialisations
                            703 ;--------------------------------------------------------
                            704 	.area HOME    (CODE)
                            705 	.area GSINIT  (CODE)
                            706 	.area GSFINAL (CODE)
                            707 	.area GSINIT  (CODE)
                            708 ;	fpga_rev2.c:29: unsigned char g_tx_reset = 0;
                            709 ;	genAssign
   1268 75 13 00            710 	mov	_g_tx_reset,#0x00
                            711 ;	fpga_rev2.c:30: unsigned char g_rx_reset = 0;
                            712 ;	genAssign
   126B 75 14 00            713 	mov	_g_rx_reset,#0x00
                            714 ;	fpga_rev2.c:42: static xdata unsigned char regval[4] = {0, 0, 0, 0};
                            715 ;	genPointerSet
                            716 ;     genFarPointerSet
   126E 90 18 0A            717 	mov	dptr,#_regval
                            718 ;	Peephole 181	changed mov to clr
                            719 ;	genPointerSet
                            720 ;     genFarPointerSet
                            721 ;	Peephole 181	changed mov to clr
                            722 ;	Peephole 219.a	removed redundant clear
                            723 ;	genPointerSet
                            724 ;     genFarPointerSet
                            725 ;	Peephole 181	changed mov to clr
                            726 ;	genPointerSet
                            727 ;     genFarPointerSet
                            728 ;	Peephole 181	changed mov to clr
                            729 ;	Peephole 219.a	removed redundant clear
   1271 E4                  730 	clr	a
   1272 F0                  731 	movx	@dptr,a
   1273 90 18 0B            732 	mov	dptr,#(_regval + 0x0001)
   1276 F0                  733 	movx	@dptr,a
   1277 90 18 0C            734 	mov	dptr,#(_regval + 0x0002)
                            735 ;	Peephole 219.b	removed redundant clear
   127A F0                  736 	movx	@dptr,a
   127B 90 18 0D            737 	mov	dptr,#(_regval + 0x0003)
   127E F0                  738 	movx	@dptr,a
                            739 ;--------------------------------------------------------
                            740 ; Home
                            741 ;--------------------------------------------------------
                            742 	.area HOME    (CODE)
                            743 	.area CSEG    (CODE)
                            744 ;--------------------------------------------------------
                            745 ; code
                            746 ;--------------------------------------------------------
                            747 	.area CSEG    (CODE)
                            748 ;------------------------------------------------------------
                            749 ;Allocation info for local variables in function 'fpga_write_reg'
                            750 ;------------------------------------------------------------
                            751 ;regval                    Allocated with name '_fpga_write_reg_PARM_2'
                            752 ;regno                     Allocated to registers r2 
                            753 ;------------------------------------------------------------
                            754 ;	fpga_rev2.c:33: fpga_write_reg (unsigned char regno, const xdata unsigned char *regval)
                            755 ;	-----------------------------------------
                            756 ;	 function fpga_write_reg
                            757 ;	-----------------------------------------
   0709                     758 _fpga_write_reg:
                    0002    759 	ar2 = 0x02
                    0003    760 	ar3 = 0x03
                    0004    761 	ar4 = 0x04
                    0005    762 	ar5 = 0x05
                    0006    763 	ar6 = 0x06
                    0007    764 	ar7 = 0x07
                    0000    765 	ar0 = 0x00
                    0001    766 	ar1 = 0x01
                            767 ;	genReceive
   0709 AA 82               768 	mov	r2,dpl
                            769 ;	fpga_rev2.c:35: spi_write (0, 0x00 | (regno & 0x7f),
                            770 ;	genAnd
   070B 74 7F               771 	mov	a,#0x7F
   070D 5A                  772 	anl	a,r2
   070E F5 27               773 	mov	_spi_write_PARM_2,a
                            774 ;	fpga_rev2.c:38: regval, 4);
                            775 ;	genAssign
   0710 75 28 01            776 	mov	_spi_write_PARM_3,#0x01
                            777 ;	genAssign
   0713 75 29 20            778 	mov	_spi_write_PARM_4,#0x20
                            779 ;	genAssign
   0716 85 15 2A            780 	mov	_spi_write_PARM_5,_fpga_write_reg_PARM_2
   0719 85 16 2B            781 	mov	(_spi_write_PARM_5 + 1),(_fpga_write_reg_PARM_2 + 1)
                            782 ;	genAssign
   071C 75 2C 04            783 	mov	_spi_write_PARM_6,#0x04
                            784 ;	genCall
   071F 75 82 00            785 	mov	dpl,#0x00
                            786 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0722 02 08 D3            787 	ljmp	_spi_write
                            788 ;
                            789 ;------------------------------------------------------------
                            790 ;Allocation info for local variables in function 'write_fpga_master_ctrl'
                            791 ;------------------------------------------------------------
                            792 ;v                         Allocated to registers r2 
                            793 ;------------------------------------------------------------
                            794 ;	fpga_rev2.c:45: write_fpga_master_ctrl (void)
                            795 ;	-----------------------------------------
                            796 ;	 function write_fpga_master_ctrl
                            797 ;	-----------------------------------------
   0725                     798 _write_fpga_master_ctrl:
                            799 ;	fpga_rev2.c:47: unsigned char v = 0;
                            800 ;	genAssign
   0725 7A 00               801 	mov	r2,#0x00
                            802 ;	fpga_rev2.c:48: if (g_tx_enable)
                            803 ;	genIfx
   0727 E5 08               804 	mov	a,_g_tx_enable
                            805 ;	genIfxJump
                            806 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0729 60 02               807 	jz	00102$
                            808 ;	Peephole 300	removed redundant label 00115$
                            809 ;	fpga_rev2.c:49: v |= bmFR_MC_ENABLE_TX;
                            810 ;	genAssign
   072B 7A 01               811 	mov	r2,#0x01
   072D                     812 00102$:
                            813 ;	fpga_rev2.c:50: if (g_rx_enable)
                            814 ;	genIfx
   072D E5 09               815 	mov	a,_g_rx_enable
                            816 ;	genIfxJump
                            817 ;	Peephole 108.c	removed ljmp by inverse jump logic
   072F 60 03               818 	jz	00104$
                            819 ;	Peephole 300	removed redundant label 00116$
                            820 ;	fpga_rev2.c:51: v |= bmFR_MC_ENABLE_RX;
                            821 ;	genOr
   0731 43 02 02            822 	orl	ar2,#0x02
   0734                     823 00104$:
                            824 ;	fpga_rev2.c:52: if (g_tx_reset)
                            825 ;	genIfx
   0734 E5 13               826 	mov	a,_g_tx_reset
                            827 ;	genIfxJump
                            828 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0736 60 03               829 	jz	00106$
                            830 ;	Peephole 300	removed redundant label 00117$
                            831 ;	fpga_rev2.c:53: v |= bmFR_MC_RESET_TX;
                            832 ;	genOr
   0738 43 02 04            833 	orl	ar2,#0x04
   073B                     834 00106$:
                            835 ;	fpga_rev2.c:54: if (g_rx_reset)
                            836 ;	genIfx
   073B E5 14               837 	mov	a,_g_rx_reset
                            838 ;	genIfxJump
                            839 ;	Peephole 108.c	removed ljmp by inverse jump logic
   073D 60 03               840 	jz	00108$
                            841 ;	Peephole 300	removed redundant label 00118$
                            842 ;	fpga_rev2.c:55: v |= bmFR_MC_RESET_RX;
                            843 ;	genOr
   073F 43 02 08            844 	orl	ar2,#0x08
   0742                     845 00108$:
                            846 ;	fpga_rev2.c:56: regval[3] = v;
                            847 ;	genPointerSet
                            848 ;     genFarPointerSet
   0742 90 18 0D            849 	mov	dptr,#(_regval + 0x0003)
   0745 EA                  850 	mov	a,r2
   0746 F0                  851 	movx	@dptr,a
                            852 ;	fpga_rev2.c:58: fpga_write_reg (FR_MASTER_CTRL, regval);
                            853 ;	genAssign
   0747 75 15 0A            854 	mov	_fpga_write_reg_PARM_2,#_regval
   074A 75 16 18            855 	mov	(_fpga_write_reg_PARM_2 + 1),#(_regval >> 8)
                            856 ;	genCall
   074D 75 82 04            857 	mov	dpl,#0x04
                            858 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0750 02 07 09            859 	ljmp	_fpga_write_reg
                            860 ;
                            861 ;------------------------------------------------------------
                            862 ;Allocation info for local variables in function 'fpga_set_reset'
                            863 ;------------------------------------------------------------
                            864 ;on                        Allocated to registers r2 
                            865 ;------------------------------------------------------------
                            866 ;	fpga_rev2.c:64: fpga_set_reset (unsigned char on)
                            867 ;	-----------------------------------------
                            868 ;	 function fpga_set_reset
                            869 ;	-----------------------------------------
   0753                     870 _fpga_set_reset:
                            871 ;	genReceive
                            872 ;	fpga_rev2.c:66: on &= 0x1;
                            873 ;	genAnd
                            874 ;	fpga_rev2.c:68: if (on){
                            875 ;	genIfx
                            876 ;	Peephole 187	used a instead of ar2 for anl
   0753 E5 82               877 	mov	a,dpl
   0755 54 01               878 	anl	a,#0x01
   0757 FA                  879 	mov	r2,a
                            880 ;	genIfxJump
                            881 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0758 60 10               882 	jz	00102$
                            883 ;	Peephole 300	removed redundant label 00107$
                            884 ;	fpga_rev2.c:69: USRP_PC &= ~bmPC_nRESET;		// active low
                            885 ;	genAnd
   075A 53 A0 FE            886 	anl	_IOC,#0xFE
                            887 ;	fpga_rev2.c:70: g_tx_enable = 0;
                            888 ;	genAssign
   075D 75 08 00            889 	mov	_g_tx_enable,#0x00
                            890 ;	fpga_rev2.c:71: g_rx_enable = 0;
                            891 ;	genAssign
   0760 75 09 00            892 	mov	_g_rx_enable,#0x00
                            893 ;	fpga_rev2.c:72: g_tx_reset = 0;
                            894 ;	genAssign
   0763 75 13 00            895 	mov	_g_tx_reset,#0x00
                            896 ;	fpga_rev2.c:73: g_rx_reset = 0;
                            897 ;	genAssign
   0766 75 14 00            898 	mov	_g_rx_reset,#0x00
                            899 ;	Peephole 112.b	changed ljmp to sjmp
                            900 ;	Peephole 251.b	replaced sjmp to ret with ret
   0769 22                  901 	ret
   076A                     902 00102$:
                            903 ;	fpga_rev2.c:76: USRP_PC |= bmPC_nRESET;
                            904 ;	genOr
   076A 43 A0 01            905 	orl	_IOC,#0x01
                            906 ;	Peephole 300	removed redundant label 00104$
   076D 22                  907 	ret
                            908 ;------------------------------------------------------------
                            909 ;Allocation info for local variables in function 'fpga_set_tx_enable'
                            910 ;------------------------------------------------------------
                            911 ;on                        Allocated to registers r2 
                            912 ;------------------------------------------------------------
                            913 ;	fpga_rev2.c:80: fpga_set_tx_enable (unsigned char on)
                            914 ;	-----------------------------------------
                            915 ;	 function fpga_set_tx_enable
                            916 ;	-----------------------------------------
   076E                     917 _fpga_set_tx_enable:
                            918 ;	genReceive
   076E AA 82               919 	mov	r2,dpl
                            920 ;	fpga_rev2.c:82: on &= 0x1;
                            921 ;	genAnd
   0770 53 02 01            922 	anl	ar2,#0x01
                            923 ;	fpga_rev2.c:83: g_tx_enable = on;
                            924 ;	genAssign
   0773 8A 08               925 	mov	_g_tx_enable,r2
                            926 ;	fpga_rev2.c:85: write_fpga_master_ctrl ();
                            927 ;	genCall
   0775 C0 02               928 	push	ar2
   0777 12 07 25            929 	lcall	_write_fpga_master_ctrl
   077A D0 02               930 	pop	ar2
                            931 ;	fpga_rev2.c:87: if (on){
                            932 ;	genIfx
   077C EA                  933 	mov	a,r2
                            934 ;	genIfxJump
                            935 ;	Peephole 108.c	removed ljmp by inverse jump logic
   077D 60 09               936 	jz	00106$
                            937 ;	Peephole 300	removed redundant label 00109$
                            938 ;	fpga_rev2.c:88: g_tx_underrun = 0;
                            939 ;	genAssign
   077F 75 0B 00            940 	mov	_g_tx_underrun,#0x00
                            941 ;	fpga_rev2.c:89: fpga_clear_flags ();
                            942 ;	genOr
   0782 43 B1 08            943 	orl	_IOE,#0x08
                            944 ;	genAnd
   0785 53 B1 F7            945 	anl	_IOE,#0xF7
   0788                     946 00106$:
   0788 22                  947 	ret
                            948 ;------------------------------------------------------------
                            949 ;Allocation info for local variables in function 'fpga_set_rx_enable'
                            950 ;------------------------------------------------------------
                            951 ;on                        Allocated to registers r2 
                            952 ;------------------------------------------------------------
                            953 ;	fpga_rev2.c:94: fpga_set_rx_enable (unsigned char on)
                            954 ;	-----------------------------------------
                            955 ;	 function fpga_set_rx_enable
                            956 ;	-----------------------------------------
   0789                     957 _fpga_set_rx_enable:
                            958 ;	genReceive
   0789 AA 82               959 	mov	r2,dpl
                            960 ;	fpga_rev2.c:96: on &= 0x1;
                            961 ;	genAnd
   078B 53 02 01            962 	anl	ar2,#0x01
                            963 ;	fpga_rev2.c:97: g_rx_enable = on;
                            964 ;	genAssign
   078E 8A 09               965 	mov	_g_rx_enable,r2
                            966 ;	fpga_rev2.c:99: write_fpga_master_ctrl ();
                            967 ;	genCall
   0790 C0 02               968 	push	ar2
   0792 12 07 25            969 	lcall	_write_fpga_master_ctrl
   0795 D0 02               970 	pop	ar2
                            971 ;	fpga_rev2.c:100: if (on){
                            972 ;	genIfx
   0797 EA                  973 	mov	a,r2
                            974 ;	genIfxJump
                            975 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0798 60 09               976 	jz	00106$
                            977 ;	Peephole 300	removed redundant label 00109$
                            978 ;	fpga_rev2.c:101: g_rx_overrun = 0;
                            979 ;	genAssign
   079A 75 0A 00            980 	mov	_g_rx_overrun,#0x00
                            981 ;	fpga_rev2.c:102: fpga_clear_flags ();
                            982 ;	genOr
   079D 43 B1 08            983 	orl	_IOE,#0x08
                            984 ;	genAnd
   07A0 53 B1 F7            985 	anl	_IOE,#0xF7
   07A3                     986 00106$:
   07A3 22                  987 	ret
                            988 ;------------------------------------------------------------
                            989 ;Allocation info for local variables in function 'fpga_set_tx_reset'
                            990 ;------------------------------------------------------------
                            991 ;on                        Allocated to registers r2 
                            992 ;------------------------------------------------------------
                            993 ;	fpga_rev2.c:107: fpga_set_tx_reset (unsigned char on)
                            994 ;	-----------------------------------------
                            995 ;	 function fpga_set_tx_reset
                            996 ;	-----------------------------------------
   07A4                     997 _fpga_set_tx_reset:
                            998 ;	genReceive
   07A4 AA 82               999 	mov	r2,dpl
                           1000 ;	fpga_rev2.c:109: on &= 0x1;
                           1001 ;	genAnd
   07A6 74 01              1002 	mov	a,#0x01
   07A8 5A                 1003 	anl	a,r2
   07A9 F5 13              1004 	mov	_g_tx_reset,a
                           1005 ;	fpga_rev2.c:112: write_fpga_master_ctrl ();
                           1006 ;	genCall
                           1007 ;	Peephole 253.b	replaced lcall/ret with ljmp
   07AB 02 07 25           1008 	ljmp	_write_fpga_master_ctrl
                           1009 ;
                           1010 ;------------------------------------------------------------
                           1011 ;Allocation info for local variables in function 'fpga_set_rx_reset'
                           1012 ;------------------------------------------------------------
                           1013 ;on                        Allocated to registers r2 
                           1014 ;------------------------------------------------------------
                           1015 ;	fpga_rev2.c:116: fpga_set_rx_reset (unsigned char on)
                           1016 ;	-----------------------------------------
                           1017 ;	 function fpga_set_rx_reset
                           1018 ;	-----------------------------------------
   07AE                    1019 _fpga_set_rx_reset:
                           1020 ;	genReceive
   07AE AA 82              1021 	mov	r2,dpl
                           1022 ;	fpga_rev2.c:118: on &= 0x1;
                           1023 ;	genAnd
   07B0 74 01              1024 	mov	a,#0x01
   07B2 5A                 1025 	anl	a,r2
   07B3 F5 14              1026 	mov	_g_rx_reset,a
                           1027 ;	fpga_rev2.c:121: write_fpga_master_ctrl ();
                           1028 ;	genCall
                           1029 ;	Peephole 253.b	replaced lcall/ret with ljmp
   07B5 02 07 25           1030 	ljmp	_write_fpga_master_ctrl
                           1031 ;
                           1032 	.area CSEG    (CODE)
                           1033 	.area CONST   (CODE)

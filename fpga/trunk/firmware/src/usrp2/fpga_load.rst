                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Nov 10 2006)
                              4 ; This file generated Wed Jan 23 16:41:20 2008
                              5 ;--------------------------------------------------------
                              6 	.module fpga_load
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _bitALTERA_DCLK
                             13 	.globl _bitALTERA_DATA0
                             14 	.globl _bitS_IN
                             15 	.globl _bitS_OUT
                             16 	.globl _bitS_CLK
                             17 	.globl _EIPX6
                             18 	.globl _EIPX5
                             19 	.globl _EIPX4
                             20 	.globl _PI2C
                             21 	.globl _PUSB
                             22 	.globl _EIEX6
                             23 	.globl _EIEX5
                             24 	.globl _EIEX4
                             25 	.globl _EI2C
                             26 	.globl _EIUSB
                             27 	.globl _SMOD1
                             28 	.globl _ERESI
                             29 	.globl _RESI
                             30 	.globl _INT6
                             31 	.globl _CY
                             32 	.globl _AC
                             33 	.globl _F0
                             34 	.globl _RS1
                             35 	.globl _RS0
                             36 	.globl _OV
                             37 	.globl _FL
                             38 	.globl _P
                             39 	.globl _TF2
                             40 	.globl _EXF2
                             41 	.globl _RCLK
                             42 	.globl _TCLK
                             43 	.globl _EXEN2
                             44 	.globl _TR2
                             45 	.globl _C_T2
                             46 	.globl _CP_RL2
                             47 	.globl _SM01
                             48 	.globl _SM11
                             49 	.globl _SM21
                             50 	.globl _REN1
                             51 	.globl _TB81
                             52 	.globl _RB81
                             53 	.globl _TI1
                             54 	.globl _RI1
                             55 	.globl _PS1
                             56 	.globl _PT2
                             57 	.globl _PS0
                             58 	.globl _PT1
                             59 	.globl _PX1
                             60 	.globl _PT0
                             61 	.globl _PX0
                             62 	.globl _EA
                             63 	.globl _ES1
                             64 	.globl _ET2
                             65 	.globl _ES0
                             66 	.globl _ET1
                             67 	.globl _EX1
                             68 	.globl _ET0
                             69 	.globl _EX0
                             70 	.globl _SM0
                             71 	.globl _SM1
                             72 	.globl _SM2
                             73 	.globl _REN
                             74 	.globl _TB8
                             75 	.globl _RB8
                             76 	.globl _TI
                             77 	.globl _RI
                             78 	.globl _TF1
                             79 	.globl _TR1
                             80 	.globl _TF0
                             81 	.globl _TR0
                             82 	.globl _IE1
                             83 	.globl _IT1
                             84 	.globl _IE0
                             85 	.globl _IT0
                             86 	.globl _SEL
                             87 	.globl _EIP
                             88 	.globl _B
                             89 	.globl _EIE
                             90 	.globl _ACC
                             91 	.globl _EICON
                             92 	.globl _PSW
                             93 	.globl _TH2
                             94 	.globl _TL2
                             95 	.globl _RCAP2H
                             96 	.globl _RCAP2L
                             97 	.globl _T2CON
                             98 	.globl _SBUF1
                             99 	.globl _SCON1
                            100 	.globl _GPIFSGLDATLNOX
                            101 	.globl _GPIFSGLDATLX
                            102 	.globl _GPIFSGLDATH
                            103 	.globl _GPIFTRIG
                            104 	.globl _EP01STAT
                            105 	.globl _IP
                            106 	.globl _OEE
                            107 	.globl _OED
                            108 	.globl _OEC
                            109 	.globl _OEB
                            110 	.globl _OEA
                            111 	.globl _IOE
                            112 	.globl _IOD
                            113 	.globl _AUTOPTRSETUP
                            114 	.globl _EP68FIFOFLGS
                            115 	.globl _EP24FIFOFLGS
                            116 	.globl _EP2468STAT
                            117 	.globl _IE
                            118 	.globl _INT4CLR
                            119 	.globl _INT2CLR
                            120 	.globl _IOC
                            121 	.globl _AUTODAT2
                            122 	.globl _AUTOPTRL2
                            123 	.globl _AUTOPTRH2
                            124 	.globl _AUTODAT1
                            125 	.globl _APTR1L
                            126 	.globl _APTR1H
                            127 	.globl _SBUF0
                            128 	.globl _SCON0
                            129 	.globl _MPAGE
                            130 	.globl _EXIF
                            131 	.globl _IOB
                            132 	.globl _CKCON
                            133 	.globl _TH1
                            134 	.globl _TH0
                            135 	.globl _TL1
                            136 	.globl _TL0
                            137 	.globl _TMOD
                            138 	.globl _TCON
                            139 	.globl _PCON
                            140 	.globl _DPS
                            141 	.globl _DPH1
                            142 	.globl _DPL1
                            143 	.globl _DPH
                            144 	.globl _DPL
                            145 	.globl _SP
                            146 	.globl _IOA
                            147 	.globl _EP8FIFOBUF
                            148 	.globl _EP6FIFOBUF
                            149 	.globl _EP4FIFOBUF
                            150 	.globl _EP2FIFOBUF
                            151 	.globl _EP1INBUF
                            152 	.globl _EP1OUTBUF
                            153 	.globl _EP0BUF
                            154 	.globl _CT4
                            155 	.globl _CT3
                            156 	.globl _CT2
                            157 	.globl _CT1
                            158 	.globl _USBTEST
                            159 	.globl _TESTCFG
                            160 	.globl _DBUG
                            161 	.globl _UDMACRCQUAL
                            162 	.globl _UDMACRCL
                            163 	.globl _UDMACRCH
                            164 	.globl _GPIFHOLDAMOUNT
                            165 	.globl _FLOWSTBHPERIOD
                            166 	.globl _FLOWSTBEDGE
                            167 	.globl _FLOWSTB
                            168 	.globl _FLOWHOLDOFF
                            169 	.globl _FLOWEQ1CTL
                            170 	.globl _FLOWEQ0CTL
                            171 	.globl _FLOWLOGIC
                            172 	.globl _FLOWSTATE
                            173 	.globl _GPIFABORT
                            174 	.globl _GPIFREADYSTAT
                            175 	.globl _GPIFREADYCFG
                            176 	.globl _XGPIFSGLDATLNOX
                            177 	.globl _XGPIFSGLDATLX
                            178 	.globl _XGPIFSGLDATH
                            179 	.globl _EP8GPIFTRIG
                            180 	.globl _EP8GPIFPFSTOP
                            181 	.globl _EP8GPIFFLGSEL
                            182 	.globl _EP6GPIFTRIG
                            183 	.globl _EP6GPIFPFSTOP
                            184 	.globl _EP6GPIFFLGSEL
                            185 	.globl _EP4GPIFTRIG
                            186 	.globl _EP4GPIFPFSTOP
                            187 	.globl _EP4GPIFFLGSEL
                            188 	.globl _EP2GPIFTRIG
                            189 	.globl _EP2GPIFPFSTOP
                            190 	.globl _EP2GPIFFLGSEL
                            191 	.globl _GPIFTCB0
                            192 	.globl _GPIFTCB1
                            193 	.globl _GPIFTCB2
                            194 	.globl _GPIFTCB3
                            195 	.globl _GPIFADRL
                            196 	.globl _GPIFADRH
                            197 	.globl _GPIFCTLCFG
                            198 	.globl _GPIFIDLECTL
                            199 	.globl _GPIFIDLECS
                            200 	.globl _GPIFWFSELECT
                            201 	.globl _SETUPDAT
                            202 	.globl _SUDPTRCTL
                            203 	.globl _SUDPTRL
                            204 	.globl _SUDPTRH
                            205 	.globl _EP8FIFOBCL
                            206 	.globl _EP8FIFOBCH
                            207 	.globl _EP6FIFOBCL
                            208 	.globl _EP6FIFOBCH
                            209 	.globl _EP4FIFOBCL
                            210 	.globl _EP4FIFOBCH
                            211 	.globl _EP2FIFOBCL
                            212 	.globl _EP2FIFOBCH
                            213 	.globl _EP8FIFOFLGS
                            214 	.globl _EP6FIFOFLGS
                            215 	.globl _EP4FIFOFLGS
                            216 	.globl _EP2FIFOFLGS
                            217 	.globl _EP8CS
                            218 	.globl _EP6CS
                            219 	.globl _EP4CS
                            220 	.globl _EP2CS
                            221 	.globl _EP1INCS
                            222 	.globl _EP1OUTCS
                            223 	.globl _EP0CS
                            224 	.globl _EP8BCL
                            225 	.globl _EP8BCH
                            226 	.globl _EP6BCL
                            227 	.globl _EP6BCH
                            228 	.globl _EP4BCL
                            229 	.globl _EP4BCH
                            230 	.globl _EP2BCL
                            231 	.globl _EP2BCH
                            232 	.globl _EP1INBC
                            233 	.globl _EP1OUTBC
                            234 	.globl _EP0BCL
                            235 	.globl _EP0BCH
                            236 	.globl _FNADDR
                            237 	.globl _MICROFRAME
                            238 	.globl _USBFRAMEL
                            239 	.globl _USBFRAMEH
                            240 	.globl _TOGCTL
                            241 	.globl _WAKEUPCS
                            242 	.globl _SUSPEND
                            243 	.globl _USBCS
                            244 	.globl _XAUTODAT2
                            245 	.globl _XAUTODAT1
                            246 	.globl _I2CTL
                            247 	.globl _I2DAT
                            248 	.globl _I2CS
                            249 	.globl _PORTECFG
                            250 	.globl _PORTCCFG
                            251 	.globl _PORTACFG
                            252 	.globl _INTSETUP
                            253 	.globl _INT4IVEC
                            254 	.globl _INT2IVEC
                            255 	.globl _CLRERRCNT
                            256 	.globl _ERRCNTLIM
                            257 	.globl _USBERRIRQ
                            258 	.globl _USBERRIE
                            259 	.globl _GPIFIRQ
                            260 	.globl _GPIFIE
                            261 	.globl _EPIRQ
                            262 	.globl _EPIE
                            263 	.globl _USBIRQ
                            264 	.globl _USBIE
                            265 	.globl _NAKIRQ
                            266 	.globl _NAKIE
                            267 	.globl _IBNIRQ
                            268 	.globl _IBNIE
                            269 	.globl _EP8FIFOIRQ
                            270 	.globl _EP8FIFOIE
                            271 	.globl _EP6FIFOIRQ
                            272 	.globl _EP6FIFOIE
                            273 	.globl _EP4FIFOIRQ
                            274 	.globl _EP4FIFOIE
                            275 	.globl _EP2FIFOIRQ
                            276 	.globl _EP2FIFOIE
                            277 	.globl _OUTPKTEND
                            278 	.globl _INPKTEND
                            279 	.globl _EP8ISOINPKTS
                            280 	.globl _EP6ISOINPKTS
                            281 	.globl _EP4ISOINPKTS
                            282 	.globl _EP2ISOINPKTS
                            283 	.globl _EP8FIFOPFL
                            284 	.globl _EP8FIFOPFH
                            285 	.globl _EP6FIFOPFL
                            286 	.globl _EP6FIFOPFH
                            287 	.globl _EP4FIFOPFL
                            288 	.globl _EP4FIFOPFH
                            289 	.globl _EP2FIFOPFL
                            290 	.globl _EP2FIFOPFH
                            291 	.globl _EP8AUTOINLENL
                            292 	.globl _EP8AUTOINLENH
                            293 	.globl _EP6AUTOINLENL
                            294 	.globl _EP6AUTOINLENH
                            295 	.globl _EP4AUTOINLENL
                            296 	.globl _EP4AUTOINLENH
                            297 	.globl _EP2AUTOINLENL
                            298 	.globl _EP2AUTOINLENH
                            299 	.globl _EP8FIFOCFG
                            300 	.globl _EP6FIFOCFG
                            301 	.globl _EP4FIFOCFG
                            302 	.globl _EP2FIFOCFG
                            303 	.globl _EP8CFG
                            304 	.globl _EP6CFG
                            305 	.globl _EP4CFG
                            306 	.globl _EP2CFG
                            307 	.globl _EP1INCFG
                            308 	.globl _EP1OUTCFG
                            309 	.globl _REVCTL
                            310 	.globl _REVID
                            311 	.globl _FIFOPINPOLAR
                            312 	.globl _UART230
                            313 	.globl _BPADDRL
                            314 	.globl _BPADDRH
                            315 	.globl _BREAKPT
                            316 	.globl _FIFORESET
                            317 	.globl _PINFLAGSCD
                            318 	.globl _PINFLAGSAB
                            319 	.globl _IFCONFIG
                            320 	.globl _CPUCS
                            321 	.globl _RES_WAVEDATA_END
                            322 	.globl _GPIF_WAVE_DATA
                            323 	.globl _fpga_load_xfer_PARM_2
                            324 	.globl _clock_out_bytes_PARM_2
                            325 	.globl _fpga_load_begin
                            326 	.globl _fpga_load_xfer
                            327 	.globl _fpga_load_end
                            328 ;--------------------------------------------------------
                            329 ; special function registers
                            330 ;--------------------------------------------------------
                            331 	.area RSEG    (DATA)
                    0080    332 _IOA	=	0x0080
                    0081    333 _SP	=	0x0081
                    0082    334 _DPL	=	0x0082
                    0083    335 _DPH	=	0x0083
                    0084    336 _DPL1	=	0x0084
                    0085    337 _DPH1	=	0x0085
                    0086    338 _DPS	=	0x0086
                    0087    339 _PCON	=	0x0087
                    0088    340 _TCON	=	0x0088
                    0089    341 _TMOD	=	0x0089
                    008A    342 _TL0	=	0x008a
                    008B    343 _TL1	=	0x008b
                    008C    344 _TH0	=	0x008c
                    008D    345 _TH1	=	0x008d
                    008E    346 _CKCON	=	0x008e
                    0090    347 _IOB	=	0x0090
                    0091    348 _EXIF	=	0x0091
                    0092    349 _MPAGE	=	0x0092
                    0098    350 _SCON0	=	0x0098
                    0099    351 _SBUF0	=	0x0099
                    009A    352 _APTR1H	=	0x009a
                    009B    353 _APTR1L	=	0x009b
                    009C    354 _AUTODAT1	=	0x009c
                    009D    355 _AUTOPTRH2	=	0x009d
                    009E    356 _AUTOPTRL2	=	0x009e
                    009F    357 _AUTODAT2	=	0x009f
                    00A0    358 _IOC	=	0x00a0
                    00A1    359 _INT2CLR	=	0x00a1
                    00A2    360 _INT4CLR	=	0x00a2
                    00A8    361 _IE	=	0x00a8
                    00AA    362 _EP2468STAT	=	0x00aa
                    00AB    363 _EP24FIFOFLGS	=	0x00ab
                    00AC    364 _EP68FIFOFLGS	=	0x00ac
                    00AF    365 _AUTOPTRSETUP	=	0x00af
                    00B0    366 _IOD	=	0x00b0
                    00B1    367 _IOE	=	0x00b1
                    00B2    368 _OEA	=	0x00b2
                    00B3    369 _OEB	=	0x00b3
                    00B4    370 _OEC	=	0x00b4
                    00B5    371 _OED	=	0x00b5
                    00B6    372 _OEE	=	0x00b6
                    00B8    373 _IP	=	0x00b8
                    00BA    374 _EP01STAT	=	0x00ba
                    00BB    375 _GPIFTRIG	=	0x00bb
                    00BD    376 _GPIFSGLDATH	=	0x00bd
                    00BE    377 _GPIFSGLDATLX	=	0x00be
                    00BF    378 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    379 _SCON1	=	0x00c0
                    00C1    380 _SBUF1	=	0x00c1
                    00C8    381 _T2CON	=	0x00c8
                    00CA    382 _RCAP2L	=	0x00ca
                    00CB    383 _RCAP2H	=	0x00cb
                    00CC    384 _TL2	=	0x00cc
                    00CD    385 _TH2	=	0x00cd
                    00D0    386 _PSW	=	0x00d0
                    00D8    387 _EICON	=	0x00d8
                    00E0    388 _ACC	=	0x00e0
                    00E8    389 _EIE	=	0x00e8
                    00F0    390 _B	=	0x00f0
                    00F8    391 _EIP	=	0x00f8
                            392 ;--------------------------------------------------------
                            393 ; special function bits
                            394 ;--------------------------------------------------------
                            395 	.area RSEG    (DATA)
                    0086    396 _SEL	=	0x0086
                    0088    397 _IT0	=	0x0088
                    0089    398 _IE0	=	0x0089
                    008A    399 _IT1	=	0x008a
                    008B    400 _IE1	=	0x008b
                    008C    401 _TR0	=	0x008c
                    008D    402 _TF0	=	0x008d
                    008E    403 _TR1	=	0x008e
                    008F    404 _TF1	=	0x008f
                    0098    405 _RI	=	0x0098
                    0099    406 _TI	=	0x0099
                    009A    407 _RB8	=	0x009a
                    009B    408 _TB8	=	0x009b
                    009C    409 _REN	=	0x009c
                    009D    410 _SM2	=	0x009d
                    009E    411 _SM1	=	0x009e
                    009F    412 _SM0	=	0x009f
                    00A8    413 _EX0	=	0x00a8
                    00A9    414 _ET0	=	0x00a9
                    00AA    415 _EX1	=	0x00aa
                    00AB    416 _ET1	=	0x00ab
                    00AC    417 _ES0	=	0x00ac
                    00AD    418 _ET2	=	0x00ad
                    00AE    419 _ES1	=	0x00ae
                    00AF    420 _EA	=	0x00af
                    00B8    421 _PX0	=	0x00b8
                    00B9    422 _PT0	=	0x00b9
                    00BA    423 _PX1	=	0x00ba
                    00BB    424 _PT1	=	0x00bb
                    00BC    425 _PS0	=	0x00bc
                    00BD    426 _PT2	=	0x00bd
                    00BE    427 _PS1	=	0x00be
                    00C0    428 _RI1	=	0x00c0
                    00C1    429 _TI1	=	0x00c1
                    00C2    430 _RB81	=	0x00c2
                    00C3    431 _TB81	=	0x00c3
                    00C4    432 _REN1	=	0x00c4
                    00C5    433 _SM21	=	0x00c5
                    00C6    434 _SM11	=	0x00c6
                    00C7    435 _SM01	=	0x00c7
                    00C8    436 _CP_RL2	=	0x00c8
                    00C9    437 _C_T2	=	0x00c9
                    00CA    438 _TR2	=	0x00ca
                    00CB    439 _EXEN2	=	0x00cb
                    00CC    440 _TCLK	=	0x00cc
                    00CD    441 _RCLK	=	0x00cd
                    00CE    442 _EXF2	=	0x00ce
                    00CF    443 _TF2	=	0x00cf
                    00D0    444 _P	=	0x00d0
                    00D1    445 _FL	=	0x00d1
                    00D2    446 _OV	=	0x00d2
                    00D3    447 _RS0	=	0x00d3
                    00D4    448 _RS1	=	0x00d4
                    00D5    449 _F0	=	0x00d5
                    00D6    450 _AC	=	0x00d6
                    00D7    451 _CY	=	0x00d7
                    00DB    452 _INT6	=	0x00db
                    00DC    453 _RESI	=	0x00dc
                    00DD    454 _ERESI	=	0x00dd
                    00DF    455 _SMOD1	=	0x00df
                    00E8    456 _EIUSB	=	0x00e8
                    00E9    457 _EI2C	=	0x00e9
                    00EA    458 _EIEX4	=	0x00ea
                    00EB    459 _EIEX5	=	0x00eb
                    00EC    460 _EIEX6	=	0x00ec
                    00F8    461 _PUSB	=	0x00f8
                    00F9    462 _PI2C	=	0x00f9
                    00FA    463 _EIPX4	=	0x00fa
                    00FB    464 _EIPX5	=	0x00fb
                    00FC    465 _EIPX6	=	0x00fc
                    0080    466 _bitS_CLK	=	0x0080
                    0081    467 _bitS_OUT	=	0x0081
                    0082    468 _bitS_IN	=	0x0082
                    00A1    469 _bitALTERA_DATA0	=	0x00a1
                    00A3    470 _bitALTERA_DCLK	=	0x00a3
                            471 ;--------------------------------------------------------
                            472 ; overlayable register banks
                            473 ;--------------------------------------------------------
                            474 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     475 	.ds 8
                            476 ;--------------------------------------------------------
                            477 ; internal ram data
                            478 ;--------------------------------------------------------
                            479 	.area DSEG    (DATA)
   0010                     480 _clock_out_bytes_PARM_2:
   0010                     481 	.ds 2
   0012                     482 _fpga_load_xfer_PARM_2:
   0012                     483 	.ds 1
                            484 ;--------------------------------------------------------
                            485 ; overlayable items in internal ram 
                            486 ;--------------------------------------------------------
                            487 	.area	OSEG    (OVR,DATA)
                            488 	.area	OSEG    (OVR,DATA)
                            489 ;--------------------------------------------------------
                            490 ; indirectly addressable internal ram data
                            491 ;--------------------------------------------------------
                            492 	.area ISEG    (DATA)
                            493 ;--------------------------------------------------------
                            494 ; bit data
                            495 ;--------------------------------------------------------
                            496 	.area BSEG    (BIT)
                            497 ;--------------------------------------------------------
                            498 ; paged external ram data
                            499 ;--------------------------------------------------------
                            500 	.area PSEG    (PAG,XDATA)
                            501 ;--------------------------------------------------------
                            502 ; external ram data
                            503 ;--------------------------------------------------------
                            504 	.area XSEG    (XDATA)
                    E400    505 _GPIF_WAVE_DATA	=	0xe400
                    E480    506 _RES_WAVEDATA_END	=	0xe480
                    E600    507 _CPUCS	=	0xe600
                    E601    508 _IFCONFIG	=	0xe601
                    E602    509 _PINFLAGSAB	=	0xe602
                    E603    510 _PINFLAGSCD	=	0xe603
                    E604    511 _FIFORESET	=	0xe604
                    E605    512 _BREAKPT	=	0xe605
                    E606    513 _BPADDRH	=	0xe606
                    E607    514 _BPADDRL	=	0xe607
                    E608    515 _UART230	=	0xe608
                    E609    516 _FIFOPINPOLAR	=	0xe609
                    E60A    517 _REVID	=	0xe60a
                    E60B    518 _REVCTL	=	0xe60b
                    E610    519 _EP1OUTCFG	=	0xe610
                    E611    520 _EP1INCFG	=	0xe611
                    E612    521 _EP2CFG	=	0xe612
                    E613    522 _EP4CFG	=	0xe613
                    E614    523 _EP6CFG	=	0xe614
                    E615    524 _EP8CFG	=	0xe615
                    E618    525 _EP2FIFOCFG	=	0xe618
                    E619    526 _EP4FIFOCFG	=	0xe619
                    E61A    527 _EP6FIFOCFG	=	0xe61a
                    E61B    528 _EP8FIFOCFG	=	0xe61b
                    E620    529 _EP2AUTOINLENH	=	0xe620
                    E621    530 _EP2AUTOINLENL	=	0xe621
                    E622    531 _EP4AUTOINLENH	=	0xe622
                    E623    532 _EP4AUTOINLENL	=	0xe623
                    E624    533 _EP6AUTOINLENH	=	0xe624
                    E625    534 _EP6AUTOINLENL	=	0xe625
                    E626    535 _EP8AUTOINLENH	=	0xe626
                    E627    536 _EP8AUTOINLENL	=	0xe627
                    E630    537 _EP2FIFOPFH	=	0xe630
                    E631    538 _EP2FIFOPFL	=	0xe631
                    E632    539 _EP4FIFOPFH	=	0xe632
                    E633    540 _EP4FIFOPFL	=	0xe633
                    E634    541 _EP6FIFOPFH	=	0xe634
                    E635    542 _EP6FIFOPFL	=	0xe635
                    E636    543 _EP8FIFOPFH	=	0xe636
                    E637    544 _EP8FIFOPFL	=	0xe637
                    E640    545 _EP2ISOINPKTS	=	0xe640
                    E641    546 _EP4ISOINPKTS	=	0xe641
                    E642    547 _EP6ISOINPKTS	=	0xe642
                    E643    548 _EP8ISOINPKTS	=	0xe643
                    E648    549 _INPKTEND	=	0xe648
                    E649    550 _OUTPKTEND	=	0xe649
                    E650    551 _EP2FIFOIE	=	0xe650
                    E651    552 _EP2FIFOIRQ	=	0xe651
                    E652    553 _EP4FIFOIE	=	0xe652
                    E653    554 _EP4FIFOIRQ	=	0xe653
                    E654    555 _EP6FIFOIE	=	0xe654
                    E655    556 _EP6FIFOIRQ	=	0xe655
                    E656    557 _EP8FIFOIE	=	0xe656
                    E657    558 _EP8FIFOIRQ	=	0xe657
                    E658    559 _IBNIE	=	0xe658
                    E659    560 _IBNIRQ	=	0xe659
                    E65A    561 _NAKIE	=	0xe65a
                    E65B    562 _NAKIRQ	=	0xe65b
                    E65C    563 _USBIE	=	0xe65c
                    E65D    564 _USBIRQ	=	0xe65d
                    E65E    565 _EPIE	=	0xe65e
                    E65F    566 _EPIRQ	=	0xe65f
                    E660    567 _GPIFIE	=	0xe660
                    E661    568 _GPIFIRQ	=	0xe661
                    E662    569 _USBERRIE	=	0xe662
                    E663    570 _USBERRIRQ	=	0xe663
                    E664    571 _ERRCNTLIM	=	0xe664
                    E665    572 _CLRERRCNT	=	0xe665
                    E666    573 _INT2IVEC	=	0xe666
                    E667    574 _INT4IVEC	=	0xe667
                    E668    575 _INTSETUP	=	0xe668
                    E670    576 _PORTACFG	=	0xe670
                    E671    577 _PORTCCFG	=	0xe671
                    E672    578 _PORTECFG	=	0xe672
                    E678    579 _I2CS	=	0xe678
                    E679    580 _I2DAT	=	0xe679
                    E67A    581 _I2CTL	=	0xe67a
                    E67B    582 _XAUTODAT1	=	0xe67b
                    E67C    583 _XAUTODAT2	=	0xe67c
                    E680    584 _USBCS	=	0xe680
                    E681    585 _SUSPEND	=	0xe681
                    E682    586 _WAKEUPCS	=	0xe682
                    E683    587 _TOGCTL	=	0xe683
                    E684    588 _USBFRAMEH	=	0xe684
                    E685    589 _USBFRAMEL	=	0xe685
                    E686    590 _MICROFRAME	=	0xe686
                    E687    591 _FNADDR	=	0xe687
                    E68A    592 _EP0BCH	=	0xe68a
                    E68B    593 _EP0BCL	=	0xe68b
                    E68D    594 _EP1OUTBC	=	0xe68d
                    E68F    595 _EP1INBC	=	0xe68f
                    E690    596 _EP2BCH	=	0xe690
                    E691    597 _EP2BCL	=	0xe691
                    E694    598 _EP4BCH	=	0xe694
                    E695    599 _EP4BCL	=	0xe695
                    E698    600 _EP6BCH	=	0xe698
                    E699    601 _EP6BCL	=	0xe699
                    E69C    602 _EP8BCH	=	0xe69c
                    E69D    603 _EP8BCL	=	0xe69d
                    E6A0    604 _EP0CS	=	0xe6a0
                    E6A1    605 _EP1OUTCS	=	0xe6a1
                    E6A2    606 _EP1INCS	=	0xe6a2
                    E6A3    607 _EP2CS	=	0xe6a3
                    E6A4    608 _EP4CS	=	0xe6a4
                    E6A5    609 _EP6CS	=	0xe6a5
                    E6A6    610 _EP8CS	=	0xe6a6
                    E6A7    611 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    612 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    613 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    614 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    615 _EP2FIFOBCH	=	0xe6ab
                    E6AC    616 _EP2FIFOBCL	=	0xe6ac
                    E6AD    617 _EP4FIFOBCH	=	0xe6ad
                    E6AE    618 _EP4FIFOBCL	=	0xe6ae
                    E6AF    619 _EP6FIFOBCH	=	0xe6af
                    E6B0    620 _EP6FIFOBCL	=	0xe6b0
                    E6B1    621 _EP8FIFOBCH	=	0xe6b1
                    E6B2    622 _EP8FIFOBCL	=	0xe6b2
                    E6B3    623 _SUDPTRH	=	0xe6b3
                    E6B4    624 _SUDPTRL	=	0xe6b4
                    E6B5    625 _SUDPTRCTL	=	0xe6b5
                    E6B8    626 _SETUPDAT	=	0xe6b8
                    E6C0    627 _GPIFWFSELECT	=	0xe6c0
                    E6C1    628 _GPIFIDLECS	=	0xe6c1
                    E6C2    629 _GPIFIDLECTL	=	0xe6c2
                    E6C3    630 _GPIFCTLCFG	=	0xe6c3
                    E6C4    631 _GPIFADRH	=	0xe6c4
                    E6C5    632 _GPIFADRL	=	0xe6c5
                    E6CE    633 _GPIFTCB3	=	0xe6ce
                    E6CF    634 _GPIFTCB2	=	0xe6cf
                    E6D0    635 _GPIFTCB1	=	0xe6d0
                    E6D1    636 _GPIFTCB0	=	0xe6d1
                    E6D2    637 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    638 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    639 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    640 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    641 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    642 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    643 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    644 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    645 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    646 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    647 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    648 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    649 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    650 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    651 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    652 _GPIFREADYCFG	=	0xe6f3
                    E6F4    653 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    654 _GPIFABORT	=	0xe6f5
                    E6C6    655 _FLOWSTATE	=	0xe6c6
                    E6C7    656 _FLOWLOGIC	=	0xe6c7
                    E6C8    657 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    658 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    659 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    660 _FLOWSTB	=	0xe6cb
                    E6CC    661 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    662 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    663 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    664 _UDMACRCH	=	0xe67d
                    E67E    665 _UDMACRCL	=	0xe67e
                    E67F    666 _UDMACRCQUAL	=	0xe67f
                    E6F8    667 _DBUG	=	0xe6f8
                    E6F9    668 _TESTCFG	=	0xe6f9
                    E6FA    669 _USBTEST	=	0xe6fa
                    E6FB    670 _CT1	=	0xe6fb
                    E6FC    671 _CT2	=	0xe6fc
                    E6FD    672 _CT3	=	0xe6fd
                    E6FE    673 _CT4	=	0xe6fe
                    E740    674 _EP0BUF	=	0xe740
                    E780    675 _EP1OUTBUF	=	0xe780
                    E7C0    676 _EP1INBUF	=	0xe7c0
                    F000    677 _EP2FIFOBUF	=	0xf000
                    F400    678 _EP4FIFOBUF	=	0xf400
                    F800    679 _EP6FIFOBUF	=	0xf800
                    FC00    680 _EP8FIFOBUF	=	0xfc00
                            681 ;--------------------------------------------------------
                            682 ; external initialized ram data
                            683 ;--------------------------------------------------------
                            684 	.area HOME    (CODE)
                            685 	.area GSINIT0 (CODE)
                            686 	.area GSINIT1 (CODE)
                            687 	.area GSINIT2 (CODE)
                            688 	.area GSINIT3 (CODE)
                            689 	.area GSINIT4 (CODE)
                            690 	.area GSINIT5 (CODE)
                            691 	.area GSINIT  (CODE)
                            692 	.area GSFINAL (CODE)
                            693 	.area CSEG    (CODE)
                            694 ;--------------------------------------------------------
                            695 ; global & static initialisations
                            696 ;--------------------------------------------------------
                            697 	.area HOME    (CODE)
                            698 	.area GSINIT  (CODE)
                            699 	.area GSFINAL (CODE)
                            700 	.area GSINIT  (CODE)
                            701 ;--------------------------------------------------------
                            702 ; Home
                            703 ;--------------------------------------------------------
                            704 	.area HOME    (CODE)
                            705 	.area CSEG    (CODE)
                            706 ;--------------------------------------------------------
                            707 ; code
                            708 ;--------------------------------------------------------
                            709 	.area CSEG    (CODE)
                            710 ;------------------------------------------------------------
                            711 ;Allocation info for local variables in function 'fpga_load_begin'
                            712 ;------------------------------------------------------------
                            713 ;------------------------------------------------------------
                            714 ;	../common/fpga_load.c:37: fpga_load_begin (void)
                            715 ;	-----------------------------------------
                            716 ;	 function fpga_load_begin
                            717 ;	-----------------------------------------
   0672                     718 _fpga_load_begin:
                    0002    719 	ar2 = 0x02
                    0003    720 	ar3 = 0x03
                    0004    721 	ar4 = 0x04
                    0005    722 	ar5 = 0x05
                    0006    723 	ar6 = 0x06
                    0007    724 	ar7 = 0x07
                    0000    725 	ar0 = 0x00
                    0001    726 	ar1 = 0x01
                            727 ;	../common/fpga_load.c:39: USRP_ALTERA_CONFIG &= ~bmALTERA_BITS;		// clear all bits (NCONFIG low)
                            728 ;	genAnd
   0672 53 A0 C1            729 	anl	_IOC,#0xC1
                            730 ;	../common/fpga_load.c:40: udelay (40);					// wait 40 us
                            731 ;	genCall
   0675 75 82 28            732 	mov	dpl,#0x28
   0678 12 12 33            733 	lcall	_udelay
                            734 ;	../common/fpga_load.c:41: USRP_ALTERA_CONFIG |= bmALTERA_NCONFIG;	// set NCONFIG high
                            735 ;	genOr
   067B 43 A0 04            736 	orl	_IOC,#0x04
                            737 ;	../common/fpga_load.c:46: while ((USRP_ALTERA_CONFIG & bmALTERA_NSTATUS) == 0) // wait for NSTATUS to go high
   067E                     738 00101$:
                            739 ;	genAnd
   067E E5 A0               740 	mov	a,_IOC
                            741 ;	genIfxJump
                            742 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0680 30 E5 FB            743 	jnb	acc.5,00101$
                            744 ;	Peephole 300	removed redundant label 00110$
                            745 ;	../common/fpga_load.c:52: return 1;
                            746 ;	genRet
   0683 75 82 01            747 	mov	dpl,#0x01
                            748 ;	Peephole 300	removed redundant label 00106$
   0686 22                  749 	ret
                            750 ;------------------------------------------------------------
                            751 ;Allocation info for local variables in function 'clock_out_config_byte'
                            752 ;------------------------------------------------------------
                            753 ;bits                      Allocated to registers 
                            754 ;------------------------------------------------------------
                            755 ;	../common/fpga_load.c:92: clock_out_config_byte (unsigned char bits) _naked
                            756 ;	-----------------------------------------
                            757 ;	 function clock_out_config_byte
                            758 ;	-----------------------------------------
   0687                     759 _clock_out_config_byte:
                            760 ;	naked function: no prologue.
                            761 ;	../common/fpga_load.c:139: _endasm;
                            762 ;	genInline
   0687 E5 82               763 	        mov a, dpl
   0689 13                  764 	        rrc a
   068A 92 A1               765 	        mov _bitALTERA_DATA0,c
   068C D2 A3               766 	        setb _bitALTERA_DCLK
   068E C2 A3               767 	        clr _bitALTERA_DCLK
   0690 13                  768 	        rrc a
   0691 92 A1               769 	        mov _bitALTERA_DATA0,c
   0693 D2 A3               770 	        setb _bitALTERA_DCLK
   0695 C2 A3               771 	        clr _bitALTERA_DCLK
   0697 13                  772 	        rrc a
   0698 92 A1               773 	        mov _bitALTERA_DATA0,c
   069A D2 A3               774 	        setb _bitALTERA_DCLK
   069C C2 A3               775 	        clr _bitALTERA_DCLK
   069E 13                  776 	        rrc a
   069F 92 A1               777 	        mov _bitALTERA_DATA0,c
   06A1 D2 A3               778 	        setb _bitALTERA_DCLK
   06A3 C2 A3               779 	        clr _bitALTERA_DCLK
   06A5 13                  780 	        rrc a
   06A6 92 A1               781 	        mov _bitALTERA_DATA0,c
   06A8 D2 A3               782 	        setb _bitALTERA_DCLK
   06AA C2 A3               783 	        clr _bitALTERA_DCLK
   06AC 13                  784 	        rrc a
   06AD 92 A1               785 	        mov _bitALTERA_DATA0,c
   06AF D2 A3               786 	        setb _bitALTERA_DCLK
   06B1 C2 A3               787 	        clr _bitALTERA_DCLK
   06B3 13                  788 	        rrc a
   06B4 92 A1               789 	        mov _bitALTERA_DATA0,c
   06B6 D2 A3               790 	        setb _bitALTERA_DCLK
   06B8 C2 A3               791 	        clr _bitALTERA_DCLK
   06BA 13                  792 	        rrc a
   06BB 92 A1               793 	        mov _bitALTERA_DATA0,c
   06BD D2 A3               794 	        setb _bitALTERA_DCLK
   06BF C2 A3               795 	        clr _bitALTERA_DCLK
   06C1 22                  796 	        ret
                            797 ;	Peephole 300	removed redundant label 00101$
                            798 ;	naked function: no epilogue.
                            799 ;------------------------------------------------------------
                            800 ;Allocation info for local variables in function 'clock_out_bytes'
                            801 ;------------------------------------------------------------
                            802 ;p                         Allocated with name '_clock_out_bytes_PARM_2'
                            803 ;bytecount                 Allocated to registers r2 
                            804 ;------------------------------------------------------------
                            805 ;	../common/fpga_load.c:145: clock_out_bytes (unsigned char bytecount,
                            806 ;	-----------------------------------------
                            807 ;	 function clock_out_bytes
                            808 ;	-----------------------------------------
   06C2                     809 _clock_out_bytes:
                            810 ;	genReceive
   06C2 AA 82               811 	mov	r2,dpl
                            812 ;	../common/fpga_load.c:148: while (bytecount-- > 0)
                            813 ;	genAssign
   06C4 AB 10               814 	mov	r3,_clock_out_bytes_PARM_2
   06C6 AC 11               815 	mov	r4,(_clock_out_bytes_PARM_2 + 1)
                            816 ;	genAssign
   06C8                     817 00101$:
                            818 ;	genAssign
   06C8 8A 05               819 	mov	ar5,r2
                            820 ;	genMinus
                            821 ;	genMinusDec
   06CA 1A                  822 	dec	r2
                            823 ;	genIfx
   06CB ED                  824 	mov	a,r5
                            825 ;	genIfxJump
                            826 ;	Peephole 108.c	removed ljmp by inverse jump logic
   06CC 60 12               827 	jz	00104$
                            828 ;	Peephole 300	removed redundant label 00109$
                            829 ;	../common/fpga_load.c:149: clock_out_config_byte (*p++);
                            830 ;	genPointerGet
                            831 ;	genFarPointerGet
   06CE 8B 82               832 	mov	dpl,r3
   06D0 8C 83               833 	mov	dph,r4
   06D2 E0                  834 	movx	a,@dptr
   06D3 FD                  835 	mov	r5,a
   06D4 A3                  836 	inc	dptr
   06D5 AB 82               837 	mov	r3,dpl
   06D7 AC 83               838 	mov	r4,dph
                            839 ;	genCall
   06D9 8D 82               840 	mov	dpl,r5
   06DB 12 06 87            841 	lcall	_clock_out_config_byte
                            842 ;	Peephole 112.b	changed ljmp to sjmp
   06DE 80 E8               843 	sjmp	00101$
   06E0                     844 00104$:
   06E0 22                  845 	ret
                            846 ;------------------------------------------------------------
                            847 ;Allocation info for local variables in function 'fpga_load_xfer'
                            848 ;------------------------------------------------------------
                            849 ;bytecount                 Allocated with name '_fpga_load_xfer_PARM_2'
                            850 ;p                         Allocated to registers 
                            851 ;------------------------------------------------------------
                            852 ;	../common/fpga_load.c:166: fpga_load_xfer (xdata unsigned char *p, unsigned char bytecount)
                            853 ;	-----------------------------------------
                            854 ;	 function fpga_load_xfer
                            855 ;	-----------------------------------------
   06E1                     856 _fpga_load_xfer:
                            857 ;	genReceive
   06E1 85 82 10            858 	mov	_clock_out_bytes_PARM_2,dpl
   06E4 85 83 11            859 	mov	(_clock_out_bytes_PARM_2 + 1),dph
                            860 ;	../common/fpga_load.c:168: clock_out_bytes (bytecount, p);
                            861 ;	genCall
   06E7 85 12 82            862 	mov	dpl,_fpga_load_xfer_PARM_2
   06EA 12 06 C2            863 	lcall	_clock_out_bytes
                            864 ;	../common/fpga_load.c:169: return 1;
                            865 ;	genRet
   06ED 75 82 01            866 	mov	dpl,#0x01
                            867 ;	Peephole 300	removed redundant label 00101$
   06F0 22                  868 	ret
                            869 ;------------------------------------------------------------
                            870 ;Allocation info for local variables in function 'fpga_load_end'
                            871 ;------------------------------------------------------------
                            872 ;status                    Allocated to registers r2 
                            873 ;------------------------------------------------------------
                            874 ;	../common/fpga_load.c:176: fpga_load_end (void)
                            875 ;	-----------------------------------------
                            876 ;	 function fpga_load_end
                            877 ;	-----------------------------------------
   06F1                     878 _fpga_load_end:
                            879 ;	../common/fpga_load.c:178: unsigned char status = USRP_ALTERA_CONFIG;
                            880 ;	genAssign
                            881 ;	../common/fpga_load.c:183: if ((status & bmALTERA_NSTATUS) == 0)		// failed to program
                            882 ;	genAnd
                            883 ;	peephole 177.g	optimized mov sequence
   06F1 E5 A0               884 	mov	a,_IOC
   06F3 FA                  885 	mov	r2,a
                            886 ;	genIfxJump
                            887 ;	Peephole 108.e	removed ljmp by inverse jump logic
   06F4 20 E5 04            888 	jb	acc.5,00104$
                            889 ;	Peephole 300	removed redundant label 00111$
                            890 ;	../common/fpga_load.c:184: return 0;
                            891 ;	genRet
   06F7 75 82 00            892 	mov	dpl,#0x00
                            893 ;	Peephole 112.b	changed ljmp to sjmp
                            894 ;	Peephole 251.b	replaced sjmp to ret with ret
   06FA 22                  895 	ret
   06FB                     896 00104$:
                            897 ;	../common/fpga_load.c:186: if ((status & bmALTERA_CONF_DONE) == bmALTERA_CONF_DONE)
                            898 ;	genAnd
   06FB 53 02 10            899 	anl	ar2,#0x10
                            900 ;	genCmpEq
                            901 ;	gencjneshort
                            902 ;	Peephole 112.b	changed ljmp to sjmp
                            903 ;	Peephole 198.b	optimized misc jump sequence
   06FE BA 10 04            904 	cjne	r2,#0x10,00106$
                            905 ;	Peephole 200.b	removed redundant sjmp
                            906 ;	Peephole 300	removed redundant label 00112$
                            907 ;	Peephole 300	removed redundant label 00113$
                            908 ;	../common/fpga_load.c:187: return 1;					// everything's cool
                            909 ;	genRet
   0701 75 82 01            910 	mov	dpl,#0x01
                            911 ;	Peephole 112.b	changed ljmp to sjmp
                            912 ;	../common/fpga_load.c:192: return 0;
                            913 ;	genRet
                            914 ;	Peephole 237.a	removed sjmp to ret
   0704 22                  915 	ret
   0705                     916 00106$:
   0705 75 82 00            917 	mov	dpl,#0x00
                            918 ;	Peephole 300	removed redundant label 00107$
   0708 22                  919 	ret
                            920 	.area CSEG    (CODE)
                            921 	.area CONST   (CODE)

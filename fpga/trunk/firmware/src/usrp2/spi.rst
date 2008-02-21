                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Nov 10 2006)
                              4 ; This file generated Wed Jan 23 16:41:20 2008
                              5 ;--------------------------------------------------------
                              6 	.module spi
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
                            323 	.globl _read_bytes_msb_PARM_2
                            324 	.globl _write_bytes_msb_PARM_2
                            325 	.globl _spi_write_PARM_6
                            326 	.globl _spi_write_PARM_5
                            327 	.globl _spi_write_PARM_4
                            328 	.globl _spi_write_PARM_3
                            329 	.globl _spi_write_PARM_2
                            330 	.globl _spi_read_PARM_6
                            331 	.globl _spi_read_PARM_5
                            332 	.globl _spi_read_PARM_4
                            333 	.globl _spi_read_PARM_3
                            334 	.globl _spi_read_PARM_2
                            335 	.globl _init_spi
                            336 	.globl _spi_read
                            337 	.globl _spi_write
                            338 ;--------------------------------------------------------
                            339 ; special function registers
                            340 ;--------------------------------------------------------
                            341 	.area RSEG    (DATA)
                    0080    342 _IOA	=	0x0080
                    0081    343 _SP	=	0x0081
                    0082    344 _DPL	=	0x0082
                    0083    345 _DPH	=	0x0083
                    0084    346 _DPL1	=	0x0084
                    0085    347 _DPH1	=	0x0085
                    0086    348 _DPS	=	0x0086
                    0087    349 _PCON	=	0x0087
                    0088    350 _TCON	=	0x0088
                    0089    351 _TMOD	=	0x0089
                    008A    352 _TL0	=	0x008a
                    008B    353 _TL1	=	0x008b
                    008C    354 _TH0	=	0x008c
                    008D    355 _TH1	=	0x008d
                    008E    356 _CKCON	=	0x008e
                    0090    357 _IOB	=	0x0090
                    0091    358 _EXIF	=	0x0091
                    0092    359 _MPAGE	=	0x0092
                    0098    360 _SCON0	=	0x0098
                    0099    361 _SBUF0	=	0x0099
                    009A    362 _APTR1H	=	0x009a
                    009B    363 _APTR1L	=	0x009b
                    009C    364 _AUTODAT1	=	0x009c
                    009D    365 _AUTOPTRH2	=	0x009d
                    009E    366 _AUTOPTRL2	=	0x009e
                    009F    367 _AUTODAT2	=	0x009f
                    00A0    368 _IOC	=	0x00a0
                    00A1    369 _INT2CLR	=	0x00a1
                    00A2    370 _INT4CLR	=	0x00a2
                    00A8    371 _IE	=	0x00a8
                    00AA    372 _EP2468STAT	=	0x00aa
                    00AB    373 _EP24FIFOFLGS	=	0x00ab
                    00AC    374 _EP68FIFOFLGS	=	0x00ac
                    00AF    375 _AUTOPTRSETUP	=	0x00af
                    00B0    376 _IOD	=	0x00b0
                    00B1    377 _IOE	=	0x00b1
                    00B2    378 _OEA	=	0x00b2
                    00B3    379 _OEB	=	0x00b3
                    00B4    380 _OEC	=	0x00b4
                    00B5    381 _OED	=	0x00b5
                    00B6    382 _OEE	=	0x00b6
                    00B8    383 _IP	=	0x00b8
                    00BA    384 _EP01STAT	=	0x00ba
                    00BB    385 _GPIFTRIG	=	0x00bb
                    00BD    386 _GPIFSGLDATH	=	0x00bd
                    00BE    387 _GPIFSGLDATLX	=	0x00be
                    00BF    388 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    389 _SCON1	=	0x00c0
                    00C1    390 _SBUF1	=	0x00c1
                    00C8    391 _T2CON	=	0x00c8
                    00CA    392 _RCAP2L	=	0x00ca
                    00CB    393 _RCAP2H	=	0x00cb
                    00CC    394 _TL2	=	0x00cc
                    00CD    395 _TH2	=	0x00cd
                    00D0    396 _PSW	=	0x00d0
                    00D8    397 _EICON	=	0x00d8
                    00E0    398 _ACC	=	0x00e0
                    00E8    399 _EIE	=	0x00e8
                    00F0    400 _B	=	0x00f0
                    00F8    401 _EIP	=	0x00f8
                            402 ;--------------------------------------------------------
                            403 ; special function bits
                            404 ;--------------------------------------------------------
                            405 	.area RSEG    (DATA)
                    0086    406 _SEL	=	0x0086
                    0088    407 _IT0	=	0x0088
                    0089    408 _IE0	=	0x0089
                    008A    409 _IT1	=	0x008a
                    008B    410 _IE1	=	0x008b
                    008C    411 _TR0	=	0x008c
                    008D    412 _TF0	=	0x008d
                    008E    413 _TR1	=	0x008e
                    008F    414 _TF1	=	0x008f
                    0098    415 _RI	=	0x0098
                    0099    416 _TI	=	0x0099
                    009A    417 _RB8	=	0x009a
                    009B    418 _TB8	=	0x009b
                    009C    419 _REN	=	0x009c
                    009D    420 _SM2	=	0x009d
                    009E    421 _SM1	=	0x009e
                    009F    422 _SM0	=	0x009f
                    00A8    423 _EX0	=	0x00a8
                    00A9    424 _ET0	=	0x00a9
                    00AA    425 _EX1	=	0x00aa
                    00AB    426 _ET1	=	0x00ab
                    00AC    427 _ES0	=	0x00ac
                    00AD    428 _ET2	=	0x00ad
                    00AE    429 _ES1	=	0x00ae
                    00AF    430 _EA	=	0x00af
                    00B8    431 _PX0	=	0x00b8
                    00B9    432 _PT0	=	0x00b9
                    00BA    433 _PX1	=	0x00ba
                    00BB    434 _PT1	=	0x00bb
                    00BC    435 _PS0	=	0x00bc
                    00BD    436 _PT2	=	0x00bd
                    00BE    437 _PS1	=	0x00be
                    00C0    438 _RI1	=	0x00c0
                    00C1    439 _TI1	=	0x00c1
                    00C2    440 _RB81	=	0x00c2
                    00C3    441 _TB81	=	0x00c3
                    00C4    442 _REN1	=	0x00c4
                    00C5    443 _SM21	=	0x00c5
                    00C6    444 _SM11	=	0x00c6
                    00C7    445 _SM01	=	0x00c7
                    00C8    446 _CP_RL2	=	0x00c8
                    00C9    447 _C_T2	=	0x00c9
                    00CA    448 _TR2	=	0x00ca
                    00CB    449 _EXEN2	=	0x00cb
                    00CC    450 _TCLK	=	0x00cc
                    00CD    451 _RCLK	=	0x00cd
                    00CE    452 _EXF2	=	0x00ce
                    00CF    453 _TF2	=	0x00cf
                    00D0    454 _P	=	0x00d0
                    00D1    455 _FL	=	0x00d1
                    00D2    456 _OV	=	0x00d2
                    00D3    457 _RS0	=	0x00d3
                    00D4    458 _RS1	=	0x00d4
                    00D5    459 _F0	=	0x00d5
                    00D6    460 _AC	=	0x00d6
                    00D7    461 _CY	=	0x00d7
                    00DB    462 _INT6	=	0x00db
                    00DC    463 _RESI	=	0x00dc
                    00DD    464 _ERESI	=	0x00dd
                    00DF    465 _SMOD1	=	0x00df
                    00E8    466 _EIUSB	=	0x00e8
                    00E9    467 _EI2C	=	0x00e9
                    00EA    468 _EIEX4	=	0x00ea
                    00EB    469 _EIEX5	=	0x00eb
                    00EC    470 _EIEX6	=	0x00ec
                    00F8    471 _PUSB	=	0x00f8
                    00F9    472 _PI2C	=	0x00f9
                    00FA    473 _EIPX4	=	0x00fa
                    00FB    474 _EIPX5	=	0x00fb
                    00FC    475 _EIPX6	=	0x00fc
                    0080    476 _bitS_CLK	=	0x0080
                    0081    477 _bitS_OUT	=	0x0081
                    0082    478 _bitS_IN	=	0x0082
                    00A1    479 _bitALTERA_DATA0	=	0x00a1
                    00A3    480 _bitALTERA_DCLK	=	0x00a3
                            481 ;--------------------------------------------------------
                            482 ; overlayable register banks
                            483 ;--------------------------------------------------------
                            484 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     485 	.ds 8
                            486 ;--------------------------------------------------------
                            487 ; internal ram data
                            488 ;--------------------------------------------------------
                            489 	.area DSEG    (DATA)
   0021                     490 _spi_read_PARM_2:
   0021                     491 	.ds 1
   0022                     492 _spi_read_PARM_3:
   0022                     493 	.ds 1
   0023                     494 _spi_read_PARM_4:
   0023                     495 	.ds 1
   0024                     496 _spi_read_PARM_5:
   0024                     497 	.ds 2
   0026                     498 _spi_read_PARM_6:
   0026                     499 	.ds 1
   0027                     500 _spi_write_PARM_2:
   0027                     501 	.ds 1
   0028                     502 _spi_write_PARM_3:
   0028                     503 	.ds 1
   0029                     504 _spi_write_PARM_4:
   0029                     505 	.ds 1
   002A                     506 _spi_write_PARM_5:
   002A                     507 	.ds 2
   002C                     508 _spi_write_PARM_6:
   002C                     509 	.ds 1
   002D                     510 _write_bytes_msb_PARM_2:
   002D                     511 	.ds 1
   002E                     512 _read_bytes_msb_PARM_2:
   002E                     513 	.ds 1
                            514 ;--------------------------------------------------------
                            515 ; overlayable items in internal ram 
                            516 ;--------------------------------------------------------
                            517 	.area	OSEG    (OVR,DATA)
                            518 	.area	OSEG    (OVR,DATA)
                            519 	.area	OSEG    (OVR,DATA)
                            520 ;--------------------------------------------------------
                            521 ; indirectly addressable internal ram data
                            522 ;--------------------------------------------------------
                            523 	.area ISEG    (DATA)
                            524 ;--------------------------------------------------------
                            525 ; bit data
                            526 ;--------------------------------------------------------
                            527 	.area BSEG    (BIT)
                            528 ;--------------------------------------------------------
                            529 ; paged external ram data
                            530 ;--------------------------------------------------------
                            531 	.area PSEG    (PAG,XDATA)
                            532 ;--------------------------------------------------------
                            533 ; external ram data
                            534 ;--------------------------------------------------------
                            535 	.area XSEG    (XDATA)
                    E400    536 _GPIF_WAVE_DATA	=	0xe400
                    E480    537 _RES_WAVEDATA_END	=	0xe480
                    E600    538 _CPUCS	=	0xe600
                    E601    539 _IFCONFIG	=	0xe601
                    E602    540 _PINFLAGSAB	=	0xe602
                    E603    541 _PINFLAGSCD	=	0xe603
                    E604    542 _FIFORESET	=	0xe604
                    E605    543 _BREAKPT	=	0xe605
                    E606    544 _BPADDRH	=	0xe606
                    E607    545 _BPADDRL	=	0xe607
                    E608    546 _UART230	=	0xe608
                    E609    547 _FIFOPINPOLAR	=	0xe609
                    E60A    548 _REVID	=	0xe60a
                    E60B    549 _REVCTL	=	0xe60b
                    E610    550 _EP1OUTCFG	=	0xe610
                    E611    551 _EP1INCFG	=	0xe611
                    E612    552 _EP2CFG	=	0xe612
                    E613    553 _EP4CFG	=	0xe613
                    E614    554 _EP6CFG	=	0xe614
                    E615    555 _EP8CFG	=	0xe615
                    E618    556 _EP2FIFOCFG	=	0xe618
                    E619    557 _EP4FIFOCFG	=	0xe619
                    E61A    558 _EP6FIFOCFG	=	0xe61a
                    E61B    559 _EP8FIFOCFG	=	0xe61b
                    E620    560 _EP2AUTOINLENH	=	0xe620
                    E621    561 _EP2AUTOINLENL	=	0xe621
                    E622    562 _EP4AUTOINLENH	=	0xe622
                    E623    563 _EP4AUTOINLENL	=	0xe623
                    E624    564 _EP6AUTOINLENH	=	0xe624
                    E625    565 _EP6AUTOINLENL	=	0xe625
                    E626    566 _EP8AUTOINLENH	=	0xe626
                    E627    567 _EP8AUTOINLENL	=	0xe627
                    E630    568 _EP2FIFOPFH	=	0xe630
                    E631    569 _EP2FIFOPFL	=	0xe631
                    E632    570 _EP4FIFOPFH	=	0xe632
                    E633    571 _EP4FIFOPFL	=	0xe633
                    E634    572 _EP6FIFOPFH	=	0xe634
                    E635    573 _EP6FIFOPFL	=	0xe635
                    E636    574 _EP8FIFOPFH	=	0xe636
                    E637    575 _EP8FIFOPFL	=	0xe637
                    E640    576 _EP2ISOINPKTS	=	0xe640
                    E641    577 _EP4ISOINPKTS	=	0xe641
                    E642    578 _EP6ISOINPKTS	=	0xe642
                    E643    579 _EP8ISOINPKTS	=	0xe643
                    E648    580 _INPKTEND	=	0xe648
                    E649    581 _OUTPKTEND	=	0xe649
                    E650    582 _EP2FIFOIE	=	0xe650
                    E651    583 _EP2FIFOIRQ	=	0xe651
                    E652    584 _EP4FIFOIE	=	0xe652
                    E653    585 _EP4FIFOIRQ	=	0xe653
                    E654    586 _EP6FIFOIE	=	0xe654
                    E655    587 _EP6FIFOIRQ	=	0xe655
                    E656    588 _EP8FIFOIE	=	0xe656
                    E657    589 _EP8FIFOIRQ	=	0xe657
                    E658    590 _IBNIE	=	0xe658
                    E659    591 _IBNIRQ	=	0xe659
                    E65A    592 _NAKIE	=	0xe65a
                    E65B    593 _NAKIRQ	=	0xe65b
                    E65C    594 _USBIE	=	0xe65c
                    E65D    595 _USBIRQ	=	0xe65d
                    E65E    596 _EPIE	=	0xe65e
                    E65F    597 _EPIRQ	=	0xe65f
                    E660    598 _GPIFIE	=	0xe660
                    E661    599 _GPIFIRQ	=	0xe661
                    E662    600 _USBERRIE	=	0xe662
                    E663    601 _USBERRIRQ	=	0xe663
                    E664    602 _ERRCNTLIM	=	0xe664
                    E665    603 _CLRERRCNT	=	0xe665
                    E666    604 _INT2IVEC	=	0xe666
                    E667    605 _INT4IVEC	=	0xe667
                    E668    606 _INTSETUP	=	0xe668
                    E670    607 _PORTACFG	=	0xe670
                    E671    608 _PORTCCFG	=	0xe671
                    E672    609 _PORTECFG	=	0xe672
                    E678    610 _I2CS	=	0xe678
                    E679    611 _I2DAT	=	0xe679
                    E67A    612 _I2CTL	=	0xe67a
                    E67B    613 _XAUTODAT1	=	0xe67b
                    E67C    614 _XAUTODAT2	=	0xe67c
                    E680    615 _USBCS	=	0xe680
                    E681    616 _SUSPEND	=	0xe681
                    E682    617 _WAKEUPCS	=	0xe682
                    E683    618 _TOGCTL	=	0xe683
                    E684    619 _USBFRAMEH	=	0xe684
                    E685    620 _USBFRAMEL	=	0xe685
                    E686    621 _MICROFRAME	=	0xe686
                    E687    622 _FNADDR	=	0xe687
                    E68A    623 _EP0BCH	=	0xe68a
                    E68B    624 _EP0BCL	=	0xe68b
                    E68D    625 _EP1OUTBC	=	0xe68d
                    E68F    626 _EP1INBC	=	0xe68f
                    E690    627 _EP2BCH	=	0xe690
                    E691    628 _EP2BCL	=	0xe691
                    E694    629 _EP4BCH	=	0xe694
                    E695    630 _EP4BCL	=	0xe695
                    E698    631 _EP6BCH	=	0xe698
                    E699    632 _EP6BCL	=	0xe699
                    E69C    633 _EP8BCH	=	0xe69c
                    E69D    634 _EP8BCL	=	0xe69d
                    E6A0    635 _EP0CS	=	0xe6a0
                    E6A1    636 _EP1OUTCS	=	0xe6a1
                    E6A2    637 _EP1INCS	=	0xe6a2
                    E6A3    638 _EP2CS	=	0xe6a3
                    E6A4    639 _EP4CS	=	0xe6a4
                    E6A5    640 _EP6CS	=	0xe6a5
                    E6A6    641 _EP8CS	=	0xe6a6
                    E6A7    642 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    643 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    644 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    645 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    646 _EP2FIFOBCH	=	0xe6ab
                    E6AC    647 _EP2FIFOBCL	=	0xe6ac
                    E6AD    648 _EP4FIFOBCH	=	0xe6ad
                    E6AE    649 _EP4FIFOBCL	=	0xe6ae
                    E6AF    650 _EP6FIFOBCH	=	0xe6af
                    E6B0    651 _EP6FIFOBCL	=	0xe6b0
                    E6B1    652 _EP8FIFOBCH	=	0xe6b1
                    E6B2    653 _EP8FIFOBCL	=	0xe6b2
                    E6B3    654 _SUDPTRH	=	0xe6b3
                    E6B4    655 _SUDPTRL	=	0xe6b4
                    E6B5    656 _SUDPTRCTL	=	0xe6b5
                    E6B8    657 _SETUPDAT	=	0xe6b8
                    E6C0    658 _GPIFWFSELECT	=	0xe6c0
                    E6C1    659 _GPIFIDLECS	=	0xe6c1
                    E6C2    660 _GPIFIDLECTL	=	0xe6c2
                    E6C3    661 _GPIFCTLCFG	=	0xe6c3
                    E6C4    662 _GPIFADRH	=	0xe6c4
                    E6C5    663 _GPIFADRL	=	0xe6c5
                    E6CE    664 _GPIFTCB3	=	0xe6ce
                    E6CF    665 _GPIFTCB2	=	0xe6cf
                    E6D0    666 _GPIFTCB1	=	0xe6d0
                    E6D1    667 _GPIFTCB0	=	0xe6d1
                    E6D2    668 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    669 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    670 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    671 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    672 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    673 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    674 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    675 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    676 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    677 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    678 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    679 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    680 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    681 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    682 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    683 _GPIFREADYCFG	=	0xe6f3
                    E6F4    684 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    685 _GPIFABORT	=	0xe6f5
                    E6C6    686 _FLOWSTATE	=	0xe6c6
                    E6C7    687 _FLOWLOGIC	=	0xe6c7
                    E6C8    688 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    689 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    690 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    691 _FLOWSTB	=	0xe6cb
                    E6CC    692 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    693 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    694 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    695 _UDMACRCH	=	0xe67d
                    E67E    696 _UDMACRCL	=	0xe67e
                    E67F    697 _UDMACRCQUAL	=	0xe67f
                    E6F8    698 _DBUG	=	0xe6f8
                    E6F9    699 _TESTCFG	=	0xe6f9
                    E6FA    700 _USBTEST	=	0xe6fa
                    E6FB    701 _CT1	=	0xe6fb
                    E6FC    702 _CT2	=	0xe6fc
                    E6FD    703 _CT3	=	0xe6fd
                    E6FE    704 _CT4	=	0xe6fe
                    E740    705 _EP0BUF	=	0xe740
                    E780    706 _EP1OUTBUF	=	0xe780
                    E7C0    707 _EP1INBUF	=	0xe7c0
                    F000    708 _EP2FIFOBUF	=	0xf000
                    F400    709 _EP4FIFOBUF	=	0xf400
                    F800    710 _EP6FIFOBUF	=	0xf800
                    FC00    711 _EP8FIFOBUF	=	0xfc00
                            712 ;--------------------------------------------------------
                            713 ; external initialized ram data
                            714 ;--------------------------------------------------------
                            715 	.area HOME    (CODE)
                            716 	.area GSINIT0 (CODE)
                            717 	.area GSINIT1 (CODE)
                            718 	.area GSINIT2 (CODE)
                            719 	.area GSINIT3 (CODE)
                            720 	.area GSINIT4 (CODE)
                            721 	.area GSINIT5 (CODE)
                            722 	.area GSINIT  (CODE)
                            723 	.area GSFINAL (CODE)
                            724 	.area CSEG    (CODE)
                            725 ;--------------------------------------------------------
                            726 ; global & static initialisations
                            727 ;--------------------------------------------------------
                            728 	.area HOME    (CODE)
                            729 	.area GSINIT  (CODE)
                            730 	.area GSFINAL (CODE)
                            731 	.area GSINIT  (CODE)
                            732 ;--------------------------------------------------------
                            733 ; Home
                            734 ;--------------------------------------------------------
                            735 	.area HOME    (CODE)
                            736 	.area CSEG    (CODE)
                            737 ;--------------------------------------------------------
                            738 ; code
                            739 ;--------------------------------------------------------
                            740 	.area CSEG    (CODE)
                            741 ;------------------------------------------------------------
                            742 ;Allocation info for local variables in function 'setup_enables'
                            743 ;------------------------------------------------------------
                            744 ;enables                   Allocated to registers r2 
                            745 ;------------------------------------------------------------
                            746 ;	spi.c:27: setup_enables (unsigned char enables)
                            747 ;	-----------------------------------------
                            748 ;	 function setup_enables
                            749 ;	-----------------------------------------
   0810                     750 _setup_enables:
                    0002    751 	ar2 = 0x02
                    0003    752 	ar3 = 0x03
                    0004    753 	ar4 = 0x04
                    0005    754 	ar5 = 0x05
                    0006    755 	ar6 = 0x06
                    0007    756 	ar7 = 0x07
                    0000    757 	ar0 = 0x00
                    0001    758 	ar1 = 0x01
                            759 ;	genReceive
   0810 AA 82               760 	mov	r2,dpl
                            761 ;	spi.c:33: enables ^= SPI_ENABLE_FPGA;
                            762 ;	genXor
   0812 63 02 01            763 	xrl	ar2,#0x01
                            764 ;	spi.c:37: USRP_PA = USRP_PA | (0x7 << 3);	// disable FPGA, CODEC_A, CODEC_B
                            765 ;	genOr
   0815 43 80 38            766 	orl	_IOA,#0x38
                            767 ;	spi.c:38: USRP_PA ^= (enables & 0x7) << 3;	// enable specified devs
                            768 ;	genAnd
   0818 74 07               769 	mov	a,#0x07
   081A 5A                  770 	anl	a,r2
                            771 ;	genLeftShift
                            772 ;	genLeftShiftLiteral
                            773 ;	genlshOne
   081B FB                  774 	mov	r3,a
                            775 ;	Peephole 105	removed redundant mov
   081C C4                  776 	swap	a
   081D 03                  777 	rr	a
   081E 54 F8               778 	anl	a,#0xf8
                            779 ;	genXor
   0820 FB                  780 	mov	r3,a
                            781 ;	Peephole 105	removed redundant mov
   0821 62 80               782 	xrl	_IOA,a
                            783 ;	spi.c:41: USRP_PE = USRP_PE | (0xf << 4);	// disable TX_A, RX_A, TX_B, RX_B
                            784 ;	genOr
   0823 43 B1 F0            785 	orl	_IOE,#0xF0
                            786 ;	spi.c:42: USRP_PE ^= (enables & 0xf0);		// enable specified devs
                            787 ;	genAnd
   0826 74 F0               788 	mov	a,#0xF0
   0828 5A                  789 	anl	a,r2
                            790 ;	genXor
   0829 62 B1               791 	xrl	_IOE,a
                            792 ;	Peephole 300	removed redundant label 00101$
   082B 22                  793 	ret
                            794 ;------------------------------------------------------------
                            795 ;Allocation info for local variables in function 'init_spi'
                            796 ;------------------------------------------------------------
                            797 ;------------------------------------------------------------
                            798 ;	spi.c:48: init_spi (void)
                            799 ;	-----------------------------------------
                            800 ;	 function init_spi
                            801 ;	-----------------------------------------
   082C                     802 _init_spi:
                            803 ;	spi.c:50: disable_all ();		/* disable all devs	  */
                            804 ;	genCall
   082C 75 82 00            805 	mov	dpl,#0x00
   082F 12 08 10            806 	lcall	_setup_enables
                            807 ;	spi.c:51: bitS_OUT = 0;			/* idle state has CLK = 0 */
                            808 ;	genAssign
   0832 C2 81               809 	clr	_bitS_OUT
                            810 ;	Peephole 300	removed redundant label 00101$
   0834 22                  811 	ret
                            812 ;------------------------------------------------------------
                            813 ;Allocation info for local variables in function 'count_bits8'
                            814 ;------------------------------------------------------------
                            815 ;v                         Allocated to registers r2 
                            816 ;count                     Allocated to registers r3 
                            817 ;------------------------------------------------------------
                            818 ;	spi.c:82: count_bits8 (unsigned char v)
                            819 ;	-----------------------------------------
                            820 ;	 function count_bits8
                            821 ;	-----------------------------------------
   0835                     822 _count_bits8:
                            823 ;	genReceive
   0835 AA 82               824 	mov	r2,dpl
                            825 ;	spi.c:84: unsigned char count = 0;
                            826 ;	genAssign
   0837 7B 00               827 	mov	r3,#0x00
                            828 ;	spi.c:85: if (v & (1 << 0)) count++;
                            829 ;	genAnd
   0839 EA                  830 	mov	a,r2
                            831 ;	genIfxJump
                            832 ;	Peephole 108.d	removed ljmp by inverse jump logic
   083A 30 E0 02            833 	jnb	acc.0,00102$
                            834 ;	Peephole 300	removed redundant label 00127$
                            835 ;	genAssign
   083D 7B 01               836 	mov	r3,#0x01
   083F                     837 00102$:
                            838 ;	spi.c:86: if (v & (1 << 1)) count++;
                            839 ;	genAnd
   083F EA                  840 	mov	a,r2
                            841 ;	genIfxJump
                            842 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0840 30 E1 01            843 	jnb	acc.1,00104$
                            844 ;	Peephole 300	removed redundant label 00128$
                            845 ;	genPlus
                            846 ;     genPlusIncr
   0843 0B                  847 	inc	r3
   0844                     848 00104$:
                            849 ;	spi.c:87: if (v & (1 << 2)) count++;
                            850 ;	genAnd
   0844 EA                  851 	mov	a,r2
                            852 ;	genIfxJump
                            853 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0845 30 E2 01            854 	jnb	acc.2,00106$
                            855 ;	Peephole 300	removed redundant label 00129$
                            856 ;	genPlus
                            857 ;     genPlusIncr
   0848 0B                  858 	inc	r3
   0849                     859 00106$:
                            860 ;	spi.c:88: if (v & (1 << 3)) count++;
                            861 ;	genAnd
   0849 EA                  862 	mov	a,r2
                            863 ;	genIfxJump
                            864 ;	Peephole 108.d	removed ljmp by inverse jump logic
   084A 30 E3 01            865 	jnb	acc.3,00108$
                            866 ;	Peephole 300	removed redundant label 00130$
                            867 ;	genPlus
                            868 ;     genPlusIncr
   084D 0B                  869 	inc	r3
   084E                     870 00108$:
                            871 ;	spi.c:89: if (v & (1 << 4)) count++;
                            872 ;	genAnd
   084E EA                  873 	mov	a,r2
                            874 ;	genIfxJump
                            875 ;	Peephole 108.d	removed ljmp by inverse jump logic
   084F 30 E4 01            876 	jnb	acc.4,00110$
                            877 ;	Peephole 300	removed redundant label 00131$
                            878 ;	genPlus
                            879 ;     genPlusIncr
   0852 0B                  880 	inc	r3
   0853                     881 00110$:
                            882 ;	spi.c:90: if (v & (1 << 5)) count++;
                            883 ;	genAnd
   0853 EA                  884 	mov	a,r2
                            885 ;	genIfxJump
                            886 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0854 30 E5 01            887 	jnb	acc.5,00112$
                            888 ;	Peephole 300	removed redundant label 00132$
                            889 ;	genPlus
                            890 ;     genPlusIncr
   0857 0B                  891 	inc	r3
   0858                     892 00112$:
                            893 ;	spi.c:91: if (v & (1 << 6)) count++;
                            894 ;	genAnd
   0858 EA                  895 	mov	a,r2
                            896 ;	genIfxJump
                            897 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0859 30 E6 01            898 	jnb	acc.6,00114$
                            899 ;	Peephole 300	removed redundant label 00133$
                            900 ;	genPlus
                            901 ;     genPlusIncr
   085C 0B                  902 	inc	r3
   085D                     903 00114$:
                            904 ;	spi.c:92: if (v & (1 << 7)) count++;
                            905 ;	genAnd
   085D EA                  906 	mov	a,r2
                            907 ;	genIfxJump
                            908 ;	Peephole 108.d	removed ljmp by inverse jump logic
   085E 30 E7 01            909 	jnb	acc.7,00116$
                            910 ;	Peephole 300	removed redundant label 00134$
                            911 ;	genPlus
                            912 ;     genPlusIncr
   0861 0B                  913 	inc	r3
   0862                     914 00116$:
                            915 ;	spi.c:93: return count;
                            916 ;	genRet
   0862 8B 82               917 	mov	dpl,r3
                            918 ;	Peephole 300	removed redundant label 00117$
   0864 22                  919 	ret
                            920 ;------------------------------------------------------------
                            921 ;Allocation info for local variables in function 'spi_read'
                            922 ;------------------------------------------------------------
                            923 ;header_lo                 Allocated with name '_spi_read_PARM_2'
                            924 ;enables                   Allocated with name '_spi_read_PARM_3'
                            925 ;format                    Allocated with name '_spi_read_PARM_4'
                            926 ;buf                       Allocated with name '_spi_read_PARM_5'
                            927 ;len                       Allocated with name '_spi_read_PARM_6'
                            928 ;header_hi                 Allocated to registers r2 
                            929 ;------------------------------------------------------------
                            930 ;	spi.c:109: spi_read (unsigned char header_hi, unsigned char header_lo,
                            931 ;	-----------------------------------------
                            932 ;	 function spi_read
                            933 ;	-----------------------------------------
   0865                     934 _spi_read:
                            935 ;	genReceive
   0865 AA 82               936 	mov	r2,dpl
                            937 ;	spi.c:113: if (count_bits8 (enables) > 1)
                            938 ;	genCall
   0867 85 22 82            939 	mov	dpl,_spi_read_PARM_3
   086A C0 02               940 	push	ar2
   086C 12 08 35            941 	lcall	_count_bits8
   086F AB 82               942 	mov	r3,dpl
   0871 D0 02               943 	pop	ar2
                            944 ;	genCmpGt
                            945 ;	genCmp
                            946 ;	genIfxJump
                            947 ;	Peephole 108.a	removed ljmp by inverse jump logic
                            948 ;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
   0873 EB                  949 	mov	a,r3
   0874 24 FE               950 	add	a,#0xff - 0x01
   0876 50 04               951 	jnc	00102$
                            952 ;	Peephole 300	removed redundant label 00121$
                            953 ;	spi.c:114: return 0;		// error, too many enables set
                            954 ;	genRet
   0878 75 82 00            955 	mov	dpl,#0x00
                            956 ;	Peephole 112.b	changed ljmp to sjmp
                            957 ;	Peephole 251.b	replaced sjmp to ret with ret
   087B 22                  958 	ret
   087C                     959 00102$:
                            960 ;	spi.c:116: setup_enables (enables);
                            961 ;	genCall
   087C 85 22 82            962 	mov	dpl,_spi_read_PARM_3
   087F C0 02               963 	push	ar2
   0881 12 08 10            964 	lcall	_setup_enables
   0884 D0 02               965 	pop	ar2
                            966 ;	spi.c:118: if (format & SPI_FMT_LSB){		// order: LSB
                            967 ;	genAnd
   0886 E5 23               968 	mov	a,_spi_read_PARM_4
                            969 ;	genIfxJump
                            970 ;	Peephole 108.d	removed ljmp by inverse jump logic
   0888 30 E7 04            971 	jnb	acc.7,00111$
                            972 ;	Peephole 300	removed redundant label 00122$
                            973 ;	spi.c:120: return 0;		// error, not implemented
                            974 ;	genRet
   088B 75 82 00            975 	mov	dpl,#0x00
                            976 ;	Peephole 112.b	changed ljmp to sjmp
                            977 ;	Peephole 251.b	replaced sjmp to ret with ret
   088E 22                  978 	ret
   088F                     979 00111$:
                            980 ;	spi.c:142: switch (format & SPI_FMT_HDR_MASK){
                            981 ;	genAnd
   088F 74 60               982 	mov	a,#0x60
   0891 55 23               983 	anl	a,_spi_read_PARM_4
                            984 ;	genCmpEq
                            985 ;	gencjneshort
                            986 ;	Peephole 112.b	changed ljmp to sjmp
   0893 FB                  987 	mov	r3,a
                            988 ;	Peephole 115.b	jump optimization
   0894 60 23               989 	jz	00107$
                            990 ;	Peephole 300	removed redundant label 00123$
                            991 ;	genCmpEq
                            992 ;	gencjneshort
   0896 BB 20 02            993 	cjne	r3,#0x20,00124$
                            994 ;	Peephole 112.b	changed ljmp to sjmp
   0899 80 05               995 	sjmp	00104$
   089B                     996 00124$:
                            997 ;	genCmpEq
                            998 ;	gencjneshort
                            999 ;	Peephole 112.b	changed ljmp to sjmp
                           1000 ;	spi.c:145: case SPI_FMT_HDR_1:
                           1001 ;	Peephole 112.b	changed ljmp to sjmp
                           1002 ;	Peephole 198.b	optimized misc jump sequence
   089B BB 40 17           1003 	cjne	r3,#0x40,00106$
   089E 80 08              1004 	sjmp	00105$
                           1005 ;	Peephole 300	removed redundant label 00125$
   08A0                    1006 00104$:
                           1007 ;	spi.c:146: write_byte_msb (header_lo);
                           1008 ;	genCall
   08A0 85 21 82           1009 	mov	dpl,_spi_read_PARM_2
   08A3 12 09 2C           1010 	lcall	_write_byte_msb
                           1011 ;	spi.c:147: break;
                           1012 ;	spi.c:148: case SPI_FMT_HDR_2:
                           1013 ;	Peephole 112.b	changed ljmp to sjmp
   08A6 80 11              1014 	sjmp	00107$
   08A8                    1015 00105$:
                           1016 ;	spi.c:149: write_byte_msb (header_hi);
                           1017 ;	genCall
   08A8 8A 82              1018 	mov	dpl,r2
   08AA 12 09 2C           1019 	lcall	_write_byte_msb
                           1020 ;	spi.c:150: write_byte_msb (header_lo);
                           1021 ;	genCall
   08AD 85 21 82           1022 	mov	dpl,_spi_read_PARM_2
   08B0 12 09 2C           1023 	lcall	_write_byte_msb
                           1024 ;	spi.c:151: break;
                           1025 ;	spi.c:152: default:
                           1026 ;	Peephole 112.b	changed ljmp to sjmp
   08B3 80 04              1027 	sjmp	00107$
   08B5                    1028 00106$:
                           1029 ;	spi.c:153: return 0;		// error
                           1030 ;	genRet
   08B5 75 82 00           1031 	mov	dpl,#0x00
                           1032 ;	spi.c:154: }
                           1033 ;	Peephole 112.b	changed ljmp to sjmp
                           1034 ;	Peephole 251.b	replaced sjmp to ret with ret
   08B8 22                 1035 	ret
   08B9                    1036 00107$:
                           1037 ;	spi.c:155: if (len != 0)
                           1038 ;	genCmpEq
                           1039 ;	gencjneshort
   08B9 E5 26              1040 	mov	a,_spi_read_PARM_6
                           1041 ;	Peephole 108.c	removed ljmp by inverse jump logic
   08BB 60 0C              1042 	jz	00112$
                           1043 ;	Peephole 300	removed redundant label 00126$
                           1044 ;	spi.c:156: read_bytes_msb (buf, len);
                           1045 ;	genAssign
   08BD 85 26 2E           1046 	mov	_read_bytes_msb_PARM_2,_spi_read_PARM_6
                           1047 ;	genCall
   08C0 85 24 82           1048 	mov	dpl,_spi_read_PARM_5
   08C3 85 25 83           1049 	mov	dph,(_spi_read_PARM_5 + 1)
   08C6 12 09 E6           1050 	lcall	_read_bytes_msb
   08C9                    1051 00112$:
                           1052 ;	spi.c:159: disable_all ();
                           1053 ;	genCall
   08C9 75 82 00           1054 	mov	dpl,#0x00
   08CC 12 08 10           1055 	lcall	_setup_enables
                           1056 ;	spi.c:160: return 1;		// success
                           1057 ;	genRet
   08CF 75 82 01           1058 	mov	dpl,#0x01
                           1059 ;	Peephole 300	removed redundant label 00113$
   08D2 22                 1060 	ret
                           1061 ;------------------------------------------------------------
                           1062 ;Allocation info for local variables in function 'spi_write'
                           1063 ;------------------------------------------------------------
                           1064 ;header_lo                 Allocated with name '_spi_write_PARM_2'
                           1065 ;enables                   Allocated with name '_spi_write_PARM_3'
                           1066 ;format                    Allocated with name '_spi_write_PARM_4'
                           1067 ;buf                       Allocated with name '_spi_write_PARM_5'
                           1068 ;len                       Allocated with name '_spi_write_PARM_6'
                           1069 ;header_hi                 Allocated to registers r2 
                           1070 ;------------------------------------------------------------
                           1071 ;	spi.c:166: spi_write (unsigned char header_hi, unsigned char header_lo,
                           1072 ;	-----------------------------------------
                           1073 ;	 function spi_write
                           1074 ;	-----------------------------------------
   08D3                    1075 _spi_write:
                           1076 ;	genReceive
   08D3 AA 82              1077 	mov	r2,dpl
                           1078 ;	spi.c:170: setup_enables (enables);
                           1079 ;	genCall
   08D5 85 28 82           1080 	mov	dpl,_spi_write_PARM_3
   08D8 C0 02              1081 	push	ar2
   08DA 12 08 10           1082 	lcall	_setup_enables
   08DD D0 02              1083 	pop	ar2
                           1084 ;	spi.c:172: if (format & SPI_FMT_LSB){		// order: LSB
                           1085 ;	genAnd
   08DF E5 29              1086 	mov	a,_spi_write_PARM_4
                           1087 ;	genIfxJump
                           1088 ;	Peephole 108.d	removed ljmp by inverse jump logic
   08E1 30 E7 04           1089 	jnb	acc.7,00109$
                           1090 ;	Peephole 300	removed redundant label 00118$
                           1091 ;	spi.c:174: return 0;		// error, not implemented
                           1092 ;	genRet
   08E4 75 82 00           1093 	mov	dpl,#0x00
                           1094 ;	Peephole 112.b	changed ljmp to sjmp
                           1095 ;	Peephole 251.b	replaced sjmp to ret with ret
   08E7 22                 1096 	ret
   08E8                    1097 00109$:
                           1098 ;	spi.c:196: switch (format & SPI_FMT_HDR_MASK){
                           1099 ;	genAnd
   08E8 74 60              1100 	mov	a,#0x60
   08EA 55 29              1101 	anl	a,_spi_write_PARM_4
                           1102 ;	genCmpEq
                           1103 ;	gencjneshort
                           1104 ;	Peephole 112.b	changed ljmp to sjmp
   08EC FB                 1105 	mov	r3,a
                           1106 ;	Peephole 115.b	jump optimization
   08ED 60 23              1107 	jz	00105$
                           1108 ;	Peephole 300	removed redundant label 00119$
                           1109 ;	genCmpEq
                           1110 ;	gencjneshort
   08EF BB 20 02           1111 	cjne	r3,#0x20,00120$
                           1112 ;	Peephole 112.b	changed ljmp to sjmp
   08F2 80 05              1113 	sjmp	00102$
   08F4                    1114 00120$:
                           1115 ;	genCmpEq
                           1116 ;	gencjneshort
                           1117 ;	Peephole 112.b	changed ljmp to sjmp
                           1118 ;	spi.c:199: case SPI_FMT_HDR_1:
                           1119 ;	Peephole 112.b	changed ljmp to sjmp
                           1120 ;	Peephole 198.b	optimized misc jump sequence
   08F4 BB 40 17           1121 	cjne	r3,#0x40,00104$
   08F7 80 08              1122 	sjmp	00103$
                           1123 ;	Peephole 300	removed redundant label 00121$
   08F9                    1124 00102$:
                           1125 ;	spi.c:200: write_byte_msb (header_lo);
                           1126 ;	genCall
   08F9 85 27 82           1127 	mov	dpl,_spi_write_PARM_2
   08FC 12 09 2C           1128 	lcall	_write_byte_msb
                           1129 ;	spi.c:201: break;
                           1130 ;	spi.c:202: case SPI_FMT_HDR_2:
                           1131 ;	Peephole 112.b	changed ljmp to sjmp
   08FF 80 11              1132 	sjmp	00105$
   0901                    1133 00103$:
                           1134 ;	spi.c:203: write_byte_msb (header_hi);
                           1135 ;	genCall
   0901 8A 82              1136 	mov	dpl,r2
   0903 12 09 2C           1137 	lcall	_write_byte_msb
                           1138 ;	spi.c:204: write_byte_msb (header_lo);
                           1139 ;	genCall
   0906 85 27 82           1140 	mov	dpl,_spi_write_PARM_2
   0909 12 09 2C           1141 	lcall	_write_byte_msb
                           1142 ;	spi.c:205: break;
                           1143 ;	spi.c:206: default:
                           1144 ;	Peephole 112.b	changed ljmp to sjmp
   090C 80 04              1145 	sjmp	00105$
   090E                    1146 00104$:
                           1147 ;	spi.c:207: return 0;		// error
                           1148 ;	genRet
   090E 75 82 00           1149 	mov	dpl,#0x00
                           1150 ;	spi.c:208: }
                           1151 ;	Peephole 112.b	changed ljmp to sjmp
                           1152 ;	Peephole 251.b	replaced sjmp to ret with ret
   0911 22                 1153 	ret
   0912                    1154 00105$:
                           1155 ;	spi.c:209: if (len != 0)
                           1156 ;	genCmpEq
                           1157 ;	gencjneshort
   0912 E5 2C              1158 	mov	a,_spi_write_PARM_6
                           1159 ;	Peephole 108.c	removed ljmp by inverse jump logic
   0914 60 0C              1160 	jz	00110$
                           1161 ;	Peephole 300	removed redundant label 00122$
                           1162 ;	spi.c:210: write_bytes_msb (buf, len);
                           1163 ;	genAssign
   0916 85 2C 2D           1164 	mov	_write_bytes_msb_PARM_2,_spi_write_PARM_6
                           1165 ;	genCall
   0919 85 2A 82           1166 	mov	dpl,_spi_write_PARM_5
   091C 85 2B 83           1167 	mov	dph,(_spi_write_PARM_5 + 1)
   091F 12 09 7F           1168 	lcall	_write_bytes_msb
   0922                    1169 00110$:
                           1170 ;	spi.c:213: disable_all ();
                           1171 ;	genCall
   0922 75 82 00           1172 	mov	dpl,#0x00
   0925 12 08 10           1173 	lcall	_setup_enables
                           1174 ;	spi.c:214: return 1;		// success
                           1175 ;	genRet
   0928 75 82 01           1176 	mov	dpl,#0x01
                           1177 ;	Peephole 300	removed redundant label 00111$
   092B 22                 1178 	ret
                           1179 ;------------------------------------------------------------
                           1180 ;Allocation info for local variables in function 'write_byte_msb'
                           1181 ;------------------------------------------------------------
                           1182 ;v                         Allocated to registers r2 
                           1183 ;------------------------------------------------------------
                           1184 ;	spi.c:220: write_byte_msb (unsigned char v)
                           1185 ;	-----------------------------------------
                           1186 ;	 function write_byte_msb
                           1187 ;	-----------------------------------------
   092C                    1188 _write_byte_msb:
                           1189 ;	genReceive
                           1190 ;	spi.c:222: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1191 ;	genRLC
                           1192 ;	peephole 177.g	optimized mov sequence
   092C E5 82              1193 	mov	a,dpl
   092E FA                 1194 	mov	r2,a
   092F 23                 1195 	rl	a
                           1196 ;	spi.c:223: bitS_OUT = v & 0x1;
                           1197 ;	genGetAbit
   0930 FA                 1198 	mov	r2,a
                           1199 ;	Peephole 105	removed redundant mov
   0931 13                 1200 	rrc	a
   0932 92 81              1201 	mov	_bitS_OUT,c
                           1202 ;	spi.c:224: bitS_CLK = 1;
                           1203 ;	genAssign
   0934 D2 80              1204 	setb	_bitS_CLK
                           1205 ;	spi.c:225: bitS_CLK = 0;
                           1206 ;	genAssign
   0936 C2 80              1207 	clr	_bitS_CLK
                           1208 ;	spi.c:227: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1209 ;	genRLC
   0938 EA                 1210 	mov	a,r2
   0939 23                 1211 	rl	a
                           1212 ;	spi.c:228: bitS_OUT = v & 0x1;
                           1213 ;	genGetAbit
   093A FA                 1214 	mov	r2,a
                           1215 ;	Peephole 105	removed redundant mov
   093B 13                 1216 	rrc	a
   093C 92 81              1217 	mov	_bitS_OUT,c
                           1218 ;	spi.c:229: bitS_CLK = 1;
                           1219 ;	genAssign
   093E D2 80              1220 	setb	_bitS_CLK
                           1221 ;	spi.c:230: bitS_CLK = 0;
                           1222 ;	genAssign
   0940 C2 80              1223 	clr	_bitS_CLK
                           1224 ;	spi.c:232: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1225 ;	genRLC
   0942 EA                 1226 	mov	a,r2
   0943 23                 1227 	rl	a
                           1228 ;	spi.c:233: bitS_OUT = v & 0x1;
                           1229 ;	genGetAbit
   0944 FA                 1230 	mov	r2,a
                           1231 ;	Peephole 105	removed redundant mov
   0945 13                 1232 	rrc	a
   0946 92 81              1233 	mov	_bitS_OUT,c
                           1234 ;	spi.c:234: bitS_CLK = 1;
                           1235 ;	genAssign
   0948 D2 80              1236 	setb	_bitS_CLK
                           1237 ;	spi.c:235: bitS_CLK = 0;
                           1238 ;	genAssign
   094A C2 80              1239 	clr	_bitS_CLK
                           1240 ;	spi.c:237: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1241 ;	genRLC
   094C EA                 1242 	mov	a,r2
   094D 23                 1243 	rl	a
                           1244 ;	spi.c:238: bitS_OUT = v & 0x1;
                           1245 ;	genGetAbit
   094E FA                 1246 	mov	r2,a
                           1247 ;	Peephole 105	removed redundant mov
   094F 13                 1248 	rrc	a
   0950 92 81              1249 	mov	_bitS_OUT,c
                           1250 ;	spi.c:239: bitS_CLK = 1;
                           1251 ;	genAssign
   0952 D2 80              1252 	setb	_bitS_CLK
                           1253 ;	spi.c:240: bitS_CLK = 0;
                           1254 ;	genAssign
   0954 C2 80              1255 	clr	_bitS_CLK
                           1256 ;	spi.c:242: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1257 ;	genRLC
   0956 EA                 1258 	mov	a,r2
   0957 23                 1259 	rl	a
                           1260 ;	spi.c:243: bitS_OUT = v & 0x1;
                           1261 ;	genGetAbit
   0958 FA                 1262 	mov	r2,a
                           1263 ;	Peephole 105	removed redundant mov
   0959 13                 1264 	rrc	a
   095A 92 81              1265 	mov	_bitS_OUT,c
                           1266 ;	spi.c:244: bitS_CLK = 1;
                           1267 ;	genAssign
   095C D2 80              1268 	setb	_bitS_CLK
                           1269 ;	spi.c:245: bitS_CLK = 0;
                           1270 ;	genAssign
   095E C2 80              1271 	clr	_bitS_CLK
                           1272 ;	spi.c:247: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1273 ;	genRLC
   0960 EA                 1274 	mov	a,r2
   0961 23                 1275 	rl	a
                           1276 ;	spi.c:248: bitS_OUT = v & 0x1;
                           1277 ;	genGetAbit
   0962 FA                 1278 	mov	r2,a
                           1279 ;	Peephole 105	removed redundant mov
   0963 13                 1280 	rrc	a
   0964 92 81              1281 	mov	_bitS_OUT,c
                           1282 ;	spi.c:249: bitS_CLK = 1;
                           1283 ;	genAssign
   0966 D2 80              1284 	setb	_bitS_CLK
                           1285 ;	spi.c:250: bitS_CLK = 0;
                           1286 ;	genAssign
   0968 C2 80              1287 	clr	_bitS_CLK
                           1288 ;	spi.c:252: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1289 ;	genRLC
   096A EA                 1290 	mov	a,r2
   096B 23                 1291 	rl	a
                           1292 ;	spi.c:253: bitS_OUT = v & 0x1;
                           1293 ;	genGetAbit
   096C FA                 1294 	mov	r2,a
                           1295 ;	Peephole 105	removed redundant mov
   096D 13                 1296 	rrc	a
   096E 92 81              1297 	mov	_bitS_OUT,c
                           1298 ;	spi.c:254: bitS_CLK = 1;
                           1299 ;	genAssign
   0970 D2 80              1300 	setb	_bitS_CLK
                           1301 ;	spi.c:255: bitS_CLK = 0;
                           1302 ;	genAssign
   0972 C2 80              1303 	clr	_bitS_CLK
                           1304 ;	spi.c:257: v = (v << 1) | (v >> 7);	// rotate left (MSB into bottom bit)
                           1305 ;	genRLC
   0974 EA                 1306 	mov	a,r2
   0975 23                 1307 	rl	a
                           1308 ;	spi.c:258: bitS_OUT = v & 0x1;
                           1309 ;	genGetAbit
   0976 FA                 1310 	mov	r2,a
                           1311 ;	Peephole 105	removed redundant mov
   0977 13                 1312 	rrc	a
   0978 92 81              1313 	mov	_bitS_OUT,c
                           1314 ;	spi.c:259: bitS_CLK = 1;
                           1315 ;	genAssign
   097A D2 80              1316 	setb	_bitS_CLK
                           1317 ;	spi.c:260: bitS_CLK = 0;
                           1318 ;	genAssign
   097C C2 80              1319 	clr	_bitS_CLK
                           1320 ;	Peephole 300	removed redundant label 00101$
   097E 22                 1321 	ret
                           1322 ;------------------------------------------------------------
                           1323 ;Allocation info for local variables in function 'write_bytes_msb'
                           1324 ;------------------------------------------------------------
                           1325 ;len                       Allocated with name '_write_bytes_msb_PARM_2'
                           1326 ;buf                       Allocated to registers r2 r3 
                           1327 ;------------------------------------------------------------
                           1328 ;	spi.c:264: write_bytes_msb (const xdata unsigned char *buf, unsigned char len)
                           1329 ;	-----------------------------------------
                           1330 ;	 function write_bytes_msb
                           1331 ;	-----------------------------------------
   097F                    1332 _write_bytes_msb:
                           1333 ;	genReceive
   097F AA 82              1334 	mov	r2,dpl
   0981 AB 83              1335 	mov	r3,dph
                           1336 ;	spi.c:266: while (len-- != 0){
                           1337 ;	genAssign
                           1338 ;	genAssign
   0983 AC 2D              1339 	mov	r4,_write_bytes_msb_PARM_2
   0985                    1340 00101$:
                           1341 ;	genAssign
   0985 8C 05              1342 	mov	ar5,r4
                           1343 ;	genMinus
                           1344 ;	genMinusDec
   0987 1C                 1345 	dec	r4
                           1346 ;	genCmpEq
                           1347 ;	gencjneshort
   0988 BD 00 01           1348 	cjne	r5,#0x00,00109$
                           1349 ;	Peephole 112.b	changed ljmp to sjmp
                           1350 ;	Peephole 251.b	replaced sjmp to ret with ret
   098B 22                 1351 	ret
   098C                    1352 00109$:
                           1353 ;	spi.c:267: write_byte_msb (*buf++);
                           1354 ;	genPointerGet
                           1355 ;	genFarPointerGet
   098C 8A 82              1356 	mov	dpl,r2
   098E 8B 83              1357 	mov	dph,r3
   0990 E0                 1358 	movx	a,@dptr
   0991 FD                 1359 	mov	r5,a
   0992 A3                 1360 	inc	dptr
   0993 AA 82              1361 	mov	r2,dpl
   0995 AB 83              1362 	mov	r3,dph
                           1363 ;	genCall
   0997 8D 82              1364 	mov	dpl,r5
   0999 C0 02              1365 	push	ar2
   099B C0 03              1366 	push	ar3
   099D C0 04              1367 	push	ar4
   099F 12 09 2C           1368 	lcall	_write_byte_msb
   09A2 D0 04              1369 	pop	ar4
   09A4 D0 03              1370 	pop	ar3
   09A6 D0 02              1371 	pop	ar2
                           1372 ;	Peephole 112.b	changed ljmp to sjmp
   09A8 80 DB              1373 	sjmp	00101$
                           1374 ;	Peephole 259.a	removed redundant label 00104$ and ret
                           1375 ;
                           1376 ;------------------------------------------------------------
                           1377 ;Allocation info for local variables in function 'read_byte_msb'
                           1378 ;------------------------------------------------------------
                           1379 ;------------------------------------------------------------
                           1380 ;	spi.c:323: read_byte_msb (void) _naked
                           1381 ;	-----------------------------------------
                           1382 ;	 function read_byte_msb
                           1383 ;	-----------------------------------------
   09AA                    1384 _read_byte_msb:
                           1385 ;	naked function: no prologue.
                           1386 ;	spi.c:370: _endasm;
                           1387 ;	genInline
   09AA E4                 1388 	        clr a
   09AB D2 80              1389 	        setb _bitS_CLK
   09AD A2 82              1390 	        mov c, _bitS_IN
   09AF 33                 1391 	        rlc a
   09B0 C2 80              1392 	        clr _bitS_CLK
   09B2 D2 80              1393 	        setb _bitS_CLK
   09B4 A2 82              1394 	        mov c, _bitS_IN
   09B6 33                 1395 	        rlc a
   09B7 C2 80              1396 	        clr _bitS_CLK
   09B9 D2 80              1397 	        setb _bitS_CLK
   09BB A2 82              1398 	        mov c, _bitS_IN
   09BD 33                 1399 	        rlc a
   09BE C2 80              1400 	        clr _bitS_CLK
   09C0 D2 80              1401 	        setb _bitS_CLK
   09C2 A2 82              1402 	        mov c, _bitS_IN
   09C4 33                 1403 	        rlc a
   09C5 C2 80              1404 	        clr _bitS_CLK
   09C7 D2 80              1405 	        setb _bitS_CLK
   09C9 A2 82              1406 	        mov c, _bitS_IN
   09CB 33                 1407 	        rlc a
   09CC C2 80              1408 	        clr _bitS_CLK
   09CE D2 80              1409 	        setb _bitS_CLK
   09D0 A2 82              1410 	        mov c, _bitS_IN
   09D2 33                 1411 	        rlc a
   09D3 C2 80              1412 	        clr _bitS_CLK
   09D5 D2 80              1413 	        setb _bitS_CLK
   09D7 A2 82              1414 	        mov c, _bitS_IN
   09D9 33                 1415 	        rlc a
   09DA C2 80              1416 	        clr _bitS_CLK
   09DC D2 80              1417 	        setb _bitS_CLK
   09DE A2 82              1418 	        mov c, _bitS_IN
   09E0 33                 1419 	        rlc a
   09E1 C2 80              1420 	        clr _bitS_CLK
   09E3 F5 82              1421 	        mov dpl,a
   09E5 22                 1422 	        ret
                           1423 ;	Peephole 300	removed redundant label 00101$
                           1424 ;	naked function: no epilogue.
                           1425 ;------------------------------------------------------------
                           1426 ;Allocation info for local variables in function 'read_bytes_msb'
                           1427 ;------------------------------------------------------------
                           1428 ;len                       Allocated with name '_read_bytes_msb_PARM_2'
                           1429 ;buf                       Allocated to registers r2 r3 
                           1430 ;------------------------------------------------------------
                           1431 ;	spi.c:375: read_bytes_msb (xdata unsigned char *buf, unsigned char len)
                           1432 ;	-----------------------------------------
                           1433 ;	 function read_bytes_msb
                           1434 ;	-----------------------------------------
   09E6                    1435 _read_bytes_msb:
                           1436 ;	genReceive
   09E6 AA 82              1437 	mov	r2,dpl
   09E8 AB 83              1438 	mov	r3,dph
                           1439 ;	spi.c:377: while (len-- != 0){
                           1440 ;	genAssign
                           1441 ;	genAssign
   09EA AC 2E              1442 	mov	r4,_read_bytes_msb_PARM_2
   09EC                    1443 00101$:
                           1444 ;	genAssign
   09EC 8C 05              1445 	mov	ar5,r4
                           1446 ;	genMinus
                           1447 ;	genMinusDec
   09EE 1C                 1448 	dec	r4
                           1449 ;	genCmpEq
                           1450 ;	gencjneshort
   09EF BD 00 01           1451 	cjne	r5,#0x00,00109$
                           1452 ;	Peephole 112.b	changed ljmp to sjmp
                           1453 ;	Peephole 251.b	replaced sjmp to ret with ret
   09F2 22                 1454 	ret
   09F3                    1455 00109$:
                           1456 ;	spi.c:378: *buf++ = read_byte_msb ();
                           1457 ;	genCall
   09F3 12 09 AA           1458 	lcall	_read_byte_msb
   09F6 AD 82              1459 	mov	r5,dpl
                           1460 ;	genPointerSet
                           1461 ;     genFarPointerSet
   09F8 8A 82              1462 	mov	dpl,r2
   09FA 8B 83              1463 	mov	dph,r3
   09FC ED                 1464 	mov	a,r5
   09FD F0                 1465 	movx	@dptr,a
   09FE A3                 1466 	inc	dptr
   09FF AA 82              1467 	mov	r2,dpl
   0A01 AB 83              1468 	mov	r3,dph
                           1469 ;	Peephole 112.b	changed ljmp to sjmp
   0A03 80 E7              1470 	sjmp	00101$
                           1471 ;	Peephole 259.a	removed redundant label 00104$ and ret
                           1472 ;
                           1473 	.area CSEG    (CODE)
                           1474 	.area CONST   (CODE)

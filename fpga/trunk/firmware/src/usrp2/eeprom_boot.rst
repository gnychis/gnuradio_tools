                              1 ;--------------------------------------------------------
                              2 ; Hand tweaked minimal eeprom boot code
                              3 ;--------------------------------------------------------
                              4 	.module eeprom_boot
                              5 	.optsdcc -mmcs51 --model-small
                              6 	
                              7 ;--------------------------------------------------------
                              8 ; Public variables in this module
                              9 ;--------------------------------------------------------
                             10 	.globl _eeprom_init
                             11 	.globl _EP8FIFOBUF
                             12 	.globl _EP6FIFOBUF
                             13 	.globl _EP4FIFOBUF
                             14 	.globl _EP2FIFOBUF
                             15 	.globl _EP1INBUF
                             16 	.globl _EP1OUTBUF
                             17 	.globl _EP0BUF
                             18 	.globl _CT4
                             19 	.globl _CT3
                             20 	.globl _CT2
                             21 	.globl _CT1
                             22 	.globl _USBTEST
                             23 	.globl _TESTCFG
                             24 	.globl _DBUG
                             25 	.globl _UDMACRCQUAL
                             26 	.globl _UDMACRCL
                             27 	.globl _UDMACRCH
                             28 	.globl _GPIFHOLDAMOUNT
                             29 	.globl _FLOWSTBHPERIOD
                             30 	.globl _FLOWSTBEDGE
                             31 	.globl _FLOWSTB
                             32 	.globl _FLOWHOLDOFF
                             33 	.globl _FLOWEQ1CTL
                             34 	.globl _FLOWEQ0CTL
                             35 	.globl _FLOWLOGIC
                             36 	.globl _FLOWSTATE
                             37 	.globl _GPIFABORT
                             38 	.globl _GPIFREADYSTAT
                             39 	.globl _GPIFREADYCFG
                             40 	.globl _XGPIFSGLDATLNOX
                             41 	.globl _XGPIFSGLDATLX
                             42 	.globl _XGPIFSGLDATH
                             43 	.globl _EP8GPIFTRIG
                             44 	.globl _EP8GPIFPFSTOP
                             45 	.globl _EP8GPIFFLGSEL
                             46 	.globl _EP6GPIFTRIG
                             47 	.globl _EP6GPIFPFSTOP
                             48 	.globl _EP6GPIFFLGSEL
                             49 	.globl _EP4GPIFTRIG
                             50 	.globl _EP4GPIFPFSTOP
                             51 	.globl _EP4GPIFFLGSEL
                             52 	.globl _EP2GPIFTRIG
                             53 	.globl _EP2GPIFPFSTOP
                             54 	.globl _EP2GPIFFLGSEL
                             55 	.globl _GPIFTCB0
                             56 	.globl _GPIFTCB1
                             57 	.globl _GPIFTCB2
                             58 	.globl _GPIFTCB3
                             59 	.globl _GPIFADRL
                             60 	.globl _GPIFADRH
                             61 	.globl _GPIFCTLCFG
                             62 	.globl _GPIFIDLECTL
                             63 	.globl _GPIFIDLECS
                             64 	.globl _GPIFWFSELECT
                             65 	.globl _SETUPDAT
                             66 	.globl _SUDPTRCTL
                             67 	.globl _SUDPTRL
                             68 	.globl _SUDPTRH
                             69 	.globl _EP8FIFOBCL
                             70 	.globl _EP8FIFOBCH
                             71 	.globl _EP6FIFOBCL
                             72 	.globl _EP6FIFOBCH
                             73 	.globl _EP4FIFOBCL
                             74 	.globl _EP4FIFOBCH
                             75 	.globl _EP2FIFOBCL
                             76 	.globl _EP2FIFOBCH
                             77 	.globl _EP8FIFOFLGS
                             78 	.globl _EP6FIFOFLGS
                             79 	.globl _EP4FIFOFLGS
                             80 	.globl _EP2FIFOFLGS
                             81 	.globl _EP8CS
                             82 	.globl _EP6CS
                             83 	.globl _EP4CS
                             84 	.globl _EP2CS
                             85 	.globl _EP1INCS
                             86 	.globl _EP1OUTCS
                             87 	.globl _EP0CS
                             88 	.globl _EP8BCL
                             89 	.globl _EP8BCH
                             90 	.globl _EP6BCL
                             91 	.globl _EP6BCH
                             92 	.globl _EP4BCL
                             93 	.globl _EP4BCH
                             94 	.globl _EP2BCL
                             95 	.globl _EP2BCH
                             96 	.globl _EP1INBC
                             97 	.globl _EP1OUTBC
                             98 	.globl _EP0BCL
                             99 	.globl _EP0BCH
                            100 	.globl _FNADDR
                            101 	.globl _MICROFRAME
                            102 	.globl _USBFRAMEL
                            103 	.globl _USBFRAMEH
                            104 	.globl _TOGCTL
                            105 	.globl _WAKEUPCS
                            106 	.globl _SUSPEND
                            107 	.globl _USBCS
                            108 	.globl _XAUTODAT2
                            109 	.globl _XAUTODAT1
                            110 	.globl _I2CTL
                            111 	.globl _I2DAT
                            112 	.globl _I2CS
                            113 	.globl _PORTECFG
                            114 	.globl _PORTCCFG
                            115 	.globl _PORTACFG
                            116 	.globl _INTSETUP
                            117 	.globl _INT4IVEC
                            118 	.globl _INT2IVEC
                            119 	.globl _CLRERRCNT
                            120 	.globl _ERRCNTLIM
                            121 	.globl _USBERRIRQ
                            122 	.globl _USBERRIE
                            123 	.globl _GPIFIRQ
                            124 	.globl _GPIFIE
                            125 	.globl _EPIRQ
                            126 	.globl _EPIE
                            127 	.globl _USBIRQ
                            128 	.globl _USBIE
                            129 	.globl _NAKIRQ
                            130 	.globl _NAKIE
                            131 	.globl _IBNIRQ
                            132 	.globl _IBNIE
                            133 	.globl _EP8FIFOIRQ
                            134 	.globl _EP8FIFOIE
                            135 	.globl _EP6FIFOIRQ
                            136 	.globl _EP6FIFOIE
                            137 	.globl _EP4FIFOIRQ
                            138 	.globl _EP4FIFOIE
                            139 	.globl _EP2FIFOIRQ
                            140 	.globl _EP2FIFOIE
                            141 	.globl _OUTPKTEND
                            142 	.globl _INPKTEND
                            143 	.globl _EP8ISOINPKTS
                            144 	.globl _EP6ISOINPKTS
                            145 	.globl _EP4ISOINPKTS
                            146 	.globl _EP2ISOINPKTS
                            147 	.globl _EP8FIFOPFL
                            148 	.globl _EP8FIFOPFH
                            149 	.globl _EP6FIFOPFL
                            150 	.globl _EP6FIFOPFH
                            151 	.globl _EP4FIFOPFL
                            152 	.globl _EP4FIFOPFH
                            153 	.globl _EP2FIFOPFL
                            154 	.globl _EP2FIFOPFH
                            155 	.globl _EP8AUTOINLENL
                            156 	.globl _EP8AUTOINLENH
                            157 	.globl _EP6AUTOINLENL
                            158 	.globl _EP6AUTOINLENH
                            159 	.globl _EP4AUTOINLENL
                            160 	.globl _EP4AUTOINLENH
                            161 	.globl _EP2AUTOINLENL
                            162 	.globl _EP2AUTOINLENH
                            163 	.globl _EP8FIFOCFG
                            164 	.globl _EP6FIFOCFG
                            165 	.globl _EP4FIFOCFG
                            166 	.globl _EP2FIFOCFG
                            167 	.globl _EP8CFG
                            168 	.globl _EP6CFG
                            169 	.globl _EP4CFG
                            170 	.globl _EP2CFG
                            171 	.globl _EP1INCFG
                            172 	.globl _EP1OUTCFG
                            173 	.globl _REVCTL
                            174 	.globl _REVID
                            175 	.globl _FIFOPINPOLAR
                            176 	.globl _UART230
                            177 	.globl _BPADDRL
                            178 	.globl _BPADDRH
                            179 	.globl _BREAKPT
                            180 	.globl _FIFORESET
                            181 	.globl _PINFLAGSCD
                            182 	.globl _PINFLAGSAB
                            183 	.globl _IFCONFIG
                            184 	.globl _CPUCS
                            185 	.globl _RES_WAVEDATA_END
                            186 	.globl _GPIF_WAVE_DATA
                            187 ;--------------------------------------------------------
                            188 ; special function registers
                            189 ;--------------------------------------------------------
                    0080    190 _IOA	=	0x0080
                    0081    191 _SP	=	0x0081
                    0082    192 _DPL	=	0x0082
                    0083    193 _DPH	=	0x0083
                    0084    194 _DPL1	=	0x0084
                    0085    195 _DPH1	=	0x0085
                    0086    196 _DPS	=	0x0086
                    0087    197 _PCON	=	0x0087
                    0088    198 _TCON	=	0x0088
                    0089    199 _TMOD	=	0x0089
                    008A    200 _TL0	=	0x008a
                    008B    201 _TL1	=	0x008b
                    008C    202 _TH0	=	0x008c
                    008D    203 _TH1	=	0x008d
                    008E    204 _CKCON	=	0x008e
                    0090    205 _IOB	=	0x0090
                    0091    206 _EXIF	=	0x0091
                    0092    207 _MPAGE	=	0x0092
                    0098    208 _SCON0	=	0x0098
                    0099    209 _SBUF0	=	0x0099
                    009A    210 _APTR1H	=	0x009a
                    009B    211 _APTR1L	=	0x009b
                    009C    212 _AUTODAT1	=	0x009c
                    009D    213 _AUTOPTRH2	=	0x009d
                    009E    214 _AUTOPTRL2	=	0x009e
                    009F    215 _AUTODAT2	=	0x009f
                    00A0    216 _IOC	=	0x00a0
                    00A1    217 _INT2CLR	=	0x00a1
                    00A2    218 _INT4CLR	=	0x00a2
                    00A8    219 _IE	=	0x00a8
                    00AA    220 _EP2468STAT	=	0x00aa
                    00AB    221 _EP24FIFOFLGS	=	0x00ab
                    00AC    222 _EP68FIFOFLGS	=	0x00ac
                    00AF    223 _AUTOPTRSETUP	=	0x00af
                    00B0    224 _IOD	=	0x00b0
                    00B1    225 _IOE	=	0x00b1
                    00B2    226 _OEA	=	0x00b2
                    00B3    227 _OEB	=	0x00b3
                    00B4    228 _OEC	=	0x00b4
                    00B5    229 _OED	=	0x00b5
                    00B6    230 _OEE	=	0x00b6
                    00B8    231 _IP	=	0x00b8
                    00BA    232 _EP01STAT	=	0x00ba
                    00BB    233 _GPIFTRIG	=	0x00bb
                    00BD    234 _GPIFSGLDATH	=	0x00bd
                    00BE    235 _GPIFSGLDATLX	=	0x00be
                    00BF    236 _GPIFSGLDATLNOX	=	0x00bf
                    00C0    237 _SCON1	=	0x00c0
                    00C1    238 _SBUF1	=	0x00c1
                    00C8    239 _T2CON	=	0x00c8
                    00CA    240 _RCAP2L	=	0x00ca
                    00CB    241 _RCAP2H	=	0x00cb
                    00CC    242 _TL2	=	0x00cc
                    00CD    243 _TH2	=	0x00cd
                    00D0    244 _PSW	=	0x00d0
                    00D8    245 _EICON	=	0x00d8
                    00E0    246 _ACC	=	0x00e0
                    00E8    247 _EIE	=	0x00e8
                    00F0    248 _B	=	0x00f0
                    00F8    249 _EIP	=	0x00f8
                            250 ;--------------------------------------------------------
                            251 ; special function bits 
                            252 ;--------------------------------------------------------
                    0086    253 _SEL	=	0x0086
                    0088    254 _IT0	=	0x0088
                    0089    255 _IE0	=	0x0089
                    008A    256 _IT1	=	0x008a
                    008B    257 _IE1	=	0x008b
                    008C    258 _TR0	=	0x008c
                    008D    259 _TF0	=	0x008d
                    008E    260 _TR1	=	0x008e
                    008F    261 _TF1	=	0x008f
                    0098    262 _RI	=	0x0098
                    0099    263 _TI	=	0x0099
                    009A    264 _RB8	=	0x009a
                    009B    265 _TB8	=	0x009b
                    009C    266 _REN	=	0x009c
                    009D    267 _SM2	=	0x009d
                    009E    268 _SM1	=	0x009e
                    009F    269 _SM0	=	0x009f
                    00A8    270 _EX0	=	0x00a8
                    00A9    271 _ET0	=	0x00a9
                    00AA    272 _EX1	=	0x00aa
                    00AB    273 _ET1	=	0x00ab
                    00AC    274 _ES0	=	0x00ac
                    00AD    275 _ET2	=	0x00ad
                    00AE    276 _ES1	=	0x00ae
                    00AF    277 _EA	=	0x00af
                    00B8    278 _PX0	=	0x00b8
                    00B9    279 _PT0	=	0x00b9
                    00BA    280 _PX1	=	0x00ba
                    00BB    281 _PT1	=	0x00bb
                    00BC    282 _PS0	=	0x00bc
                    00BD    283 _PT2	=	0x00bd
                    00BE    284 _PS1	=	0x00be
                    00C0    285 _RI1	=	0x00c0
                    00C1    286 _TI1	=	0x00c1
                    00C2    287 _RB81	=	0x00c2
                    00C3    288 _TB81	=	0x00c3
                    00C4    289 _REN1	=	0x00c4
                    00C5    290 _SM21	=	0x00c5
                    00C6    291 _SM11	=	0x00c6
                    00C7    292 _SM01	=	0x00c7
                    00C8    293 _CP_RL2	=	0x00c8
                    00C9    294 _C_T2	=	0x00c9
                    00CA    295 _TR2	=	0x00ca
                    00CB    296 _EXEN2	=	0x00cb
                    00CC    297 _TCLK	=	0x00cc
                    00CD    298 _RCLK	=	0x00cd
                    00CE    299 _EXF2	=	0x00ce
                    00CF    300 _TF2	=	0x00cf
                    00D0    301 _P	=	0x00d0
                    00D1    302 _FL	=	0x00d1
                    00D2    303 _OV	=	0x00d2
                    00D3    304 _RS0	=	0x00d3
                    00D4    305 _RS1	=	0x00d4
                    00D5    306 _F0	=	0x00d5
                    00D6    307 _AC	=	0x00d6
                    00D7    308 _CY	=	0x00d7
                    00DB    309 _INT6	=	0x00db
                    00DC    310 _RESI	=	0x00dc
                    00DD    311 _ERESI	=	0x00dd
                    00DF    312 _SMOD1	=	0x00df
                    00E8    313 _EIUSB	=	0x00e8
                    00E9    314 _EI2C	=	0x00e9
                    00EA    315 _EIEX4	=	0x00ea
                    00EB    316 _EIEX5	=	0x00eb
                    00EC    317 _EIEX6	=	0x00ec
                    00F8    318 _PUSB	=	0x00f8
                    00F9    319 _PI2C	=	0x00f9
                    00FA    320 _EIPX4	=	0x00fa
                    00FB    321 _EIPX5	=	0x00fb
                    00FC    322 _EIPX6	=	0x00fc
                    0080    323 _bitS_CLK	=	0x0080
                    0081    324 _bitS_OUT	=	0x0081
                    0082    325 _bitS_IN	=	0x0082
                    00A1    326 _bitALTERA_DATA0	=	0x00a1
                    00A3    327 _bitALTERA_DCLK	=	0x00a3
                            328 ;--------------------------------------------------------
                            329 ; overlayable register banks 
                            330 ;--------------------------------------------------------
                            331 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                     332 	.ds 8
                            333 ;--------------------------------------------------------
                            334 ; internal ram data
                            335 ;--------------------------------------------------------
                            336 	.area DSEG    (DATA)
                            337 ;--------------------------------------------------------
                            338 ; overlayable items in internal ram 
                            339 ;--------------------------------------------------------
                            340 	.area OSEG    (OVR,DATA)
                            341 ;--------------------------------------------------------
                            342 ; Stack segment in internal ram 
                            343 ;--------------------------------------------------------
                            344 	.area	SSEG	(DATA)
   0009                     345 __start__stack:
   0009                     346 	.ds	1
                            347 
                            348 ;--------------------------------------------------------
                            349 ; indirectly addressable internal ram data
                            350 ;--------------------------------------------------------
                            351 	.area ISEG    (DATA)
                            352 ;--------------------------------------------------------
                            353 ; bit data
                            354 ;--------------------------------------------------------
                            355 	.area BSEG    (BIT)
                            356 ;--------------------------------------------------------
                            357 ; external ram data
                            358 ;--------------------------------------------------------
                            359 	.area XSEG    (XDATA)
                    E400    360 _GPIF_WAVE_DATA	=	0xe400
                    E480    361 _RES_WAVEDATA_END	=	0xe480
                    E600    362 _CPUCS	=	0xe600
                    E601    363 _IFCONFIG	=	0xe601
                    E602    364 _PINFLAGSAB	=	0xe602
                    E603    365 _PINFLAGSCD	=	0xe603
                    E604    366 _FIFORESET	=	0xe604
                    E605    367 _BREAKPT	=	0xe605
                    E606    368 _BPADDRH	=	0xe606
                    E607    369 _BPADDRL	=	0xe607
                    E608    370 _UART230	=	0xe608
                    E609    371 _FIFOPINPOLAR	=	0xe609
                    E60A    372 _REVID	=	0xe60a
                    E60B    373 _REVCTL	=	0xe60b
                    E610    374 _EP1OUTCFG	=	0xe610
                    E611    375 _EP1INCFG	=	0xe611
                    E612    376 _EP2CFG	=	0xe612
                    E613    377 _EP4CFG	=	0xe613
                    E614    378 _EP6CFG	=	0xe614
                    E615    379 _EP8CFG	=	0xe615
                    E618    380 _EP2FIFOCFG	=	0xe618
                    E619    381 _EP4FIFOCFG	=	0xe619
                    E61A    382 _EP6FIFOCFG	=	0xe61a
                    E61B    383 _EP8FIFOCFG	=	0xe61b
                    E620    384 _EP2AUTOINLENH	=	0xe620
                    E621    385 _EP2AUTOINLENL	=	0xe621
                    E622    386 _EP4AUTOINLENH	=	0xe622
                    E623    387 _EP4AUTOINLENL	=	0xe623
                    E624    388 _EP6AUTOINLENH	=	0xe624
                    E625    389 _EP6AUTOINLENL	=	0xe625
                    E626    390 _EP8AUTOINLENH	=	0xe626
                    E627    391 _EP8AUTOINLENL	=	0xe627
                    E630    392 _EP2FIFOPFH	=	0xe630
                    E631    393 _EP2FIFOPFL	=	0xe631
                    E632    394 _EP4FIFOPFH	=	0xe632
                    E633    395 _EP4FIFOPFL	=	0xe633
                    E634    396 _EP6FIFOPFH	=	0xe634
                    E635    397 _EP6FIFOPFL	=	0xe635
                    E636    398 _EP8FIFOPFH	=	0xe636
                    E637    399 _EP8FIFOPFL	=	0xe637
                    E640    400 _EP2ISOINPKTS	=	0xe640
                    E641    401 _EP4ISOINPKTS	=	0xe641
                    E642    402 _EP6ISOINPKTS	=	0xe642
                    E643    403 _EP8ISOINPKTS	=	0xe643
                    E648    404 _INPKTEND	=	0xe648
                    E649    405 _OUTPKTEND	=	0xe649
                    E650    406 _EP2FIFOIE	=	0xe650
                    E651    407 _EP2FIFOIRQ	=	0xe651
                    E652    408 _EP4FIFOIE	=	0xe652
                    E653    409 _EP4FIFOIRQ	=	0xe653
                    E654    410 _EP6FIFOIE	=	0xe654
                    E655    411 _EP6FIFOIRQ	=	0xe655
                    E656    412 _EP8FIFOIE	=	0xe656
                    E657    413 _EP8FIFOIRQ	=	0xe657
                    E658    414 _IBNIE	=	0xe658
                    E659    415 _IBNIRQ	=	0xe659
                    E65A    416 _NAKIE	=	0xe65a
                    E65B    417 _NAKIRQ	=	0xe65b
                    E65C    418 _USBIE	=	0xe65c
                    E65D    419 _USBIRQ	=	0xe65d
                    E65E    420 _EPIE	=	0xe65e
                    E65F    421 _EPIRQ	=	0xe65f
                    E660    422 _GPIFIE	=	0xe660
                    E661    423 _GPIFIRQ	=	0xe661
                    E662    424 _USBERRIE	=	0xe662
                    E663    425 _USBERRIRQ	=	0xe663
                    E664    426 _ERRCNTLIM	=	0xe664
                    E665    427 _CLRERRCNT	=	0xe665
                    E666    428 _INT2IVEC	=	0xe666
                    E667    429 _INT4IVEC	=	0xe667
                    E668    430 _INTSETUP	=	0xe668
                    E670    431 _PORTACFG	=	0xe670
                    E671    432 _PORTCCFG	=	0xe671
                    E672    433 _PORTECFG	=	0xe672
                    E678    434 _I2CS	=	0xe678
                    E679    435 _I2DAT	=	0xe679
                    E67A    436 _I2CTL	=	0xe67a
                    E67B    437 _XAUTODAT1	=	0xe67b
                    E67C    438 _XAUTODAT2	=	0xe67c
                    E680    439 _USBCS	=	0xe680
                    E681    440 _SUSPEND	=	0xe681
                    E682    441 _WAKEUPCS	=	0xe682
                    E683    442 _TOGCTL	=	0xe683
                    E684    443 _USBFRAMEH	=	0xe684
                    E685    444 _USBFRAMEL	=	0xe685
                    E686    445 _MICROFRAME	=	0xe686
                    E687    446 _FNADDR	=	0xe687
                    E68A    447 _EP0BCH	=	0xe68a
                    E68B    448 _EP0BCL	=	0xe68b
                    E68D    449 _EP1OUTBC	=	0xe68d
                    E68F    450 _EP1INBC	=	0xe68f
                    E690    451 _EP2BCH	=	0xe690
                    E691    452 _EP2BCL	=	0xe691
                    E694    453 _EP4BCH	=	0xe694
                    E695    454 _EP4BCL	=	0xe695
                    E698    455 _EP6BCH	=	0xe698
                    E699    456 _EP6BCL	=	0xe699
                    E69C    457 _EP8BCH	=	0xe69c
                    E69D    458 _EP8BCL	=	0xe69d
                    E6A0    459 _EP0CS	=	0xe6a0
                    E6A1    460 _EP1OUTCS	=	0xe6a1
                    E6A2    461 _EP1INCS	=	0xe6a2
                    E6A3    462 _EP2CS	=	0xe6a3
                    E6A4    463 _EP4CS	=	0xe6a4
                    E6A5    464 _EP6CS	=	0xe6a5
                    E6A6    465 _EP8CS	=	0xe6a6
                    E6A7    466 _EP2FIFOFLGS	=	0xe6a7
                    E6A8    467 _EP4FIFOFLGS	=	0xe6a8
                    E6A9    468 _EP6FIFOFLGS	=	0xe6a9
                    E6AA    469 _EP8FIFOFLGS	=	0xe6aa
                    E6AB    470 _EP2FIFOBCH	=	0xe6ab
                    E6AC    471 _EP2FIFOBCL	=	0xe6ac
                    E6AD    472 _EP4FIFOBCH	=	0xe6ad
                    E6AE    473 _EP4FIFOBCL	=	0xe6ae
                    E6AF    474 _EP6FIFOBCH	=	0xe6af
                    E6B0    475 _EP6FIFOBCL	=	0xe6b0
                    E6B1    476 _EP8FIFOBCH	=	0xe6b1
                    E6B2    477 _EP8FIFOBCL	=	0xe6b2
                    E6B3    478 _SUDPTRH	=	0xe6b3
                    E6B4    479 _SUDPTRL	=	0xe6b4
                    E6B5    480 _SUDPTRCTL	=	0xe6b5
                    E6B8    481 _SETUPDAT	=	0xe6b8
                    E6C0    482 _GPIFWFSELECT	=	0xe6c0
                    E6C1    483 _GPIFIDLECS	=	0xe6c1
                    E6C2    484 _GPIFIDLECTL	=	0xe6c2
                    E6C3    485 _GPIFCTLCFG	=	0xe6c3
                    E6C4    486 _GPIFADRH	=	0xe6c4
                    E6C5    487 _GPIFADRL	=	0xe6c5
                    E6CE    488 _GPIFTCB3	=	0xe6ce
                    E6CF    489 _GPIFTCB2	=	0xe6cf
                    E6D0    490 _GPIFTCB1	=	0xe6d0
                    E6D1    491 _GPIFTCB0	=	0xe6d1
                    E6D2    492 _EP2GPIFFLGSEL	=	0xe6d2
                    E6D3    493 _EP2GPIFPFSTOP	=	0xe6d3
                    E6D4    494 _EP2GPIFTRIG	=	0xe6d4
                    E6DA    495 _EP4GPIFFLGSEL	=	0xe6da
                    E6DB    496 _EP4GPIFPFSTOP	=	0xe6db
                    E6DC    497 _EP4GPIFTRIG	=	0xe6dc
                    E6E2    498 _EP6GPIFFLGSEL	=	0xe6e2
                    E6E3    499 _EP6GPIFPFSTOP	=	0xe6e3
                    E6E4    500 _EP6GPIFTRIG	=	0xe6e4
                    E6EA    501 _EP8GPIFFLGSEL	=	0xe6ea
                    E6EB    502 _EP8GPIFPFSTOP	=	0xe6eb
                    E6EC    503 _EP8GPIFTRIG	=	0xe6ec
                    E6F0    504 _XGPIFSGLDATH	=	0xe6f0
                    E6F1    505 _XGPIFSGLDATLX	=	0xe6f1
                    E6F2    506 _XGPIFSGLDATLNOX	=	0xe6f2
                    E6F3    507 _GPIFREADYCFG	=	0xe6f3
                    E6F4    508 _GPIFREADYSTAT	=	0xe6f4
                    E6F5    509 _GPIFABORT	=	0xe6f5
                    E6C6    510 _FLOWSTATE	=	0xe6c6
                    E6C7    511 _FLOWLOGIC	=	0xe6c7
                    E6C8    512 _FLOWEQ0CTL	=	0xe6c8
                    E6C9    513 _FLOWEQ1CTL	=	0xe6c9
                    E6CA    514 _FLOWHOLDOFF	=	0xe6ca
                    E6CB    515 _FLOWSTB	=	0xe6cb
                    E6CC    516 _FLOWSTBEDGE	=	0xe6cc
                    E6CD    517 _FLOWSTBHPERIOD	=	0xe6cd
                    E60C    518 _GPIFHOLDAMOUNT	=	0xe60c
                    E67D    519 _UDMACRCH	=	0xe67d
                    E67E    520 _UDMACRCL	=	0xe67e
                    E67F    521 _UDMACRCQUAL	=	0xe67f
                    E6F8    522 _DBUG	=	0xe6f8
                    E6F9    523 _TESTCFG	=	0xe6f9
                    E6FA    524 _USBTEST	=	0xe6fa
                    E6FB    525 _CT1	=	0xe6fb
                    E6FC    526 _CT2	=	0xe6fc
                    E6FD    527 _CT3	=	0xe6fd
                    E6FE    528 _CT4	=	0xe6fe
                    E740    529 _EP0BUF	=	0xe740
                    E780    530 _EP1OUTBUF	=	0xe780
                    E7C0    531 _EP1INBUF	=	0xe7c0
                    F000    532 _EP2FIFOBUF	=	0xf000
                    F400    533 _EP4FIFOBUF	=	0xf400
                    F800    534 _EP6FIFOBUF	=	0xf800
                    FC00    535 _EP8FIFOBUF	=	0xfc00
                            536 ;--------------------------------------------------------
                            537 ; external initialized ram data
                            538 ;--------------------------------------------------------
                            539 ;--------------------------------------------------------
                            540 ; interrupt vector 
                            541 ;--------------------------------------------------------
                            542 	.area CSEG    (CODE)
   0000                     543 __interrupt_vect:
   0000 02 00 B3            544 	ljmp	__sdcc_gsinit_startup
                            545 ;--------------------------------------------------------
                            546 ; global & static initialisations
                            547 ;--------------------------------------------------------
                            548 	.area GSINIT  (CODE)
                            549 	.area GSFINAL (CODE)
                            550 	.area GSINIT  (CODE)
   00B3                     551 __sdcc_gsinit_startup:
   00B3 75 81 08            552 	mov	sp,#__start__stack - 1
   00B6 12 00 91            553 	lcall	__sdcc_external_startup
   00B9 E5 82               554 	mov	a,dpl
   00BB 60 03               555 	jz	__sdcc_init_data
   00BD 02 00 03            556 	ljmp	__sdcc_program_startup
   00C0                     557 __sdcc_init_data:
                            558 	.area GSFINAL (CODE)
   00C0 02 00 03            559 	ljmp	__sdcc_program_startup
                            560 ;--------------------------------------------------------
                            561 ; Home
                            562 ;--------------------------------------------------------
                            563 	.area HOME    (CODE)
                            564 	.area CSEG    (CODE)
                            565 ;--------------------------------------------------------
                            566 ; code
                            567 ;--------------------------------------------------------
                            568 	.area CSEG    (CODE)
   0003                     569 __sdcc_program_startup:
   0003 12 00 2D            570 	lcall	_eeprom_init
                            571 ;	return from _eeprom_init will spin here
   0006 80 FE               572 	sjmp .
                            573 	.area CSEG    (CODE)

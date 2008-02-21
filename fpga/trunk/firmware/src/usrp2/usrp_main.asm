;--------------------------------------------------------
; File Created by SDCC : FreeWare ANSI-C Compiler
; Version 2.6.0 #4309 (Nov 10 2006)
; This file generated Wed Jan 23 16:41:20 2008
;--------------------------------------------------------
	.module usrp_main
	.optsdcc -mmcs51 --model-small
	
;--------------------------------------------------------
; Public variables in this module
;--------------------------------------------------------
	.globl _main
	.globl _patch_usb_descriptors
	.globl _isr_tick
	.globl _bitALTERA_DCLK
	.globl _bitALTERA_DATA0
	.globl _bitS_IN
	.globl _bitS_OUT
	.globl _bitS_CLK
	.globl _EIPX6
	.globl _EIPX5
	.globl _EIPX4
	.globl _PI2C
	.globl _PUSB
	.globl _EIEX6
	.globl _EIEX5
	.globl _EIEX4
	.globl _EI2C
	.globl _EIUSB
	.globl _SMOD1
	.globl _ERESI
	.globl _RESI
	.globl _INT6
	.globl _CY
	.globl _AC
	.globl _F0
	.globl _RS1
	.globl _RS0
	.globl _OV
	.globl _FL
	.globl _P
	.globl _TF2
	.globl _EXF2
	.globl _RCLK
	.globl _TCLK
	.globl _EXEN2
	.globl _TR2
	.globl _C_T2
	.globl _CP_RL2
	.globl _SM01
	.globl _SM11
	.globl _SM21
	.globl _REN1
	.globl _TB81
	.globl _RB81
	.globl _TI1
	.globl _RI1
	.globl _PS1
	.globl _PT2
	.globl _PS0
	.globl _PT1
	.globl _PX1
	.globl _PT0
	.globl _PX0
	.globl _EA
	.globl _ES1
	.globl _ET2
	.globl _ES0
	.globl _ET1
	.globl _EX1
	.globl _ET0
	.globl _EX0
	.globl _SM0
	.globl _SM1
	.globl _SM2
	.globl _REN
	.globl _TB8
	.globl _RB8
	.globl _TI
	.globl _RI
	.globl _TF1
	.globl _TR1
	.globl _TF0
	.globl _TR0
	.globl _IE1
	.globl _IT1
	.globl _IE0
	.globl _IT0
	.globl _SEL
	.globl _EIP
	.globl _B
	.globl _EIE
	.globl _ACC
	.globl _EICON
	.globl _PSW
	.globl _TH2
	.globl _TL2
	.globl _RCAP2H
	.globl _RCAP2L
	.globl _T2CON
	.globl _SBUF1
	.globl _SCON1
	.globl _GPIFSGLDATLNOX
	.globl _GPIFSGLDATLX
	.globl _GPIFSGLDATH
	.globl _GPIFTRIG
	.globl _EP01STAT
	.globl _IP
	.globl _OEE
	.globl _OED
	.globl _OEC
	.globl _OEB
	.globl _OEA
	.globl _IOE
	.globl _IOD
	.globl _AUTOPTRSETUP
	.globl _EP68FIFOFLGS
	.globl _EP24FIFOFLGS
	.globl _EP2468STAT
	.globl _IE
	.globl _INT4CLR
	.globl _INT2CLR
	.globl _IOC
	.globl _AUTODAT2
	.globl _AUTOPTRL2
	.globl _AUTOPTRH2
	.globl _AUTODAT1
	.globl _APTR1L
	.globl _APTR1H
	.globl _SBUF0
	.globl _SCON0
	.globl _MPAGE
	.globl _EXIF
	.globl _IOB
	.globl _CKCON
	.globl _TH1
	.globl _TH0
	.globl _TL1
	.globl _TL0
	.globl _TMOD
	.globl _TCON
	.globl _PCON
	.globl _DPS
	.globl _DPH1
	.globl _DPL1
	.globl _DPH
	.globl _DPL
	.globl _SP
	.globl _IOA
	.globl _hash1
	.globl _EP8FIFOBUF
	.globl _EP6FIFOBUF
	.globl _EP4FIFOBUF
	.globl _EP2FIFOBUF
	.globl _EP1INBUF
	.globl _EP1OUTBUF
	.globl _EP0BUF
	.globl _CT4
	.globl _CT3
	.globl _CT2
	.globl _CT1
	.globl _USBTEST
	.globl _TESTCFG
	.globl _DBUG
	.globl _UDMACRCQUAL
	.globl _UDMACRCL
	.globl _UDMACRCH
	.globl _GPIFHOLDAMOUNT
	.globl _FLOWSTBHPERIOD
	.globl _FLOWSTBEDGE
	.globl _FLOWSTB
	.globl _FLOWHOLDOFF
	.globl _FLOWEQ1CTL
	.globl _FLOWEQ0CTL
	.globl _FLOWLOGIC
	.globl _FLOWSTATE
	.globl _GPIFABORT
	.globl _GPIFREADYSTAT
	.globl _GPIFREADYCFG
	.globl _XGPIFSGLDATLNOX
	.globl _XGPIFSGLDATLX
	.globl _XGPIFSGLDATH
	.globl _EP8GPIFTRIG
	.globl _EP8GPIFPFSTOP
	.globl _EP8GPIFFLGSEL
	.globl _EP6GPIFTRIG
	.globl _EP6GPIFPFSTOP
	.globl _EP6GPIFFLGSEL
	.globl _EP4GPIFTRIG
	.globl _EP4GPIFPFSTOP
	.globl _EP4GPIFFLGSEL
	.globl _EP2GPIFTRIG
	.globl _EP2GPIFPFSTOP
	.globl _EP2GPIFFLGSEL
	.globl _GPIFTCB0
	.globl _GPIFTCB1
	.globl _GPIFTCB2
	.globl _GPIFTCB3
	.globl _GPIFADRL
	.globl _GPIFADRH
	.globl _GPIFCTLCFG
	.globl _GPIFIDLECTL
	.globl _GPIFIDLECS
	.globl _GPIFWFSELECT
	.globl _SETUPDAT
	.globl _SUDPTRCTL
	.globl _SUDPTRL
	.globl _SUDPTRH
	.globl _EP8FIFOBCL
	.globl _EP8FIFOBCH
	.globl _EP6FIFOBCL
	.globl _EP6FIFOBCH
	.globl _EP4FIFOBCL
	.globl _EP4FIFOBCH
	.globl _EP2FIFOBCL
	.globl _EP2FIFOBCH
	.globl _EP8FIFOFLGS
	.globl _EP6FIFOFLGS
	.globl _EP4FIFOFLGS
	.globl _EP2FIFOFLGS
	.globl _EP8CS
	.globl _EP6CS
	.globl _EP4CS
	.globl _EP2CS
	.globl _EP1INCS
	.globl _EP1OUTCS
	.globl _EP0CS
	.globl _EP8BCL
	.globl _EP8BCH
	.globl _EP6BCL
	.globl _EP6BCH
	.globl _EP4BCL
	.globl _EP4BCH
	.globl _EP2BCL
	.globl _EP2BCH
	.globl _EP1INBC
	.globl _EP1OUTBC
	.globl _EP0BCL
	.globl _EP0BCH
	.globl _FNADDR
	.globl _MICROFRAME
	.globl _USBFRAMEL
	.globl _USBFRAMEH
	.globl _TOGCTL
	.globl _WAKEUPCS
	.globl _SUSPEND
	.globl _USBCS
	.globl _XAUTODAT2
	.globl _XAUTODAT1
	.globl _I2CTL
	.globl _I2DAT
	.globl _I2CS
	.globl _PORTECFG
	.globl _PORTCCFG
	.globl _PORTACFG
	.globl _INTSETUP
	.globl _INT4IVEC
	.globl _INT2IVEC
	.globl _CLRERRCNT
	.globl _ERRCNTLIM
	.globl _USBERRIRQ
	.globl _USBERRIE
	.globl _GPIFIRQ
	.globl _GPIFIE
	.globl _EPIRQ
	.globl _EPIE
	.globl _USBIRQ
	.globl _USBIE
	.globl _NAKIRQ
	.globl _NAKIE
	.globl _IBNIRQ
	.globl _IBNIE
	.globl _EP8FIFOIRQ
	.globl _EP8FIFOIE
	.globl _EP6FIFOIRQ
	.globl _EP6FIFOIE
	.globl _EP4FIFOIRQ
	.globl _EP4FIFOIE
	.globl _EP2FIFOIRQ
	.globl _EP2FIFOIE
	.globl _OUTPKTEND
	.globl _INPKTEND
	.globl _EP8ISOINPKTS
	.globl _EP6ISOINPKTS
	.globl _EP4ISOINPKTS
	.globl _EP2ISOINPKTS
	.globl _EP8FIFOPFL
	.globl _EP8FIFOPFH
	.globl _EP6FIFOPFL
	.globl _EP6FIFOPFH
	.globl _EP4FIFOPFL
	.globl _EP4FIFOPFH
	.globl _EP2FIFOPFL
	.globl _EP2FIFOPFH
	.globl _EP8AUTOINLENL
	.globl _EP8AUTOINLENH
	.globl _EP6AUTOINLENL
	.globl _EP6AUTOINLENH
	.globl _EP4AUTOINLENL
	.globl _EP4AUTOINLENH
	.globl _EP2AUTOINLENL
	.globl _EP2AUTOINLENH
	.globl _EP8FIFOCFG
	.globl _EP6FIFOCFG
	.globl _EP4FIFOCFG
	.globl _EP2FIFOCFG
	.globl _EP8CFG
	.globl _EP6CFG
	.globl _EP4CFG
	.globl _EP2CFG
	.globl _EP1INCFG
	.globl _EP1OUTCFG
	.globl _REVCTL
	.globl _REVID
	.globl _FIFOPINPOLAR
	.globl _UART230
	.globl _BPADDRL
	.globl _BPADDRH
	.globl _BREAKPT
	.globl _FIFORESET
	.globl _PINFLAGSCD
	.globl _PINFLAGSAB
	.globl _IFCONFIG
	.globl _CPUCS
	.globl _RES_WAVEDATA_END
	.globl _GPIF_WAVE_DATA
	.globl _g_tx_underrun
	.globl _g_rx_overrun
	.globl _g_rx_enable
	.globl _g_tx_enable
	.globl _app_vendor_cmd
;--------------------------------------------------------
; special function registers
;--------------------------------------------------------
	.area RSEG    (DATA)
_IOA	=	0x0080
_SP	=	0x0081
_DPL	=	0x0082
_DPH	=	0x0083
_DPL1	=	0x0084
_DPH1	=	0x0085
_DPS	=	0x0086
_PCON	=	0x0087
_TCON	=	0x0088
_TMOD	=	0x0089
_TL0	=	0x008a
_TL1	=	0x008b
_TH0	=	0x008c
_TH1	=	0x008d
_CKCON	=	0x008e
_IOB	=	0x0090
_EXIF	=	0x0091
_MPAGE	=	0x0092
_SCON0	=	0x0098
_SBUF0	=	0x0099
_APTR1H	=	0x009a
_APTR1L	=	0x009b
_AUTODAT1	=	0x009c
_AUTOPTRH2	=	0x009d
_AUTOPTRL2	=	0x009e
_AUTODAT2	=	0x009f
_IOC	=	0x00a0
_INT2CLR	=	0x00a1
_INT4CLR	=	0x00a2
_IE	=	0x00a8
_EP2468STAT	=	0x00aa
_EP24FIFOFLGS	=	0x00ab
_EP68FIFOFLGS	=	0x00ac
_AUTOPTRSETUP	=	0x00af
_IOD	=	0x00b0
_IOE	=	0x00b1
_OEA	=	0x00b2
_OEB	=	0x00b3
_OEC	=	0x00b4
_OED	=	0x00b5
_OEE	=	0x00b6
_IP	=	0x00b8
_EP01STAT	=	0x00ba
_GPIFTRIG	=	0x00bb
_GPIFSGLDATH	=	0x00bd
_GPIFSGLDATLX	=	0x00be
_GPIFSGLDATLNOX	=	0x00bf
_SCON1	=	0x00c0
_SBUF1	=	0x00c1
_T2CON	=	0x00c8
_RCAP2L	=	0x00ca
_RCAP2H	=	0x00cb
_TL2	=	0x00cc
_TH2	=	0x00cd
_PSW	=	0x00d0
_EICON	=	0x00d8
_ACC	=	0x00e0
_EIE	=	0x00e8
_B	=	0x00f0
_EIP	=	0x00f8
;--------------------------------------------------------
; special function bits
;--------------------------------------------------------
	.area RSEG    (DATA)
_SEL	=	0x0086
_IT0	=	0x0088
_IE0	=	0x0089
_IT1	=	0x008a
_IE1	=	0x008b
_TR0	=	0x008c
_TF0	=	0x008d
_TR1	=	0x008e
_TF1	=	0x008f
_RI	=	0x0098
_TI	=	0x0099
_RB8	=	0x009a
_TB8	=	0x009b
_REN	=	0x009c
_SM2	=	0x009d
_SM1	=	0x009e
_SM0	=	0x009f
_EX0	=	0x00a8
_ET0	=	0x00a9
_EX1	=	0x00aa
_ET1	=	0x00ab
_ES0	=	0x00ac
_ET2	=	0x00ad
_ES1	=	0x00ae
_EA	=	0x00af
_PX0	=	0x00b8
_PT0	=	0x00b9
_PX1	=	0x00ba
_PT1	=	0x00bb
_PS0	=	0x00bc
_PT2	=	0x00bd
_PS1	=	0x00be
_RI1	=	0x00c0
_TI1	=	0x00c1
_RB81	=	0x00c2
_TB81	=	0x00c3
_REN1	=	0x00c4
_SM21	=	0x00c5
_SM11	=	0x00c6
_SM01	=	0x00c7
_CP_RL2	=	0x00c8
_C_T2	=	0x00c9
_TR2	=	0x00ca
_EXEN2	=	0x00cb
_TCLK	=	0x00cc
_RCLK	=	0x00cd
_EXF2	=	0x00ce
_TF2	=	0x00cf
_P	=	0x00d0
_FL	=	0x00d1
_OV	=	0x00d2
_RS0	=	0x00d3
_RS1	=	0x00d4
_F0	=	0x00d5
_AC	=	0x00d6
_CY	=	0x00d7
_INT6	=	0x00db
_RESI	=	0x00dc
_ERESI	=	0x00dd
_SMOD1	=	0x00df
_EIUSB	=	0x00e8
_EI2C	=	0x00e9
_EIEX4	=	0x00ea
_EIEX5	=	0x00eb
_EIEX6	=	0x00ec
_PUSB	=	0x00f8
_PI2C	=	0x00f9
_EIPX4	=	0x00fa
_EIPX5	=	0x00fb
_EIPX6	=	0x00fc
_bitS_CLK	=	0x0080
_bitS_OUT	=	0x0081
_bitS_IN	=	0x0082
_bitALTERA_DATA0	=	0x00a1
_bitALTERA_DCLK	=	0x00a3
;--------------------------------------------------------
; overlayable register banks
;--------------------------------------------------------
	.area REG_BANK_0	(REL,OVR,DATA)
	.ds 8
;--------------------------------------------------------
; internal ram data
;--------------------------------------------------------
	.area DSEG    (DATA)
_g_tx_enable::
	.ds 1
_g_rx_enable::
	.ds 1
_g_rx_overrun::
	.ds 1
_g_tx_underrun::
	.ds 1
_isr_tick_count_1_1:
	.ds 1
;--------------------------------------------------------
; overlayable items in internal ram 
;--------------------------------------------------------
	.area OSEG    (OVR,DATA)
;--------------------------------------------------------
; Stack segment in internal ram 
;--------------------------------------------------------
	.area	SSEG	(DATA)
__start__stack:
	.ds	1

;--------------------------------------------------------
; indirectly addressable internal ram data
;--------------------------------------------------------
	.area ISEG    (DATA)
;--------------------------------------------------------
; bit data
;--------------------------------------------------------
	.area BSEG    (BIT)
;--------------------------------------------------------
; paged external ram data
;--------------------------------------------------------
	.area PSEG    (PAG,XDATA)
;--------------------------------------------------------
; external ram data
;--------------------------------------------------------
	.area XSEG    (XDATA)
_GPIF_WAVE_DATA	=	0xe400
_RES_WAVEDATA_END	=	0xe480
_CPUCS	=	0xe600
_IFCONFIG	=	0xe601
_PINFLAGSAB	=	0xe602
_PINFLAGSCD	=	0xe603
_FIFORESET	=	0xe604
_BREAKPT	=	0xe605
_BPADDRH	=	0xe606
_BPADDRL	=	0xe607
_UART230	=	0xe608
_FIFOPINPOLAR	=	0xe609
_REVID	=	0xe60a
_REVCTL	=	0xe60b
_EP1OUTCFG	=	0xe610
_EP1INCFG	=	0xe611
_EP2CFG	=	0xe612
_EP4CFG	=	0xe613
_EP6CFG	=	0xe614
_EP8CFG	=	0xe615
_EP2FIFOCFG	=	0xe618
_EP4FIFOCFG	=	0xe619
_EP6FIFOCFG	=	0xe61a
_EP8FIFOCFG	=	0xe61b
_EP2AUTOINLENH	=	0xe620
_EP2AUTOINLENL	=	0xe621
_EP4AUTOINLENH	=	0xe622
_EP4AUTOINLENL	=	0xe623
_EP6AUTOINLENH	=	0xe624
_EP6AUTOINLENL	=	0xe625
_EP8AUTOINLENH	=	0xe626
_EP8AUTOINLENL	=	0xe627
_EP2FIFOPFH	=	0xe630
_EP2FIFOPFL	=	0xe631
_EP4FIFOPFH	=	0xe632
_EP4FIFOPFL	=	0xe633
_EP6FIFOPFH	=	0xe634
_EP6FIFOPFL	=	0xe635
_EP8FIFOPFH	=	0xe636
_EP8FIFOPFL	=	0xe637
_EP2ISOINPKTS	=	0xe640
_EP4ISOINPKTS	=	0xe641
_EP6ISOINPKTS	=	0xe642
_EP8ISOINPKTS	=	0xe643
_INPKTEND	=	0xe648
_OUTPKTEND	=	0xe649
_EP2FIFOIE	=	0xe650
_EP2FIFOIRQ	=	0xe651
_EP4FIFOIE	=	0xe652
_EP4FIFOIRQ	=	0xe653
_EP6FIFOIE	=	0xe654
_EP6FIFOIRQ	=	0xe655
_EP8FIFOIE	=	0xe656
_EP8FIFOIRQ	=	0xe657
_IBNIE	=	0xe658
_IBNIRQ	=	0xe659
_NAKIE	=	0xe65a
_NAKIRQ	=	0xe65b
_USBIE	=	0xe65c
_USBIRQ	=	0xe65d
_EPIE	=	0xe65e
_EPIRQ	=	0xe65f
_GPIFIE	=	0xe660
_GPIFIRQ	=	0xe661
_USBERRIE	=	0xe662
_USBERRIRQ	=	0xe663
_ERRCNTLIM	=	0xe664
_CLRERRCNT	=	0xe665
_INT2IVEC	=	0xe666
_INT4IVEC	=	0xe667
_INTSETUP	=	0xe668
_PORTACFG	=	0xe670
_PORTCCFG	=	0xe671
_PORTECFG	=	0xe672
_I2CS	=	0xe678
_I2DAT	=	0xe679
_I2CTL	=	0xe67a
_XAUTODAT1	=	0xe67b
_XAUTODAT2	=	0xe67c
_USBCS	=	0xe680
_SUSPEND	=	0xe681
_WAKEUPCS	=	0xe682
_TOGCTL	=	0xe683
_USBFRAMEH	=	0xe684
_USBFRAMEL	=	0xe685
_MICROFRAME	=	0xe686
_FNADDR	=	0xe687
_EP0BCH	=	0xe68a
_EP0BCL	=	0xe68b
_EP1OUTBC	=	0xe68d
_EP1INBC	=	0xe68f
_EP2BCH	=	0xe690
_EP2BCL	=	0xe691
_EP4BCH	=	0xe694
_EP4BCL	=	0xe695
_EP6BCH	=	0xe698
_EP6BCL	=	0xe699
_EP8BCH	=	0xe69c
_EP8BCL	=	0xe69d
_EP0CS	=	0xe6a0
_EP1OUTCS	=	0xe6a1
_EP1INCS	=	0xe6a2
_EP2CS	=	0xe6a3
_EP4CS	=	0xe6a4
_EP6CS	=	0xe6a5
_EP8CS	=	0xe6a6
_EP2FIFOFLGS	=	0xe6a7
_EP4FIFOFLGS	=	0xe6a8
_EP6FIFOFLGS	=	0xe6a9
_EP8FIFOFLGS	=	0xe6aa
_EP2FIFOBCH	=	0xe6ab
_EP2FIFOBCL	=	0xe6ac
_EP4FIFOBCH	=	0xe6ad
_EP4FIFOBCL	=	0xe6ae
_EP6FIFOBCH	=	0xe6af
_EP6FIFOBCL	=	0xe6b0
_EP8FIFOBCH	=	0xe6b1
_EP8FIFOBCL	=	0xe6b2
_SUDPTRH	=	0xe6b3
_SUDPTRL	=	0xe6b4
_SUDPTRCTL	=	0xe6b5
_SETUPDAT	=	0xe6b8
_GPIFWFSELECT	=	0xe6c0
_GPIFIDLECS	=	0xe6c1
_GPIFIDLECTL	=	0xe6c2
_GPIFCTLCFG	=	0xe6c3
_GPIFADRH	=	0xe6c4
_GPIFADRL	=	0xe6c5
_GPIFTCB3	=	0xe6ce
_GPIFTCB2	=	0xe6cf
_GPIFTCB1	=	0xe6d0
_GPIFTCB0	=	0xe6d1
_EP2GPIFFLGSEL	=	0xe6d2
_EP2GPIFPFSTOP	=	0xe6d3
_EP2GPIFTRIG	=	0xe6d4
_EP4GPIFFLGSEL	=	0xe6da
_EP4GPIFPFSTOP	=	0xe6db
_EP4GPIFTRIG	=	0xe6dc
_EP6GPIFFLGSEL	=	0xe6e2
_EP6GPIFPFSTOP	=	0xe6e3
_EP6GPIFTRIG	=	0xe6e4
_EP8GPIFFLGSEL	=	0xe6ea
_EP8GPIFPFSTOP	=	0xe6eb
_EP8GPIFTRIG	=	0xe6ec
_XGPIFSGLDATH	=	0xe6f0
_XGPIFSGLDATLX	=	0xe6f1
_XGPIFSGLDATLNOX	=	0xe6f2
_GPIFREADYCFG	=	0xe6f3
_GPIFREADYSTAT	=	0xe6f4
_GPIFABORT	=	0xe6f5
_FLOWSTATE	=	0xe6c6
_FLOWLOGIC	=	0xe6c7
_FLOWEQ0CTL	=	0xe6c8
_FLOWEQ1CTL	=	0xe6c9
_FLOWHOLDOFF	=	0xe6ca
_FLOWSTB	=	0xe6cb
_FLOWSTBEDGE	=	0xe6cc
_FLOWSTBHPERIOD	=	0xe6cd
_GPIFHOLDAMOUNT	=	0xe60c
_UDMACRCH	=	0xe67d
_UDMACRCL	=	0xe67e
_UDMACRCQUAL	=	0xe67f
_DBUG	=	0xe6f8
_TESTCFG	=	0xe6f9
_USBTEST	=	0xe6fa
_CT1	=	0xe6fb
_CT2	=	0xe6fc
_CT3	=	0xe6fd
_CT4	=	0xe6fe
_EP0BUF	=	0xe740
_EP1OUTBUF	=	0xe780
_EP1INBUF	=	0xe7c0
_EP2FIFOBUF	=	0xf000
_EP4FIFOBUF	=	0xf400
_EP6FIFOBUF	=	0xf800
_EP8FIFOBUF	=	0xfc00
_hash1	=	0xe1f0
_patch_usb_descriptors_hw_rev_1_1:
	.ds 1
_patch_usb_descriptors_serial_no_1_1:
	.ds 8
;--------------------------------------------------------
; external initialized ram data
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT0 (CODE)
	.area GSINIT1 (CODE)
	.area GSINIT2 (CODE)
	.area GSINIT3 (CODE)
	.area GSINIT4 (CODE)
	.area GSINIT5 (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area CSEG    (CODE)
;--------------------------------------------------------
; interrupt vector 
;--------------------------------------------------------
	.area HOME    (CODE)
__interrupt_vect:
	ljmp	__sdcc_gsinit_startup
;--------------------------------------------------------
; global & static initialisations
;--------------------------------------------------------
	.area HOME    (CODE)
	.area GSINIT  (CODE)
	.area GSFINAL (CODE)
	.area GSINIT  (CODE)
	.globl __sdcc_gsinit_startup
	.globl __sdcc_program_startup
	.globl __start__stack
	.globl __mcs51_genRAMCLEAR
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_tick'
;------------------------------------------------------------
;count                     Allocated with name '_isr_tick_count_1_1'
;------------------------------------------------------------
;	usrp_main.c:309: static unsigned char	count = 1;
;	genAssign
	mov	_isr_tick_count_1_1,#0x01
;	usrp_main.c:55: unsigned char g_tx_enable = 0;
;	genAssign
	mov	_g_tx_enable,#0x00
;	usrp_main.c:56: unsigned char g_rx_enable = 0;
;	genAssign
	mov	_g_rx_enable,#0x00
;	usrp_main.c:57: unsigned char g_rx_overrun = 0;
;	genAssign
	mov	_g_rx_overrun,#0x00
;	usrp_main.c:58: unsigned char g_tx_underrun = 0;
;	genAssign
	mov	_g_tx_underrun,#0x00
	.area GSFINAL (CODE)
	ljmp	__sdcc_program_startup
;--------------------------------------------------------
; Home
;--------------------------------------------------------
	.area HOME    (CODE)
	.area CSEG    (CODE)
__sdcc_program_startup:
	lcall	_main
;	return from main will lock up
	sjmp .
;--------------------------------------------------------
; code
;--------------------------------------------------------
	.area CSEG    (CODE)
;------------------------------------------------------------
;Allocation info for local variables in function 'get_ep0_data'
;------------------------------------------------------------
;------------------------------------------------------------
;	usrp_main.c:68: get_ep0_data (void)
;	-----------------------------------------
;	 function get_ep0_data
;	-----------------------------------------
_get_ep0_data:
	ar2 = 0x02
	ar3 = 0x03
	ar4 = 0x04
	ar5 = 0x05
	ar6 = 0x06
	ar7 = 0x07
	ar0 = 0x00
	ar1 = 0x01
;	usrp_main.c:70: EP0BCL = 0;			// arm EP0 for OUT xfer.  This sets the busy bit
;	genAssign
	mov	dptr,#_EP0BCL
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:72: while (EP0CS & bmEPBUSY)	// wait for busy to clear
00101$:
;	genAssign
	mov	dptr,#_EP0CS
	movx	a,@dptr
;	genAnd
	mov	r2,a
;	Peephole 105	removed redundant mov
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	acc.1,00101$
;	Peephole 300	removed redundant label 00107$
;	Peephole 300	removed redundant label 00104$
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'app_vendor_cmd'
;------------------------------------------------------------
;------------------------------------------------------------
;	usrp_main.c:81: app_vendor_cmd (void)
;	-----------------------------------------
;	 function app_vendor_cmd
;	-----------------------------------------
_app_vendor_cmd:
;	usrp_main.c:83: if (bRequestType == VRT_VENDOR_IN){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_SETUPDAT
	movx	a,@dptr
	mov	r2,a
;	genCmpEq
;	gencjneshort
	cjne	r2,#0xC0,00163$
	sjmp	00164$
00163$:
	ljmp	00142$
00164$:
;	usrp_main.c:89: switch (bRequest){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0001)
	movx	a,@dptr
	mov	r2,a
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x80,00165$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00101$
00165$:
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x81,00166$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00106$
00166$:
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x82,00167$
	ljmp	00109$
00167$:
	ljmp	00112$
;	usrp_main.c:91: case VRQ_GET_STATUS:
00101$:
;	usrp_main.c:92: switch (wIndexL){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0004)
	movx	a,@dptr
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	mov	r2,a
;	Peephole 115.b	jump optimization
	jz	00102$
;	Peephole 300	removed redundant label 00168$
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	usrp_main.c:94: case GS_TX_UNDERRUN:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x01,00104$
	sjmp	00103$
;	Peephole 300	removed redundant label 00169$
00102$:
;	usrp_main.c:95: EP0BUF[0] = g_tx_underrun;
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_EP0BUF
	mov	a,_g_tx_underrun
	movx	@dptr,a
;	usrp_main.c:96: g_tx_underrun = 0;
;	genAssign
	mov	_g_tx_underrun,#0x00
;	usrp_main.c:97: EP0BCH = 0;
;	genAssign
	mov	dptr,#_EP0BCH
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:98: EP0BCL = 1;
;	genAssign
	mov	dptr,#_EP0BCL
	mov	a,#0x01
	movx	@dptr,a
;	usrp_main.c:99: break;
	ljmp	00143$
;	usrp_main.c:101: case GS_RX_OVERRUN:
00103$:
;	usrp_main.c:102: EP0BUF[0] = g_rx_overrun;
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_EP0BUF
	mov	a,_g_rx_overrun
	movx	@dptr,a
;	usrp_main.c:103: g_rx_overrun = 0;
;	genAssign
	mov	_g_rx_overrun,#0x00
;	usrp_main.c:104: EP0BCH = 0;
;	genAssign
	mov	dptr,#_EP0BCH
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:105: EP0BCL = 1;
;	genAssign
	mov	dptr,#_EP0BCL
	mov	a,#0x01
	movx	@dptr,a
;	usrp_main.c:106: break;
	ljmp	00143$
;	usrp_main.c:108: default:
00104$:
;	usrp_main.c:109: return 0;
;	genRet
	mov	dpl,#0x00
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
;	usrp_main.c:113: case VRQ_I2C_READ:
00106$:
;	usrp_main.c:114: if (!i2c_read (wValueL, EP0BUF, wLengthL))
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
	mov	r2,a
;	genAddrOf
	mov	_i2c_read_PARM_2,#_EP0BUF
	mov	(_i2c_read_PARM_2 + 1),#(_EP0BUF >> 8)
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0006)
	movx	a,@dptr
	mov	_i2c_read_PARM_3,a
;	genCall
	mov	dpl,r2
	lcall	_i2c_read
	mov	a,dpl
;	genIfx
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
;	usrp_main.c:115: return 0;
;	genRet
	jnz	00108$
;	Peephole 300	removed redundant label 00170$
;	Peephole 256.c	loading dpl with zero from a
	mov	dpl,a
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00108$:
;	usrp_main.c:117: EP0BCH = 0;
;	genAssign
	mov	dptr,#_EP0BCH
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:118: EP0BCL = wLengthL;
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0006)
	movx	a,@dptr
;	genAssign
	mov	r2,a
	mov	dptr,#_EP0BCL
;	Peephole 100	removed redundant mov
	movx	@dptr,a
;	usrp_main.c:119: break;
	ljmp	00143$
;	usrp_main.c:121: case VRQ_SPI_READ:
00109$:
;	usrp_main.c:122: if (!spi_read (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, wLengthL))
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0003)
	movx	a,@dptr
	mov	r2,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
	mov	_spi_read_PARM_2,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0005)
	movx	a,@dptr
	mov	_spi_read_PARM_3,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0004)
	movx	a,@dptr
	mov	_spi_read_PARM_4,a
;	genAddrOf
	mov	_spi_read_PARM_5,#_EP0BUF
	mov	(_spi_read_PARM_5 + 1),#(_EP0BUF >> 8)
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0006)
	movx	a,@dptr
	mov	_spi_read_PARM_6,a
;	genCall
	mov	dpl,r2
	lcall	_spi_read
	mov	a,dpl
;	genIfx
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
;	usrp_main.c:123: return 0;
;	genRet
	jnz	00111$
;	Peephole 300	removed redundant label 00171$
;	Peephole 256.c	loading dpl with zero from a
	mov	dpl,a
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
00111$:
;	usrp_main.c:125: EP0BCH = 0;
;	genAssign
	mov	dptr,#_EP0BCH
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:126: EP0BCL = wLengthL;
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0006)
	movx	a,@dptr
;	genAssign
	mov	r2,a
	mov	dptr,#_EP0BCL
;	Peephole 100	removed redundant mov
	movx	@dptr,a
;	usrp_main.c:127: break;
	ljmp	00143$
;	usrp_main.c:129: default:
00112$:
;	usrp_main.c:130: return 0;
;	genRet
	mov	dpl,#0x00
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
;	usrp_main.c:131: }
00142$:
;	usrp_main.c:134: else if (bRequestType == VRT_VENDOR_OUT){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#_SETUPDAT
	movx	a,@dptr
	mov	r2,a
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x40,00172$
	sjmp	00173$
00172$:
	ljmp	00139$
00173$:
;	usrp_main.c:140: switch (bRequest){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0001)
	movx	a,@dptr
;	genCmpGt
;	genCmp
;	genIfxJump
;	Peephole 132.b	optimized genCmpGt by inverse logic (acc differs)
	mov  r2,a
;	Peephole 177.a	removed redundant mov
	add	a,#0xff - 0x0B
	jnc	00174$
	ljmp	00136$
00174$:
;	genJumpTab
	mov	a,r2
;	Peephole 254	optimized left shift
	add	a,r2
	add	a,r2
	mov	dptr,#00175$
	jmp	@a+dptr
00175$:
	ljmp	00136$
	ljmp	00114$
	ljmp	00119$
	ljmp	00136$
	ljmp	00125$
	ljmp	00126$
	ljmp	00127$
	ljmp	00136$
	ljmp	00130$
	ljmp	00133$
	ljmp	00128$
	ljmp	00129$
;	usrp_main.c:142: case VRQ_SET_LED:
00114$:
;	usrp_main.c:143: switch (wIndexL){
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0004)
	movx	a,@dptr
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	mov	r2,a
;	Peephole 115.b	jump optimization
	jz	00115$
;	Peephole 300	removed redundant label 00176$
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	usrp_main.c:144: case 0:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x01,00117$
	sjmp	00116$
;	Peephole 300	removed redundant label 00177$
00115$:
;	usrp_main.c:145: set_led_0 (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_set_led_0
;	usrp_main.c:146: break;
	ljmp	00143$
;	usrp_main.c:148: case 1:
00116$:
;	usrp_main.c:149: set_led_1 (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_set_led_1
;	usrp_main.c:150: break;
	ljmp	00143$
;	usrp_main.c:152: default:
00117$:
;	usrp_main.c:153: return 0;
;	genRet
	mov	dpl,#0x00
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
;	usrp_main.c:157: case VRQ_FPGA_LOAD:
00119$:
;	usrp_main.c:158: switch (wIndexL){			// sub-command
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0004)
	movx	a,@dptr
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
	mov	r2,a
;	Peephole 115.b	jump optimization
	jz	00120$
;	Peephole 300	removed redundant label 00178$
;	genCmpEq
;	gencjneshort
	cjne	r2,#0x01,00179$
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00121$
00179$:
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	usrp_main.c:159: case FL_BEGIN:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r2,#0x02,00123$
	sjmp	00122$
;	Peephole 300	removed redundant label 00180$
00120$:
;	usrp_main.c:160: return fpga_load_begin ();
;	genCall
;	genRet
;	Peephole 251.a	replaced ljmp to ret with ret
;	Peephole 253.a	replaced lcall/ret with ljmp
	ljmp	_fpga_load_begin
;	usrp_main.c:162: case FL_XFER:
00121$:
;	usrp_main.c:163: get_ep0_data ();
;	genCall
	lcall	_get_ep0_data
;	usrp_main.c:164: return fpga_load_xfer (EP0BUF, EP0BCL);
;	genAssign
	mov	dptr,#_EP0BCL
	movx	a,@dptr
	mov	_fpga_load_xfer_PARM_2,a
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_EP0BUF
;	genRet
;	Peephole 251.a	replaced ljmp to ret with ret
;	Peephole 253.a	replaced lcall/ret with ljmp
	ljmp	_fpga_load_xfer
;	usrp_main.c:166: case FL_END:
00122$:
;	usrp_main.c:167: return fpga_load_end ();
;	genCall
;	genRet
;	Peephole 251.a	replaced ljmp to ret with ret
;	Peephole 253.a	replaced lcall/ret with ljmp
	ljmp	_fpga_load_end
;	usrp_main.c:169: default:
00123$:
;	usrp_main.c:170: return 0;
;	genRet
	mov	dpl,#0x00
;	Peephole 251.a	replaced ljmp to ret with ret
	ret
;	usrp_main.c:175: case VRQ_FPGA_SET_RESET:
00125$:
;	usrp_main.c:176: fpga_set_reset (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_fpga_set_reset
;	usrp_main.c:177: break;
	ljmp	00143$
;	usrp_main.c:179: case VRQ_FPGA_SET_TX_ENABLE:
00126$:
;	usrp_main.c:180: fpga_set_tx_enable (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_fpga_set_tx_enable
;	usrp_main.c:181: break;
	ljmp	00143$
;	usrp_main.c:183: case VRQ_FPGA_SET_RX_ENABLE:
00127$:
;	usrp_main.c:184: fpga_set_rx_enable (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_fpga_set_rx_enable
;	usrp_main.c:185: break;
	ljmp	00143$
;	usrp_main.c:187: case VRQ_FPGA_SET_TX_RESET:
00128$:
;	usrp_main.c:188: fpga_set_tx_reset (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_fpga_set_tx_reset
;	usrp_main.c:189: break;
;	usrp_main.c:191: case VRQ_FPGA_SET_RX_RESET:
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00143$
00129$:
;	usrp_main.c:192: fpga_set_rx_reset (wValueL);
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
;	genCall
	mov	r2,a
;	Peephole 244.c	loading dpl from a instead of r2
	mov	dpl,a
	lcall	_fpga_set_rx_reset
;	usrp_main.c:193: break;
;	usrp_main.c:195: case VRQ_I2C_WRITE:
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00143$
00130$:
;	usrp_main.c:196: get_ep0_data ();
;	genCall
	lcall	_get_ep0_data
;	usrp_main.c:197: if (!i2c_write (wValueL, EP0BUF, EP0BCL))
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
	mov	r2,a
;	genAddrOf
	mov	_i2c_write_PARM_2,#_EP0BUF
	mov	(_i2c_write_PARM_2 + 1),#(_EP0BUF >> 8)
;	genAssign
	mov	dptr,#_EP0BCL
	movx	a,@dptr
	mov	_i2c_write_PARM_3,a
;	genCall
	mov	dpl,r2
	lcall	_i2c_write
	mov	a,dpl
;	genIfx
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
;	usrp_main.c:198: return 0;
;	genRet
	jnz	00143$
;	Peephole 300	removed redundant label 00181$
;	Peephole 256.c	loading dpl with zero from a
	mov	dpl,a
;	usrp_main.c:201: case VRQ_SPI_WRITE:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00133$:
;	usrp_main.c:202: get_ep0_data ();
;	genCall
	lcall	_get_ep0_data
;	usrp_main.c:203: if (!spi_write (wValueH, wValueL, wIndexH, wIndexL, EP0BUF, EP0BCL))
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0003)
	movx	a,@dptr
	mov	r2,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0002)
	movx	a,@dptr
	mov	_spi_write_PARM_2,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0005)
	movx	a,@dptr
	mov	_spi_write_PARM_3,a
;	genPointerGet
;	genFarPointerGet
	mov	dptr,#(_SETUPDAT + 0x0004)
	movx	a,@dptr
	mov	_spi_write_PARM_4,a
;	genAddrOf
	mov	_spi_write_PARM_5,#_EP0BUF
	mov	(_spi_write_PARM_5 + 1),#(_EP0BUF >> 8)
;	genAssign
	mov	dptr,#_EP0BCL
	movx	a,@dptr
	mov	_spi_write_PARM_6,a
;	genCall
	mov	dpl,r2
	lcall	_spi_write
	mov	a,dpl
;	genIfx
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
;	usrp_main.c:204: return 0;
;	genRet
	jnz	00143$
;	Peephole 300	removed redundant label 00182$
;	Peephole 256.c	loading dpl with zero from a
	mov	dpl,a
;	usrp_main.c:207: default:
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00136$:
;	usrp_main.c:208: return 0;
;	genRet
	mov	dpl,#0x00
;	usrp_main.c:209: }
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 251.b	replaced sjmp to ret with ret
	ret
00139$:
;	usrp_main.c:213: return 0;    // invalid bRequestType
;	genRet
	mov	dpl,#0x00
;	Peephole 112.b	changed ljmp to sjmp
;	usrp_main.c:215: return 1;
;	genRet
;	Peephole 237.a	removed sjmp to ret
	ret
00143$:
	mov	dpl,#0x01
;	Peephole 300	removed redundant label 00144$
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main_loop'
;------------------------------------------------------------
;------------------------------------------------------------
;	usrp_main.c:221: main_loop (void)
;	-----------------------------------------
;	 function main_loop
;	-----------------------------------------
_main_loop:
;	usrp_main.c:223: setup_flowstate_common ();
;	genAssign
	mov	dptr,#_FLOWSTATE
	mov	a,#0x81
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWLOGIC
	mov	a,#0x2D
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWEQ0CTL
	mov	a,#0x26
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWEQ1CTL
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWHOLDOFF
	mov	a,#0x04
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWSTB
	mov	a,#0x04
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWSTBEDGE
	mov	a,#0x03
	movx	@dptr,a
;	genAssign
	mov	dptr,#_FLOWSTBHPERIOD
	mov	a,#0x02
	movx	@dptr,a
;	genAssign
	mov	dptr,#_GPIFHOLDAMOUNT
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	usrp_main.c:225: while (1){
00141$:
;	usrp_main.c:227: if (usb_setup_packet_avail ())
;	genIfx
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	__usb_got_SUDAV,00105$
;	Peephole 300	removed redundant label 00160$
;	usrp_main.c:228: usb_handle_setup_packet ();
;	genCall
	lcall	_usb_handle_setup_packet
00105$:
;	usrp_main.c:231: if (GPIFTRIG & bmGPIF_IDLE){
;	genAnd
	mov	a,_GPIFTRIG
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.7,00141$
;	Peephole 300	removed redundant label 00161$
;	usrp_main.c:237: if (UC_BOARD_HAS_FPGA && (USRP_PA & (bmPA_TX_UNDERRUN | bmPA_RX_OVERRUN))){
;	genAnd
	mov	a,_IOA
	anl	a,#0xC0
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00114$
;	Peephole 300	removed redundant label 00162$
;	usrp_main.c:240: if (USRP_PA & bmPA_TX_UNDERRUN)
;	genAnd
	mov	a,_IOA
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.7,00107$
;	Peephole 300	removed redundant label 00163$
;	usrp_main.c:241: g_tx_underrun = 1;
;	genAssign
	mov	_g_tx_underrun,#0x01
00107$:
;	usrp_main.c:243: if (USRP_PA & bmPA_RX_OVERRUN)
;	genAnd
	mov	a,_IOA
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.6,00110$
;	Peephole 300	removed redundant label 00164$
;	usrp_main.c:244: g_rx_overrun = 1;
;	genAssign
	mov	_g_rx_overrun,#0x01
;	usrp_main.c:247: fpga_clear_flags ();
00110$:
;	genOr
	orl	_IOE,#0x08
;	genAnd
	anl	_IOE,#0xF7
00114$:
;	usrp_main.c:253: if (g_tx_enable && !(EP24FIFOFLGS & 0x02)){  // USB end point fifo is not empty...
;	genIfx
	mov	a,_g_tx_enable
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00125$
;	Peephole 300	removed redundant label 00165$
;	genAnd
	mov	a,_EP24FIFOFLGS
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	acc.1,00125$
;	Peephole 300	removed redundant label 00166$
;	usrp_main.c:255: if (fpga_has_room_for_packet ()){	   // ... and FPGA has room for packet
;	genAssign
	mov	dptr,#_GPIFREADYSTAT
	movx	a,@dptr
;	genAnd
	mov	r2,a
;	Peephole 105	removed redundant mov
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.0,00125$
;	Peephole 300	removed redundant label 00167$
;	usrp_main.c:257: GPIFTCB1 = 0x01;	SYNCDELAY;
;	genAssign
	mov	dptr,#_GPIFTCB1
	mov	a,#0x01
	movx	@dptr,a
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:258: GPIFTCB0 = 0x00;	SYNCDELAY;
;	genAssign
	mov	dptr,#_GPIFTCB0
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:260: setup_flowstate_write ();
;	genAssign
	mov	dptr,#_FLOWEQ0CTL
	mov	a,#0x21
	movx	@dptr,a
;	usrp_main.c:262: SYNCDELAY;
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:263: GPIFTRIG = bmGPIF_EP2_START | bmGPIF_WRITE; 	// start the xfer
;	genAssign
	mov	_GPIFTRIG,#0x00
;	usrp_main.c:264: SYNCDELAY;
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:266: while (!(GPIFTRIG & bmGPIF_IDLE)){
00119$:
;	genAnd
	mov	a,_GPIFTRIG
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.7,00119$
;	Peephole 300	removed redundant label 00168$
00125$:
;	usrp_main.c:275: if (g_rx_enable && !(EP6CS & bmEPFULL)){	// USB end point fifo is not full...
;	genIfx
	mov	a,_g_rx_enable
;	genIfxJump
;	Peephole 108.c	removed ljmp by inverse jump logic
	jz	00141$
;	Peephole 300	removed redundant label 00169$
;	genAssign
	mov	dptr,#_EP6CS
	movx	a,@dptr
;	genAnd
	mov	r2,a
;	Peephole 105	removed redundant mov
;	genIfxJump
;	Peephole 108.e	removed ljmp by inverse jump logic
	jb	acc.3,00141$
;	Peephole 300	removed redundant label 00170$
;	usrp_main.c:277: if (fpga_has_packet_avail ()){		// ... and FPGA has packet available
;	genAssign
	mov	dptr,#_GPIFREADYSTAT
	movx	a,@dptr
;	genAnd
	mov	r2,a
;	Peephole 105	removed redundant mov
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.1,00141$
;	Peephole 300	removed redundant label 00171$
;	usrp_main.c:279: GPIFTCB1 = 0x01;	SYNCDELAY;
;	genAssign
	mov	dptr,#_GPIFTCB1
	mov	a,#0x01
	movx	@dptr,a
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:280: GPIFTCB0 = 0x00;	SYNCDELAY;
;	genAssign
	mov	dptr,#_GPIFTCB0
;	Peephole 181	changed mov to clr
	clr	a
	movx	@dptr,a
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:282: setup_flowstate_read ();
;	genAssign
	mov	dptr,#_FLOWEQ0CTL
	mov	a,#0x26
	movx	@dptr,a
;	usrp_main.c:284: SYNCDELAY;
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:285: GPIFTRIG = bmGPIF_EP6_START | bmGPIF_READ; 	// start the xfer
;	genAssign
	mov	_GPIFTRIG,#0x06
;	usrp_main.c:286: SYNCDELAY;
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:288: while (!(GPIFTRIG & bmGPIF_IDLE)){
00130$:
;	genAnd
	mov	a,_GPIFTRIG
;	genIfxJump
;	Peephole 108.d	removed ljmp by inverse jump logic
	jnb	acc.7,00130$
;	Peephole 300	removed redundant label 00172$
;	usrp_main.c:292: SYNCDELAY;
;	genInline
	 nop; nop; nop; 
;	usrp_main.c:293: INPKTEND = 6;	// tell USB we filled buffer (6 is our endpoint num)
;	genAssign
	mov	dptr,#_INPKTEND
	mov	a,#0x06
	movx	@dptr,a
	ljmp	00141$
;	Peephole 259.b	removed redundant label 00143$ and ret
;
;------------------------------------------------------------
;Allocation info for local variables in function 'isr_tick'
;------------------------------------------------------------
;count                     Allocated with name '_isr_tick_count_1_1'
;------------------------------------------------------------
;	usrp_main.c:307: isr_tick (void) interrupt
;	-----------------------------------------
;	 function isr_tick
;	-----------------------------------------
_isr_tick:
	push	acc
;	usrp_main.c:311: if (--count == 0){
;	genMinus
;	genMinusDec
	dec	_isr_tick_count_1_1
;	genIfx
	mov	a,_isr_tick_count_1_1
;	genIfxJump
;	Peephole 108.b	removed ljmp by inverse jump logic
	jnz	00102$
;	Peephole 300	removed redundant label 00106$
;	usrp_main.c:312: count = 50;
;	genAssign
	mov	_isr_tick_count_1_1,#0x32
;	usrp_main.c:313: USRP_LED_REG ^= bmLED0;
;	genXor
	xrl	_IOC,#0x40
00102$:
;	usrp_main.c:316: clear_timer_irq ();
;	genAssign
	clr	_TF2
;	Peephole 300	removed redundant label 00103$
	pop	acc
	reti
;	eliminated unneeded push/pop psw
;	eliminated unneeded push/pop dpl
;	eliminated unneeded push/pop dph
;	eliminated unneeded push/pop b
;------------------------------------------------------------
;Allocation info for local variables in function 'patch_usb_descriptors'
;------------------------------------------------------------
;i                         Allocated to registers r2 
;ch                        Allocated to registers r3 
;hw_rev                    Allocated with name '_patch_usb_descriptors_hw_rev_1_1'
;serial_no                 Allocated with name '_patch_usb_descriptors_serial_no_1_1'
;------------------------------------------------------------
;	usrp_main.c:324: patch_usb_descriptors(void)
;	-----------------------------------------
;	 function patch_usb_descriptors
;	-----------------------------------------
_patch_usb_descriptors:
;	usrp_main.c:330: eeprom_read(I2C_ADDR_BOOT, HW_REV_OFFSET, &hw_rev, 1);	// LSB of device id
;	genAddrOf
	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_hw_rev_1_1
	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_hw_rev_1_1 >> 8)
;	genAssign
	mov	_eeprom_read_PARM_2,#0x05
;	genAssign
	mov	_eeprom_read_PARM_4,#0x01
;	genCall
	mov	dpl,#0x50
	lcall	_eeprom_read
;	usrp_main.c:331: usb_desc_hw_rev_binary_patch_location_0[0] = hw_rev;
;	genAssign
	mov	dptr,#_patch_usb_descriptors_hw_rev_1_1
	movx	a,@dptr
;	genPointerSet
;     genFarPointerSet
	mov	r2,a
	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_0
;	Peephole 100	removed redundant mov
	movx	@dptr,a
;	usrp_main.c:332: usb_desc_hw_rev_binary_patch_location_1[0] = hw_rev;
;	genPointerSet
;     genFarPointerSet
	mov	dptr,#_usb_desc_hw_rev_binary_patch_location_1
	mov	a,r2
	movx	@dptr,a
;	usrp_main.c:333: usb_desc_hw_rev_ascii_patch_location_0[0] = hw_rev + '0';     // FIXME if we get > 9
;	genPlus
;     genPlusIncr
	mov	a,#0x30
;	Peephole 236.a	used r2 instead of ar2
	add	a,r2
;	genPointerSet
;     genFarPointerSet
	mov	r2,a
	mov	dptr,#_usb_desc_hw_rev_ascii_patch_location_0
;	Peephole 100	removed redundant mov
	movx	@dptr,a
;	usrp_main.c:335: eeprom_read(I2C_ADDR_BOOT, SERIAL_NO_OFFSET, serial_no, SERIAL_NO_LEN);
;	genAddrOf
	mov	_eeprom_read_PARM_3,#_patch_usb_descriptors_serial_no_1_1
	mov	(_eeprom_read_PARM_3 + 1),#(_patch_usb_descriptors_serial_no_1_1 >> 8)
;	genAssign
	mov	_eeprom_read_PARM_2,#0xF8
;	genAssign
	mov	_eeprom_read_PARM_4,#0x08
;	genCall
	mov	dpl,#0x50
	lcall	_eeprom_read
;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
;	genAssign
	mov	r2,#0x00
00103$:
;	genCmpLt
;	genCmp
	cjne	r2,#0x08,00113$
00113$:
;	genIfxJump
;	Peephole 108.a	removed ljmp by inverse jump logic
	jnc	00107$
;	Peephole 300	removed redundant label 00114$
;	usrp_main.c:338: unsigned char ch = serial_no[i];
;	genPlus
;	Peephole 236.g	used r2 instead of ar2
	mov	a,r2
	add	a,#_patch_usb_descriptors_serial_no_1_1
	mov	dpl,a
;	Peephole 181	changed mov to clr
	clr	a
	addc	a,#(_patch_usb_descriptors_serial_no_1_1 >> 8)
	mov	dph,a
;	genPointerGet
;	genFarPointerGet
	movx	a,@dptr
	mov	r3,a
;	usrp_main.c:339: if (ch == 0xff)	// make unprogrammed EEPROM default to '0'
;	genCmpEq
;	gencjneshort
;	Peephole 112.b	changed ljmp to sjmp
;	Peephole 198.b	optimized misc jump sequence
	cjne	r3,#0xFF,00102$
;	Peephole 200.b	removed redundant sjmp
;	Peephole 300	removed redundant label 00115$
;	Peephole 300	removed redundant label 00116$
;	usrp_main.c:340: ch = '0';
;	genAssign
	mov	r3,#0x30
00102$:
;	usrp_main.c:341: usb_desc_serial_number_ascii[i << 1] = ch;
;	genCast
	mov	ar4,r2
;	genLeftShift
;	genLeftShiftLiteral
;	genlshTwo
;	peephole 177.g	optimized mov sequence
;	Peephole 181	changed mov to clr
	clr	a
	mov	r5,a
	xch	a,r4
	add	a,acc
	xch	a,r4
	rlc	a
	mov	r5,a
;	genPlus
;	Peephole 236.g	used r4 instead of ar4
	mov	a,r4
	add	a,#_usb_desc_serial_number_ascii
	mov	dpl,a
;	Peephole 236.g	used r5 instead of ar5
	mov	a,r5
	addc	a,#(_usb_desc_serial_number_ascii >> 8)
	mov	dph,a
;	genPointerSet
;     genFarPointerSet
	mov	a,r3
	movx	@dptr,a
;	usrp_main.c:337: for (i = 0; i < SERIAL_NO_LEN; i++){
;	genPlus
;     genPlusIncr
	inc	r2
;	Peephole 112.b	changed ljmp to sjmp
	sjmp	00103$
00107$:
	ret
;------------------------------------------------------------
;Allocation info for local variables in function 'main'
;------------------------------------------------------------
;------------------------------------------------------------
;	usrp_main.c:346: main (void)
;	-----------------------------------------
;	 function main
;	-----------------------------------------
_main:
;	usrp_main.c:355: memset (hash1, 0, USRP_HASH_SIZE);	// zero fpga bitstream hash.  This forces reload
;	genAssign
	mov	_memset_PARM_2,#0x00
;	genAssign
	mov	_memset_PARM_3,#0x10
	clr	a
	mov	(_memset_PARM_3 + 1),a
;	genCall
;	Peephole 182.a	used 16 bit load of DPTR
	mov	dptr,#_hash1
	mov	b,#0x00
	lcall	_memset
;	usrp_main.c:357: init_usrp ();
;	genCall
	lcall	_init_usrp
;	usrp_main.c:358: init_gpif ();
;	genCall
	lcall	_init_gpif
;	usrp_main.c:361: IFCONFIG |= bmGSTATE;			// no conflict, start with it on
;	genAssign
;	genOr
	mov	dptr,#_IFCONFIG
	movx	a,@dptr
	mov	r2,a
;	Peephole 248.a	optimized or to xdata
	orl	a,#0x04
	movx	@dptr,a
;	usrp_main.c:363: set_led_0 (0);
;	genCall
	mov	dpl,#0x00
	lcall	_set_led_0
;	usrp_main.c:364: set_led_1 (0);
;	genCall
	mov	dpl,#0x00
	lcall	_set_led_1
;	usrp_main.c:366: EA = 0;		// disable all interrupts
;	genAssign
	clr	_EA
;	usrp_main.c:368: patch_usb_descriptors();
;	genCall
	lcall	_patch_usb_descriptors
;	usrp_main.c:370: setup_autovectors ();
;	genCall
	lcall	_setup_autovectors
;	usrp_main.c:371: usb_install_handlers ();
;	genCall
	lcall	_usb_install_handlers
;	usrp_main.c:372: hook_timer_tick ((unsigned short) isr_tick);
;	genCast
	mov	r2,#_isr_tick
	mov	r3,#(_isr_tick >> 8)
;	genCall
	mov	dpl,r2
	mov	dph,r3
	lcall	_hook_timer_tick
;	usrp_main.c:374: EIEX4 = 1;		// disable INT4 FIXME
;	genAssign
	setb	_EIEX4
;	usrp_main.c:375: EA = 1;		// global interrupt enable
;	genAssign
	setb	_EA
;	usrp_main.c:377: fx2_renumerate ();	// simulates disconnect / reconnect
;	genCall
	lcall	_fx2_renumerate
;	usrp_main.c:379: main_loop ();
;	genCall
;	Peephole 253.b	replaced lcall/ret with ljmp
	ljmp	_main_loop
;
	.area CSEG    (CODE)
	.area CONST   (CODE)

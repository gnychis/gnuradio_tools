                              1 ;--------------------------------------------------------
                              2 ; File Created by SDCC : FreeWare ANSI-C Compiler
                              3 ; Version 2.6.0 #4309 (Nov 10 2006)
                              4 ; This file generated Wed Jan 23 16:41:20 2008
                              5 ;--------------------------------------------------------
                              6 	.module eeprom_io
                              7 	.optsdcc -mmcs51 --model-small
                              8 	
                              9 ;--------------------------------------------------------
                             10 ; Public variables in this module
                             11 ;--------------------------------------------------------
                             12 	.globl _eeprom_read_PARM_4
                             13 	.globl _eeprom_read_PARM_3
                             14 	.globl _eeprom_read_PARM_2
                             15 	.globl _eeprom_read
                             16 ;--------------------------------------------------------
                             17 ; special function registers
                             18 ;--------------------------------------------------------
                             19 	.area RSEG    (DATA)
                             20 ;--------------------------------------------------------
                             21 ; special function bits
                             22 ;--------------------------------------------------------
                             23 	.area RSEG    (DATA)
                             24 ;--------------------------------------------------------
                             25 ; overlayable register banks
                             26 ;--------------------------------------------------------
                             27 	.area REG_BANK_0	(REL,OVR,DATA)
   0000                      28 	.ds 8
                             29 ;--------------------------------------------------------
                             30 ; internal ram data
                             31 ;--------------------------------------------------------
                             32 	.area DSEG    (DATA)
   0017                      33 _eeprom_read_PARM_2:
   0017                      34 	.ds 1
   0018                      35 _eeprom_read_PARM_3:
   0018                      36 	.ds 2
   001A                      37 _eeprom_read_PARM_4:
   001A                      38 	.ds 1
                             39 ;--------------------------------------------------------
                             40 ; overlayable items in internal ram 
                             41 ;--------------------------------------------------------
                             42 	.area OSEG    (OVR,DATA)
                             43 ;--------------------------------------------------------
                             44 ; indirectly addressable internal ram data
                             45 ;--------------------------------------------------------
                             46 	.area ISEG    (DATA)
                             47 ;--------------------------------------------------------
                             48 ; bit data
                             49 ;--------------------------------------------------------
                             50 	.area BSEG    (BIT)
                             51 ;--------------------------------------------------------
                             52 ; paged external ram data
                             53 ;--------------------------------------------------------
                             54 	.area PSEG    (PAG,XDATA)
                             55 ;--------------------------------------------------------
                             56 ; external ram data
                             57 ;--------------------------------------------------------
                             58 	.area XSEG    (XDATA)
   180E                      59 _eeprom_read_cmd_1_1:
   180E                      60 	.ds 1
                             61 ;--------------------------------------------------------
                             62 ; external initialized ram data
                             63 ;--------------------------------------------------------
                             64 	.area HOME    (CODE)
                             65 	.area GSINIT0 (CODE)
                             66 	.area GSINIT1 (CODE)
                             67 	.area GSINIT2 (CODE)
                             68 	.area GSINIT3 (CODE)
                             69 	.area GSINIT4 (CODE)
                             70 	.area GSINIT5 (CODE)
                             71 	.area GSINIT  (CODE)
                             72 	.area GSFINAL (CODE)
                             73 	.area CSEG    (CODE)
                             74 ;--------------------------------------------------------
                             75 ; global & static initialisations
                             76 ;--------------------------------------------------------
                             77 	.area HOME    (CODE)
                             78 	.area GSINIT  (CODE)
                             79 	.area GSFINAL (CODE)
                             80 	.area GSINIT  (CODE)
                             81 ;--------------------------------------------------------
                             82 ; Home
                             83 ;--------------------------------------------------------
                             84 	.area HOME    (CODE)
                             85 	.area CSEG    (CODE)
                             86 ;--------------------------------------------------------
                             87 ; code
                             88 ;--------------------------------------------------------
                             89 	.area CSEG    (CODE)
                             90 ;------------------------------------------------------------
                             91 ;Allocation info for local variables in function 'eeprom_read'
                             92 ;------------------------------------------------------------
                             93 ;eeprom_offset             Allocated with name '_eeprom_read_PARM_2'
                             94 ;buf                       Allocated with name '_eeprom_read_PARM_3'
                             95 ;len                       Allocated with name '_eeprom_read_PARM_4'
                             96 ;i2c_addr                  Allocated to registers r2 
                             97 ;cmd                       Allocated with name '_eeprom_read_cmd_1_1'
                             98 ;------------------------------------------------------------
                             99 ;	eeprom_io.c:29: eeprom_read (unsigned char i2c_addr, unsigned char eeprom_offset,
                            100 ;	-----------------------------------------
                            101 ;	 function eeprom_read
                            102 ;	-----------------------------------------
   0A05                     103 _eeprom_read:
                    0002    104 	ar2 = 0x02
                    0003    105 	ar3 = 0x03
                    0004    106 	ar4 = 0x04
                    0005    107 	ar5 = 0x05
                    0006    108 	ar6 = 0x06
                    0007    109 	ar7 = 0x07
                    0000    110 	ar0 = 0x00
                    0001    111 	ar1 = 0x01
                            112 ;	genReceive
   0A05 AA 82               113 	mov	r2,dpl
                            114 ;	eeprom_io.c:36: cmd[0] = eeprom_offset;
                            115 ;	genPointerSet
                            116 ;     genFarPointerSet
   0A07 90 18 0E            117 	mov	dptr,#_eeprom_read_cmd_1_1
   0A0A E5 17               118 	mov	a,_eeprom_read_PARM_2
   0A0C F0                  119 	movx	@dptr,a
                            120 ;	eeprom_io.c:37: if (!i2c_write(i2c_addr, cmd, 1))
                            121 ;	genAssign
   0A0D 75 1B 0E            122 	mov	_i2c_write_PARM_2,#_eeprom_read_cmd_1_1
   0A10 75 1C 18            123 	mov	(_i2c_write_PARM_2 + 1),#(_eeprom_read_cmd_1_1 >> 8)
                            124 ;	genAssign
   0A13 75 1D 01            125 	mov	_i2c_write_PARM_3,#0x01
                            126 ;	genCall
   0A16 8A 82               127 	mov	dpl,r2
   0A18 C0 02               128 	push	ar2
   0A1A 12 0B 64            129 	lcall	_i2c_write
   0A1D E5 82               130 	mov	a,dpl
   0A1F D0 02               131 	pop	ar2
                            132 ;	genIfx
                            133 ;	genIfxJump
                            134 ;	Peephole 108.b	removed ljmp by inverse jump logic
                            135 ;	eeprom_io.c:38: return 0;
                            136 ;	genRet
   0A21 70 03               137 	jnz	00102$
                            138 ;	Peephole 300	removed redundant label 00106$
                            139 ;	Peephole 256.c	loading dpl with zero from a
   0A23 F5 82               140 	mov	dpl,a
                            141 ;	Peephole 112.b	changed ljmp to sjmp
                            142 ;	Peephole 251.b	replaced sjmp to ret with ret
   0A25 22                  143 	ret
   0A26                     144 00102$:
                            145 ;	eeprom_io.c:40: return i2c_read(i2c_addr, buf, len);
                            146 ;	genAssign
   0A26 85 18 1B            147 	mov	_i2c_read_PARM_2,_eeprom_read_PARM_3
   0A29 85 19 1C            148 	mov	(_i2c_read_PARM_2 + 1),(_eeprom_read_PARM_3 + 1)
                            149 ;	genAssign
   0A2C 85 1A 1D            150 	mov	_i2c_read_PARM_3,_eeprom_read_PARM_4
                            151 ;	genCall
   0A2F 8A 82               152 	mov	dpl,r2
                            153 ;	genRet
                            154 ;	Peephole 253.b	replaced lcall/ret with ljmp
   0A31 02 0A A1            155 	ljmp	_i2c_read
                            156 ;
                            157 	.area CSEG    (CODE)
                            158 	.area CONST   (CODE)

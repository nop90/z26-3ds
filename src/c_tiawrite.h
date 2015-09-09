/*

	tiawrite.c -- handlers for writes to and reads from TIA registers


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#pragma once

void ReadCollision(void);

void ReadAnalogINPT(void);

void ReadDigitalINPT(void);

void ReadTIAdummy ( void);

void AdjustPalette();

void H_VSYNC(void);

void H_VBLANK(void);

void H_WSYNC(void);

void H_Null(void);

void H_NUSIZ0(void);

void H_NUSIZ1(void);

void H_COLUP0(void);

void H_COLUP1(void);

void H_COLUPF(void);

void H_COLUBK(void);

void H_CTRLPF(void);

void H_REFP0(void);

void H_REFP1(void);

void H_PF0(void);

void H_PF1(void);

void H_PF2(void);

void H_RESP0(void);

void H_RESP1(void);

void H_RESM0(void);

void H_RESM1(void);

void H_RESBL(void);

void H_GRP0(void);

void H_GRP1(void);

void H_ENAM0(void);

void H_ENAM1(void);

void H_ENABL(void);

void H_HMP0(void);

void H_HMP1(void);

void H_HMM0(void);

void H_HMM1(void);

void H_HMBL(void);

void H_VDELP0(void);

void H_VDELP1(void);

void H_VDELBL(void);

void H_RESMP0(void);

void H_RESMP1(void);

void H_HMOVE(void);

void H_HMCLR(void);

void H_CXCLR(void);

void (* TIAReadHandler[16])(void) = {						
	ReadCollision,	// CXM0P
	ReadCollision,	// CXM1P
	ReadCollision,	// CXP0FB
	ReadCollision,	// CXP1FB
	ReadCollision,	// CXM0FB
	ReadCollision,	// CXM1FB
	ReadCollision,	// CXBLPF
	ReadCollision,	// CXPPMM
	ReadAnalogINPT,	// INPT0
	ReadAnalogINPT,	// INPT1
	ReadAnalogINPT,	// INPT2
	ReadAnalogINPT,	// INPT3
	ReadDigitalINPT,	// INPT4
	ReadDigitalINPT,	// INPT5
	ReadTIAdummy,	// 0x0E
	ReadTIAdummy	// 0x0F
};

void (* TIAWriteHandler[64])(void) = {						
	H_VSYNC,	 //  00 -- VSYNC
	H_VBLANK,	 //  01 -- VBLANK
	H_WSYNC,	 //  02 -- WSYNC
	H_Null,		 //  03 -- reset horizontal sync
				 // 	  for factory testing only !

	H_NUSIZ0,	 //  04 -- NUSIZ0
	H_NUSIZ1,	 //  05 -- NUSIZ1
	H_COLUP0,	 //  06 -- COLUP0
	H_COLUP1,	 //  07 -- COLUP1
	H_COLUPF,	 //  08 -- COLUPF
	H_COLUBK,	 //  09 -- COLUBK
	H_CTRLPF,	 //  0a -- CTRLPF
	H_REFP0,	 //  0b -- REFP0
	H_REFP1,	 //  0c -- REFP1
	H_PF0,		 //  0d -- PF0
	H_PF1,		 //  0e -- PF1
	H_PF2,		 //  0f -- PF2
	H_RESP0,	 //  10 -- RESP0
	H_RESP1,	 //  11 -- RESP1
	H_RESM0,	 //  12 -- RESM0
	H_RESM1,	 //  13 -- RESM1
	H_RESBL,	 //  14 -- RESBL
	H_AUDC0,	 //  15 -- AUDC0
	H_AUDC1,	 //  16 -- AUDC1
	H_AUDF0,	 //  17 -- AUDF0
	H_AUDF1,	 //  18 -- AUDF1
	H_AUDV0,	 //  19 -- AUDV0
	H_AUDV1,	 //  1a -- AUDV1
	H_GRP0,		 //  1b -- GRP0
	H_GRP1,		 //  1c -- GRP1
	H_ENAM0,	 //  1d -- ENAM0
	H_ENAM1,	 //  1e -- ENAM1
	H_ENABL,	 //  1f -- ENABL
	H_HMP0,		 //  20 -- HMP0
	H_HMP1,		 //  21 -- HMP1
	H_HMM0,		 //  22 -- HMM0
	H_HMM1,		 //  23 -- HMM1
	H_HMBL,		 //  24 -- HMBL
	H_VDELP0,	 //  25 -- VDELP0
	H_VDELP1,	 //  26 -- VDELP1
	H_VDELBL,	 //  27 -- VDELBL
	H_RESMP0,	 //  28 -- RESMP0
 	H_RESMP1,	 //  29 -- RESMP1
	H_HMOVE,	 //  2a -- HMOVE
	H_HMCLR,	 //  2b -- HMCLR
	H_CXCLR,	 //  2c -- CXCLR

	H_Null,		 //  2d -- these registers are undefined
	H_Null,		 //  2e
	H_Null,		 //  2f
	H_Null,		 //  30
	H_Null,		 //  31
	H_Null,		 //  32
	H_Null,		 //  33
	H_Null,		 //  34
	H_Null,		 //  35
	H_Null,		 //  36
	H_Null,		 //  37
	H_Null,		 //  38
	H_Null,		 //  39
	H_Null,		 //  3a
	H_Null,		 //  3b
	H_Null,		 //  3c
	H_Null,		 //  3d
	H_Null,		 //  3e
	H_Null		 //  3f
};

void C_NewTIA(void);
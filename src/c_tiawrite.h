/*

	tiawrite.c -- handlers for writes to and reads from TIA registers


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#ifndef __C_TIAWRITE_H__
#define __C_TIAWRITE_H__

#include "c_tiasnd.h"

void (* TIAReadHandler[16])(void);

void (* TIAWriteHandler[64])(void);

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

void C_NewTIA(void);

#endif
/*

	tiasnd.c -- z26 sound generation routines

	based on TIASound (c) 1996-1997 by Ron Fries
	please see the end of this file for Ron's banner

*/

#ifndef __C_TIASND_H__
#define __C_TIASND_H__

#include "globals.h"

/* CONSTANT DEFINITIONS */

/* definitions for AUDCx (15, 16) */
#define SET_TO_1     0x00      /* 0000 */
#define POLY4        0x01      /* 0001 */
#define DIV31_POLY4  0x02      /* 0010 */
#define POLY5_POLY4  0x03      /* 0011 */
#define PURE1        0x04      /* 0100 */
#define PURE2        0x05      /* 0101 */
#define DIV31_PURE   0x06      /* 0110 */
#define POLY5_2      0x07      /* 0111 */
#define POLY9        0x08      /* 1000 */
#define POLY5        0x09      /* 1001 */
#define DIV31_POLY5  0x0a      /* 1010 */
#define POLY5_POLY5  0x0b      /* 1011 */
#define DIV3_PURE    0x0c      /* 1100 */
#define DIV3_PURE2   0x0d      /* 1101 */
#define DIV93_PURE   0x0e      /* 1110 */
#define DIV3_POLY5   0x0f      /* 1111 */
                 
#define DIV3_MASK    0x0c                 
                 
#define AUDC0        0x15
#define AUDC1        0x16
#define AUDF0        0x17
#define AUDF1        0x18
#define AUDV0        0x19
#define AUDV1        0x1a

/* the size (in entries) of the 4 polynomial tables */
#define POLY4_SIZE  0x000f
#define POLY5_SIZE  0x001f
#define POLY9_SIZE  0x01ff

/* channel definitions */
#define CHAN1       0
#define CHAN2       1

#define FALSE       0
#define TRUE        1

int TSB_result;

db Bit4[15];
db Bit5[31];
db Bit5T[31];
db Div31[31];
db Div6[6];
dd Samp_n_cnt;
dd Samp_n_max;
db D6[2];
db P4[2];
db P5[2];
db AUDC[2];
db AUDF[2];
db AUDV[2];
db Outvol[2];
db Div_n_cnt[2];
db Div_n_max[2];

dd P9_sreg[2];
dd prev_sample;
db next_sample;

void (* AUDC_Jumptab[16])(int chan);

void TSB_Always_High(int chan);
	
void TSB_Poly4(int chan);
	
void TSB_Div31_Poly4(int chan);
	
void TSB_Poly5_Poly4(int chan);
	
void TSB_Pure(int chan);
	
void TSB_Div31_Pure(int chan);
	
void TSB_Poly5(int chan);
	
void TSB_Poly9(int chan);
	
void TSB_Poly5_Poly5(int chan);
	
void TSB_Div6_Pure(int chan);
	
void TSB_Div31_Div6(int chan);
	
void TSB_Poly5_Div6(int chan);

void Init_Tiasnd();

void UTS_Chan(int chan);

void H_AUDC0();

void H_AUDC1();

void H_AUDF0();

void H_AUDF1();

void H_AUDV0();

void H_AUDV1();

void TSB_ProcessChannel(int chan);

void TSB_Ch0done();

dd TIA_Sound_Byte();

#endif

/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

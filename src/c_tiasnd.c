/*

	tiasnd.c -- z26 sound generation routines

	based on TIASound (c) 1996-1997 by Ron Fries
	please see the end of this file for Ron's banner

*/

#include "globals.h"
#include "c_tiasnd.h"
#include "c_pitfall2.h"
#include "c_banks.h"

extern db P2_AUDV;

void TSB_Always_High(int chan){
//	Outvol[chan] = AUDV[chan];
}
	
void TSB_Poly4(int chan){
	P4[chan]++;
	if(P4[chan] == 15) P4[chan] = 0;
	if(Bit4[P4[chan]] == 0) Outvol[chan] = 0;
	else Outvol[chan] = AUDV[chan];
}
	
void TSB_Div31_Poly4(int chan){
	if(Div31[P5[chan]] == 1){
		P4[chan]++;
		if(P4[chan] == 15) P4[chan] = 0;
		if(Bit4[P4[chan]] == 0) Outvol[chan] = 0;
		else Outvol[chan] = AUDV[chan];
	}
}
	
void TSB_Poly5_Poly4(int chan){
	if(Bit5T[P5[chan]] == 1){
		P4[chan]++;
		if(P4[chan] == 15) P4[chan] = 0;
		if(Bit4[P4[chan]] == 0) Outvol[chan] = 0;
		else Outvol[chan] = AUDV[chan];
	}
}
	
void TSB_Pure(int chan){
	if(Outvol[chan] == 0) Outvol[chan] = AUDV[chan];
	else Outvol[chan] = 0;
}
	
void TSB_Div31_Pure(int chan){
	if(Div31[P5[chan]] == 1){
		if(Outvol[chan] == 0) Outvol[chan] = AUDV[chan];
		else Outvol[chan] = 0;
	}
}
	
void TSB_Poly5(int chan){
	if(Bit5[P5[chan]] == 1) Outvol[chan] = AUDV[chan];
	else Outvol[chan] = 0;
}
	
void TSB_Poly9(int chan){
/*
 generate a sequence of pseudo-random bits 511 bits long
 by emulating a 9-bit shift register with feedback taps at
 positions 5 and 9.
*/
	P9_sreg[chan] = (P9_sreg[chan] >> 1) |
		(((P9_sreg[chan] & 0x1) ^ ((P9_sreg[chan] & 0x10) >> 4)) << 8);
	if(P9_sreg[chan] & 1) Outvol[chan] = AUDV[chan];
	else Outvol[chan] = 0;
}
	
void TSB_Poly5_Poly5(int chan){
	if(Bit5[P5[chan]] == 1){
		if(Bit5[P5[chan]] == 1) Outvol[chan] = AUDV[chan];
		else Outvol[chan] = 0;
	}
}
	
void TSB_Div6_Pure(int chan){
	D6[chan]++;
	if(D6[chan] == 6) D6[chan] = 0;
	if(Div6[D6[chan]] == 1){
		if(Outvol[chan] == 0) Outvol[chan] = AUDV[chan];
		else Outvol[chan] = 0;
	}
}
	
void TSB_Div31_Div6(int chan){
	if(Div31[P5[chan]] == 1){
		D6[chan]++;
		if(D6[chan] == 6) D6[chan] = 0;
		if(Div6[D6[chan]] == 1){
			if(Outvol[chan] == 0) Outvol[chan] = AUDV[chan];
			else Outvol[chan] = 0;
		}
	}
}
	
void TSB_Poly5_Div6(int chan){
	if(Bit5T[P5[chan]] == 1){
		D6[chan]++;
		if(D6[chan] == 6) D6[chan] = 0;
		if(Div6[D6[chan]] == 1){
			if(Outvol[chan] == 0) Outvol[chan] = AUDV[chan];
			else Outvol[chan] = 0;
		}
	}
}	

/*
 	handle the power-up initialization functions
 	these functions should only be executed on a cold-restart

 calculate the sample 'divide by N' value based on the playback freq
*/

void Init_Tiasnd() {
	int chan;
	
	Samp_n_max = (31400 << 8) / 31400;
	Samp_n_cnt = 0;

	for (chan = CHAN1; chan <= CHAN2; chan++)
	{
		Outvol[chan] =	0;
		Div_n_cnt[chan]	= 0;
		Div_n_max[chan]	= 0;
		AUDC[chan] = 0;
		AUDF[chan] = 0;
		AUDV[chan] = 0;
		P4[chan] = 0;
		P5[chan] = 0;
		P9_sreg[chan] =	1;
	}
}

/*
	update TIA sound registers
*/

void UTS_Chan(int chan) {
	dd new_val;

	if(AUDC[chan] == 0) {
		new_val = 0;
		Outvol[chan] = AUDV[chan];
	} else new_val = AUDF[chan] + 1;

	if( new_val != Div_n_max[chan] ) {
		Div_n_max[chan] = new_val & 0xff;
		if( Div_n_cnt[chan] == 0 || new_val == 0 )
			Div_n_cnt[chan] = new_val & 0xff;
	}
}


void H_AUDC0() {
	AUDC[0] = DataBus & 0x0f;
	UTS_Chan(0);
}


void H_AUDC1() {
	AUDC[1] = DataBus & 0x0f;
	UTS_Chan(1);
}


void H_AUDF0() {
	AUDF[0] = DataBus & 0x1f;
	UTS_Chan(0);
}


void H_AUDF1() {
	AUDF[1] = DataBus & 0x1f;
	UTS_Chan(1);
}


void H_AUDV0() {
	AUDV[0] = (DataBus & 0xf) << 3;
	UTS_Chan(0);
}


void H_AUDV1() {
	AUDV[1] = (DataBus & 0xf) << 3;
	UTS_Chan(1);
}


/*
	generate a sound byte based on the TIA chip parameters
*/

void TSB_ProcessChannel(int chan) {
	if(Div_n_cnt[chan] < 1) return;
	if(Div_n_cnt[chan] > 1) {
		Div_n_cnt[chan]--;
	} else {
		/* reset the counter */
		Div_n_cnt[chan] = Div_n_max[chan];

		/* the P5 counter has multiple uses, so we inc it here */
		P5[chan]++;
		if (P5[chan] == POLY5_SIZE)
			P5[chan] = 0;

		(* AUDC_Jumptab[AUDC[chan] & 0xf])(chan);
	}
}

void TSB_Ch0done() {
	/* decrement the sample counter - value is 256 since the lower
		byte contains the fractional part */
	Samp_n_cnt -= 256;

	/* if the count down has reached zero */
	if (Samp_n_cnt < 256)
	{
		/* adjust the sample counter */
		Samp_n_cnt += Samp_n_max;

		/* calculate the latest output value and set our result */
		if(Pitfall2){
			Clock_Pitfall2();
			TSB_result = ((P2_AUDV & 0xf) << 3) + Outvol[1];
		}else TSB_result = Outvol[0] + Outvol[1];
		if(GamePaused) TSB_result = 0x80;

		if(dsp){	/* doing digital signal processing ? */
			/* take edge of square wave */
			next_sample = TSB_result & 0xff;
			/* dsp = 2: scaled moving average */
			prev_sample = (prev_sample + next_sample) >> 1;
			TSB_result = prev_sample & 0xff;
			/* dsp = 1: simple moving average */
			if(dsp == 1) prev_sample = next_sample;
		}
	}
}

dd TIA_Sound_Byte() {
	TSB_result = -1;

	while(TSB_result==-1) {
		if(!Pitfall2) TSB_ProcessChannel(0);
		TSB_ProcessChannel(1);
		TSB_Ch0done(); /* sets TSB_result for us */
	}
	return TSB_result;
}


/*****************************************************************************/
/*                                                                           */
/*                 License Information and Copyright Notice                  */
/*                 ========================================                  */
/*                                                                           */
/* TiaSound is Copyright(c) 1996 by Ron Fries                                */
/*                                                                           */
/* This library is free software; you can redistribute it and/or modify it   */
/* under the terms of version 2 of the GNU Library General Public License    */
/* as published by the Free Software Foundation.                             */
/*                                                                           */
/* This library is distributed in the hope that it will be useful, but       */
/* WITHOUT ANY WARRANTY; without even the implied warranty of                */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library */
/* General Public License for more details.                                  */
/* To obtain a copy of the GNU Library General Public License, write to the  */
/* Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.   */
/*                                                                           */
/* Any permitted reproduction of these routines, in whole or in part, must   */
/* bear this legend.                                                         */
/*                                                                           */
/*****************************************************************************/

/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

/*

 Pitfall 2 8K bankswitch scheme -- similar to standard F8

	21 -- 8K+DPC Pitfall2 [P2]
	
	2 4K ROM banks at $1000 - $1FFF
	select bank 0 by accessing $1FF8
	select bank 1 by accessing $1FF9
	the DPC has:
		2K of graphics ROM,
		a random number genarator
		and a sample generator for 3 combined squarewave sound channels
	DPC read ports range from $1000 to $103F
	DPC write ports range from $1040 to $107F

 Based in part on David Crane's U.S. Patent 4,644,495, Feb 17,1987.


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

//db Pitfall2 = 0;	//  tell RIOT timer to clock the music

#include "globals.h"
#include "c_pitfall2.h"
#include "c_banks.h"


/*
	Pitfall 2 register handlers
*/

/*
	null register read/write
*/

void P2_NoIO(void){

	if(!(AddressBus & 0xfc0)) DataBus = 0;	// only change for read registers
}


/*
 routine to tune the pitch of the music

 We use this to match the Pitfall II music clock to the TIA music clock.

 Due to the discrete nature of this stuff, since the two clocks are not 
 integer multiples of one another, adjustments of the ratio can affect the
 relative pitch of notes in a chord as well as the overall pitch.  So you 
 need to make sure that the important chords sound *nice*.
*/

dd Tune_Music(void){

	return DataBus * 129 / 79;
}

/*
	 write top register
*/

void P2_WriteTop(void){

	P2_Top[AddressBus & 0x7] = DataBus;
	if((AddressBus & 0x7) > 4)
		P2_Music_Top[AddressBus & 0x7] = Tune_Music();
}

/*
	write bottom register
*/

void P2_WriteBottom(void){

	P2_Bottom[AddressBus & 0x7] = DataBus;
	if((AddressBus & 0x7) > 4)
		P2_Music_Bottom[AddressBus & 0x7] = Tune_Music();
}

/*
	write counter low
*/

void P2_WriteCounterLow(void){

	P2_Counters[AddressBus & 0x7] =
		(P2_Counters[AddressBus & 07] & 0x700) + DataBus;
	if((AddressBus & 0x7) > 4)
		P2_Music_Count[AddressBus & 0x7] = Tune_Music();
}

/*
	write counter high AND music enable
*/

void P2_WriteCounterHigh(void){

	P2_Counters[AddressBus & 0x7] =
		((P2_Counters[AddressBus & 07] & 0xff) + (DataBus * 256)) & 0x7ff;
	P2_Enable[AddressBus & 0x7] = DataBus;
	P2_Flags[AddressBus & 0x7] = 0;
}

/*
	reset the random number generator
*/

void P2_ResetRandom(void){

	P2_sreg = 1;
}

/*
	read flags
*/

void P2_ReadFlags(void){

	DataBus = P2_Flags[AddressBus & 0x7];
}

/*
	support function to read data via data fetcher
*/

void Read_DF(void){

	if((P2_Counters[AddressBus & 0x7] & 0xff) == P2_Top[AddressBus & 0x7])
		P2_Flags[AddressBus & 0x7] = 0xff;
	if((P2_Counters[AddressBus & 0x7] & 0xff) == P2_Bottom[AddressBus &0x7])
		P2_Flags[AddressBus & 0x7] = 0x0;

	P2_Rbyte = CartRom[0x27ff - P2_Counters[AddressBus & 0x7]];	// yes it *is* magic
	P2_Counters[AddressBus & 0x7]--;

}


/*
	read data via data fetcher
*/

void P2_Read_DF(void){

	Read_DF();
	DataBus = P2_Rbyte;
}

/*
	read data via data fetcher ANDed with flag
*/

void P2_Read_DF_Flag(void){

	Read_DF();
	DataBus = P2_Rbyte & P2_Flags[AddressBus & 0x7];
}	

/*
	Generate a sequence of pseudo-random numbers 255 numbers long
	by emulating an 8-bit shift register with feedback taps at
	positions 4, 5, 6, and 8.
*/

void P2_Read_Random(void){

	P2_sreg =
		(((((P2_sreg & 0x80) >> 7) ^
		   ((P2_sreg & 0x20) >> 5)) ^
		  (((P2_sreg & 0x10) >> 4) ^
		   ((P2_sreg & 0x08) >> 3))) ^ 1) |
		    (P2_sreg << 1);
	DataBus = P2_sreg;
}



/*
	read sound stuff
*/

/*
	read sound entry point

	This is just for show -- Pitfall 2 short-circuits AUDV.
*/

void P2_Read_Sound(void){

	DataBus = P2_AUDV;
}


/*
	clock music -- clock all channels
*/

void Clock_Music(void){

	if(P2_Enable[5] & 0x10){
		if(P2_Music_Count[5] == P2_Music_Bottom[5]){
			P2_Flags[5] = 0;
			P2_Music_Count[5]--;
		}else if(P2_Music_Count[5] == 0xffffffff){
			P2_Music_Count[5] = P2_Music_Top[5];
			P2_Flags[5] = 0xff;
		}else P2_Music_Count[5]--;
	}
	if(P2_Enable[6] & 0x10){
		if(P2_Music_Count[6] == P2_Music_Bottom[6]){
			P2_Flags[6] = 0;
			P2_Music_Count[6]--;
		}else if(P2_Music_Count[6] == 0xffffffff){
			P2_Music_Count[6] = P2_Music_Top[6];
			P2_Flags[6] = 0xff;
		}else P2_Music_Count[6]--;
	}
	if(P2_Enable[7] & 0x10){
		if(P2_Music_Count[7] == P2_Music_Bottom[7]){
			P2_Flags[7] = 0;
			P2_Music_Count[7]--;
		}else if(P2_Music_Count[7] == 0xffffffff){
			P2_Music_Count[7] = P2_Music_Top[7];
			P2_Flags[7] = 0xff;
		}else P2_Music_Count[7]--;
	}
}


/*
	build AUDV byte
*/

/*
	clock Pitfall 2 from TIA sound
*/

void Clock_Pitfall2(void){

	Clock_Music();
	P2_AUDV = Mix_AUDV[(P2_Flags[5] & 0x1) | (P2_Flags[6] & 0x2) | (P2_Flags[7] & 0x4)];
}


/*
	Pitfall 2 initialization
*/

void Init_P2(void){				 //  <-- from init.asm

	int i;
	
	for(i=0; i<8; i++){
		P2_Flags[i] =  0;
		P2_Counters[i] =  0;
		P2_Top[i] = 0;
		P2_Bottom[i] = 0;
		P2_Enable[i] = 0;
		P2_Music_Top[i] = 0;
		P2_Music_Bottom[i] = 0;
		P2_Music_Count[i] = 0;
	}

	Pitfall2 = 0;
	P2_Rbyte = 0;
	P2_AUDV = 0;

	P2_sreg = 1;		 //  random # generator (must be non-zero)
}

void SetPitfallII(void){				 //  <-- from banks.asm
 	BSType = 21;
 	RomBank = 0x1000;	// don't know if this is needed...
 	Pitfall2 = 1;		// tell RIOT to clock the music
}

/*
	bankswitch entry points
*/

void InitP2(void){
	int i;
	
	for(i = 0; i < 0x1000; i++){
		ReadAccess[i] = TIARIOTReadAccess[i];
		WriteAccess[i] = TIARIOTWriteAccess[i];
		ReadAccess[0x1000 + i] = &ReadBS4K;
		WriteAccess[0x1000 + i] = &WriteROM4K;
	}
	for(i = 0; i < 2; i++){
		ReadAccess[0x1ff8 + i] = &ReadHotspotBS4K;
		WriteAccess[0x1ff8 + i] = &WriteHotspotBS4K;
	}
	HotspotAdjust = 8;

	for(i = 0; i < 0x40; i++){
		ReadAccess[0x1000 + i] = P2_ReadFunctions[i];
		WriteAccess[0x1000 + i] = P2_ReadFunctions[i];
		WriteAccess[0x1040 + i] = P2_WriteFunctions[i];
		ReadAccess[0x1040 + i] = P2_WriteFunctions[i];
	}
	Copy64K();
}

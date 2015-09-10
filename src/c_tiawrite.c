/*

	tiawrite.c -- handlers for writes to and reads from TIA registers


 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

/*
	TIA read handlers
*/

#include "globals.h"
#include "position.h"
#include "controls.h"
#include "c_tiawrite.h"
#include "c_tialine.h"
#include "c_tiasnd.h"
#include "video.h"

void ReadCollision(void){

	CatchUpPixels();
	DataBus = (DataBus & 0x3f) |
	          ((TIACollide >> ((AddressBus & 0x7) << 1)) & 0x3) << 6;
}

void ReadAnalogINPT(void){

	if(ChargeTrigger0[AddressBus & 0x3] <= ChargeCounter)
		DataBus = (DataBus & 0x3f) | 0x80;
}

void ReadDigitalINPT(void){

	TestLightgunHit(RClock, ScanLine);
	DataBus = (DataBus & 0x3f) | InputLatch[AddressBus & 0x1];
}

void ReadTIAdummy ( void){

	DataBus &= 0x3f;	/* TIA only sets the two topmost bits */
}

/*
	TIA write handlers
*/


void AdjustPalette() {

	if (Frame > 256) return;
	if (UserPaletteNumber != 0xff) return;
	if (GamePaletteNumber != 0xff) return;
	if (LinesInFrame != PrevLinesInFrame)
	{
		if (Frame != 5) return;		// force adjustment of unstable games (once)
	}

	if (LinesInFrame < 287)
	{	// NTSC
		if (PaletteNumber == 0) return;
		PaletteNumber = 0;
	}
	else
	{	// PAL
		if (PaletteNumber == 1) return;
		PaletteNumber = 1;
	}
	srv_SetPalette();
	ClearScreenBuffers();
	position_game();

}

void H_VSYNC(void){

	if(DataBus & 0x02){
	
		if (VSyncFlag) return;	// somebody hitting VSYNC more than necessary
		
		PrevLinesInFrame = LinesInFrame;
		LinesInFrame = ScanLine - 1;
		ScanLine = 1;
		if (LinesInFrame > 3) Frame++;	// ignore quick double-hit (pickpile)
		
		AdjustPalette();
	}
	VSyncFlag = DataBus & 0x02;
}


void H_VBLANK(void){
	
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	VBlank = DataBus;
//	TIA_Mask_Objects = ((DataBus & 0x02) << 5) | (TIA_Mask_Objects & 0x3f);
	TIA_VBLANK = DataBus & 0x02;
	if(DataBus & 0x80) ChargeCounter = 0;
}


void H_WSYNC(void){

 	// Don't halt the CPU, if we're already at the end of the line
	if(RClock != CYCLESPERSCANLINE) TriggerWSYNC = 1;
 	// WSYNC only halts the CPU on read cycles so we handle it in cpu.m4
}


void H_Null(void){

}


void H_NUSIZ0(void){
//	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	NUSIZ0_number = DataBus & 0x07;
	NUSIZ_M0_width = DataBus & 0x30;

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x00003ff8) | NUSIZ0_number;
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];

	Pointer_Index_M0 = (Pointer_Index_M0 & 0xc8) | NUSIZ0_number | NUSIZ_M0_width;
	TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
/*
	if(NUSIZ0_number == 5){
		// double and quadrouple width players need one extra offset cycle
//		if((TIA_P0_Offset) && (NUSIZ_P0_width == 0)) TIA_P0_Offset++;
		NUSIZ_P0_width = 1;
	}else if(NUSIZ0_number == 7){
//		if((TIA_P0_Offset) && (NUSIZ_P0_width == 0)) TIA_P0_Offset++;
		NUSIZ_P0_width = 2;
	}else{
//		if((TIA_P0_Offset) && (NUSIZ_P0_width != 0)) TIA_P0_Offset--;
		NUSIZ_P0_width = 0;
	}
*/
}


void H_NUSIZ1(void){
//	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	NUSIZ1_number = DataBus & 0x07;
	NUSIZ_M1_width = DataBus & 0x30;

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x00003ff8) | NUSIZ1_number;
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];

	Pointer_Index_M1 = (Pointer_Index_M1 & 0xc8) | NUSIZ1_number | NUSIZ_M1_width;
	TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
/*
	if(NUSIZ1_number == 5){
		// double and quadrouple width players need one extra offset cycle
//		if((TIA_P1_Offset) && (NUSIZ_P1_width == 0)) TIA_P1_Offset++;
		NUSIZ_P1_width = 1;
	}else if(NUSIZ1_number == 7){
//		if((TIA_P1_Offset) && (NUSIZ_P1_width == 0)) TIA_P1_Offset++;
		NUSIZ_P1_width = 2;
	}else{
//		if((TIA_P1_Offset) && (NUSIZ_P1_width != 0)) TIA_P1_Offset--;
		NUSIZ_P1_width = 0;
	}
*/
}


void H_COLUP0(void){
	CatchUpPixels();
	TIA_Colour_Table[P0_COLOUR] = (DataBus >> 1) * 257;

}


void H_COLUP1(void){
	CatchUpPixels();
	TIA_Colour_Table[P1_COLOUR] = (DataBus >> 1) * 257;

}


void H_COLUPF(void){
	CatchUpPixels();
	TIA_Colour_Table[PF_COLOUR] = (DataBus >> 1) * 257;

}


void H_COLUBK(void){
	CatchUpPixels();
	TIA_Colour_Table[BG_COLOUR] = (DataBus >> 1) * 257;

}


void H_CTRLPF(void){
	CatchUpPixels();
	if(DataBus & 0x01) CTRLPF_PF_Reflect = 1;
	else CTRLPF_PF_Reflect = 0;
	if(DataBus & 0x02) CTRLPF_Score = 1;
	else CTRLPF_Score = 0;
	if(DataBus & 0x04){
		CTRLPF_Priority = 1;
		// playfield doesn't use score colours when it has priority
		CTRLPF_Score = 0;
	}
	else CTRLPF_Priority = 0;
	CTRLPF_BL_width = ((DataBus & 0x30) >> 4);

	Pointer_Index_BL = (Pointer_Index_BL & 0x0c) | CTRLPF_BL_width;
	TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
}


void H_REFP0(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_REFP0 = (DataBus & 0x08) <<9;

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x00002fff) | TIA_REFP0;
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
}


void H_REFP1(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_REFP1 = (DataBus & 0x08) << 9;

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x00002fff) | TIA_REFP1;
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
}


void H_PF0(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_Playfield_Bits = (TIA_Playfield_Bits & 0x0000ffff) | (DataBus << 16);
}


void H_PF1(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_Playfield_Bits = (TIA_Playfield_Bits & 0x00ff00ff) | (DataBus << 8);
}


void H_PF2(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_Playfield_Bits = (TIA_Playfield_Bits & 0x00ffff00) | DataBus;
}


void H_RESP0(void){
	CatchUpPixels();
	if((RClock % CYCLESPERSCANLINE) < 23) TIA_P0_counter = 2;
	else TIA_P0_counter = 0;
//	if(TIA_P0_Offset) TIA_P0_Offset = 5;	// clock gets reset for sprite retriggering trick

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x00003ff7);
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
}


void H_RESP1(void){
	CatchUpPixels();
	if((RClock % CYCLESPERSCANLINE) < 23) TIA_P1_counter = 2;
	else TIA_P1_counter = 0;
//	if(TIA_P1_Offset) TIA_P1_Offset = 5;	// clock gets reset for sprite retriggering trick

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x00003ff7);
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
}


void H_RESM0(void){
	CatchUpPixels();
	if((RClock % CYCLESPERSCANLINE) < 23) TIA_M0_counter = 2;
	else TIA_M0_counter = 0;

	Pointer_Index_M0 = (Pointer_Index_M0 & 0xf7);
	TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
}


void H_RESM1(void){
	CatchUpPixels();
	if((RClock % CYCLESPERSCANLINE) < 23) TIA_M1_counter = 2;
	else TIA_M1_counter = 0;
	Pointer_Index_M1 = (Pointer_Index_M1 & 0xf7);
	TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
}


void H_RESBL(void){
	CatchUpPixels();
	if((RClock % CYCLESPERSCANLINE) < 23) TIA_BL_counter = 2;
	else TIA_BL_counter = 0;
}


/*
	AUDC0, AUDC1, AUDF0, AUDF1, AUDV0, AUDV1 are handled in tiasnd.c
*/


void H_GRP0(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_GRP1_old = TIA_GRP1_new;
	TIA_GRP0_new = DataBus << 4;

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x0000300f);
	if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
	else Pointer_Index_P0 |= TIA_GRP0_new;
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x0000300f);
	if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
	else Pointer_Index_P1 |= TIA_GRP1_new;
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
}


void H_GRP1(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_GRP0_old = TIA_GRP0_new;
	TIA_ENABL_old = TIA_ENABL_new;
	TIA_GRP1_new = DataBus << 4;

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x0000300f);
	if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
	else Pointer_Index_P0 |= TIA_GRP0_new;
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x0000300f);
	if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
	else Pointer_Index_P1 |= TIA_GRP1_new;
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];

	Pointer_Index_BL = (Pointer_Index_BL & 0x0b);
	if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
	else Pointer_Index_BL |= TIA_ENABL_new;
	TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
}


void H_ENAM0(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	if(TIA_RESMP0) TIA_ENAM0 = 0;	// locked missiles are disabled
	else TIA_ENAM0 = (DataBus & 0x02) << 5;

	Pointer_Index_M0 = (Pointer_Index_M0 & 0xbf) | TIA_ENAM0;
	TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
}


void H_ENAM1(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	if(TIA_RESMP1) TIA_ENAM1 = 0;	// locked missiles are disabled
	else TIA_ENAM1 = (DataBus & 0x02) << 5;

	Pointer_Index_M1 = (Pointer_Index_M1 & 0xbf) | TIA_ENAM1;
	TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
}


void H_ENABL(void){
	TIA_Delayed_Write = 1;
	CatchUpPixels();
	TIA_Delayed_Write = 0;
	TIA_ENABL_new = (DataBus & 0x02) << 1;

	Pointer_Index_BL = (Pointer_Index_BL & 0x0b);
	if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
	else Pointer_Index_BL |= TIA_ENABL_new;
	TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
}


void H_HMP0(void){
	CatchUpPixels();
	TIA_HMP0_Value = (DataBus >> 4) ^ 0x08;
}


void H_HMP1(void){
	CatchUpPixels();
	TIA_HMP1_Value = (DataBus >> 4) ^ 0x08;
}


void H_HMM0(void){
	CatchUpPixels();
	TIA_HMM0_Value = (DataBus >> 4) ^ 0x08;
}


void H_HMM1(void){
	CatchUpPixels();
	TIA_HMM1_Value = (DataBus >> 4) ^ 0x08;
}


void H_HMBL(void){
	CatchUpPixels();
	TIA_HMBL_Value = (DataBus >> 4) ^ 0x08;
}


void H_VDELP0(void){
	CatchUpPixels();
	TIA_VDELP0 = DataBus & 0x01;

	Pointer_Index_P0 = (Pointer_Index_P0 & 0x0000300f);
	if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
	else Pointer_Index_P0 |= TIA_GRP0_new;
	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
}


void H_VDELP1(void){
	CatchUpPixels();
	TIA_VDELP1 = DataBus & 0x01;

	Pointer_Index_P1 = (Pointer_Index_P1 & 0x0000300f);
	if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
	else Pointer_Index_P1 |= TIA_GRP1_new;
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
}


void H_VDELBL(void){
	CatchUpPixels();
	TIA_VDELBL = DataBus & 0x01;

	Pointer_Index_BL = (Pointer_Index_BL & 0x0b);
	if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
	else Pointer_Index_BL |= TIA_ENABL_new;
	TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
}


void H_RESMP0(void){
	CatchUpPixels();
	TIA_RESMP0 = DataBus & 0x02;
	if(TIA_RESMP0){
		TIA_ENAM0 = 0;	// locking missile to player disables it
		// reset missile position to center of player position
		if(TIA_P0_counter < 5) TIA_M0_counter = TIA_P0_counter - 5 + 159;
		else TIA_M0_counter = TIA_P0_counter - 5;
		Pointer_Index_M0 = (Pointer_Index_M0 & 0xbf);
		TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
	}
}


void H_RESMP1(void){
	CatchUpPixels();
	TIA_RESMP1 = DataBus & 0x02;
	if(TIA_RESMP1){
		TIA_ENAM1 = 0;	// locking missile to player disables it
		// reset missile position to center of player position
		if(TIA_P1_counter < 5) TIA_M1_counter = TIA_P1_counter - 5 + 159;
		else TIA_M1_counter = TIA_P1_counter - 5;
		Pointer_Index_M1 = (Pointer_Index_M1 & 0xbf);
		TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
	}
}


void H_HMOVE(void){
	CatchUpPixels();
	if(((RClock % CYCLESPERSCANLINE) < 21) || ((RClock % CYCLESPERSCANLINE) > 74)) TIA_Display_HBlank = 1;
	TIA_HMOVE_Setup = 1;	// setting up HMOVE goes through several stages, so we only trigger it here
}


void H_HMCLR(void){
	CatchUpPixels();
	TIA_HMP0_Value = 8;
	TIA_HMP1_Value = 8;
	TIA_HMM0_Value = 8;
	TIA_HMM1_Value = 8;
	TIA_HMBL_Value = 8;
}


void H_CXCLR(void){
	CatchUpPixels();
	TIACollide = 0;
}


/*
	call the right TIA write handler
*/

void C_NewTIA(void){

	(* TIAWriteHandler[AddressBus & 0x3f])();
}

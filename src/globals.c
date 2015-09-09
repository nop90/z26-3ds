/*
** globals.c
*/

#include "globals.h"

/*
** reinitialize the global variables
*/

void def_LoadDefaults(void)
{
	UserBankswitch = 0xff;
	BSType = 0;

	PaletteNumber = 0xff;		// actual palette
	GamePaletteNumber = 0xff;	// game specified palette override
	UserPaletteNumber = 0xff;	// user specified palette override

	UserLeftController = 0xff;
	LeftController=0xff;

	UserRightController = 0xff;
	RightController=0xff;

	UserAllowAll4 = 0xff;
	AllowAll4 = 0;

	UserSwapPortsFlag = 0xff;
	SwapPortsFlag = 0;
	
	UserP0Diff = 0;			// default difficulty is easy
	UserP1Diff = 0;
	UserConsoleBW = 0;		// default to color console

	GameOffset = 0;
	theme = 0x50;			// aqua
	VideoMode = 0xff;
	FullScreen = 1;
	Narrow = 0;
	Tall = 0;
	CFirst = 0xffff;
	quiet = 0;
	IOPortA = 0xff;
	IOPortA_Controllers = 0xff;
	IOPortA_UnusedBits = 0xff;
	IOPortB = 0x0b;			// 0000 1011
	dsp = 1;
	UserPaddleSensitivity = 0;
	PaddleSensitivity = 0;
	UserTraceCount = 0;
	TraceCount = 0;
	UserTraceEnabled = 0;
	TraceEnabled = 0;
	OldTraceCount = 0;
	
	UserMouseBaseX = 0xff;
	UserMouseBaseY = 0xff;
	MouseBaseX = 0xff;
	MouseBaseY = 0xff;
	
	SimColourLoss = 0;
	UserLightgun = 0;
	UserLGadjust = 5;
	Lightgun = 0;
	LGadjust = 5;
	ShowLineCount = 0;
	UserDepth = 60;
	Depth = 60;
	KidVid = 0;
	KidVidTape = 0;
	MaxLines = 256 ;
	DoInterlace = 0;
	DoScanline = 0;
	MouseRude = 0;
	GrabInput = 0;
	ExitEmulator = 0;
	GamePaused = 0;
	GameReallyPaused = 0;
	StartInGUI = 0;
	OldCFirst = 0;
	PaddleAdjust = 0;

	UserJoystickEnabled = 1;
	JoystickEnabled = 1;
	MouseEnabled = 1;
	KeyboardEnabled = 1;
	StelladaptorEnabled = 1;

	Seconds = time(&MyTime);	/* randomize RIOT timer (in RIOT.ASM)*/
}

/* 
** Init C Variables every time emulator() is called.
**
** called from init.asm
*/

void InitCVars(void)
{
	int i;

	VBlankOff=0;
	VBlankOn=0;
	LinesInFrame=262;
	BailoutLine=500;	/* 320, 360, 380 */
	for (i=0; i<KEYTABLESIZE; i++) KeyTable[i] = 0;
	p0_mask = 0xff;
	p1_mask = 0xff;
	m0_mask = 0xff;
	m1_mask = 0xff;
	pf_mask = 0xff;
	
	memset(RiotRam, 0, sizeof(RiotRam));
	memset(TIA, 0, sizeof(TIA));
	memset(Ram, 0, sizeof(Ram));
	
	Frame = 0;
	PrevFrame = 0;
	VBlanking = -1;		/* 0 if vblanking, -1 otherwise */
	VBlank = 0;			/* VBlank flag */
	VSyncFlag = 0;		/* VSync flag */

	ScanLine = 1;		/* Current scan line */
	OurBailoutLine = 500; /* Initial bailout line (fine tune if exceeded) */
	
	WByte = 0;

	DisplayPointer = (dw*) ScreenBuffer;
}


/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

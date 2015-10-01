/*
** globals.c
*/

#include <string.h>
#include <3DS.h>
#include "globals.h"

double	ctrticks = 0;
double	Ticks = 0.0;
double	FirstFlipTime = 0.0;
double  PrevFrametime = 0;

db isN3DS = 0;
int	Flips = 0;
int	FPSflips = 0;
double	CurrentFPS = 0.0;
double	FPStime = 0.0;
dd FPSLimit = 0xffffffff;  // !0
dd DrawHack_Skipcols = 0; // o3ds hack to gain some FPS - Draws only odd columns 
dd DrawHack_Blankpix = 0; // o3ds hack to gain some FPS - Do not draw blank rows

int screen_width = 0;	/* physical width */
int screen_height = 0;	/* physical height */
int screen_bpp = 32;		/* bits per pixel */
int tiawidth = 320;		/* # of pixels per scanline generated by TIA engine */
int pixelspread = 1;	/* how many times to replicate the tia pixels */
int scanlinespread = 1;	/* how many display lines per scanline */
int lines2draw = 1;		/* how many display lines to draw */

int MessageCode=0;		/* gets message code for final output */
int status_timer = -1;	/* Counts down once per frame while status is shown,
						   status disappears when it's -1 again. */
int CartSize=0;			/* gets cart size */

/* Masks (used for disabling graphics objects) */
db p0_mask = 0xff;
db p1_mask = 0xff;
db m0_mask = 0xff;
db m1_mask = 0xff;
db bl_mask = 0xff;
db pf_mask = 0xff;

FILE *parmfp = NULL;	// parameter file pointer

dd SQ_Max = 4096;	

dd ChargeTrigger0[4] = {TRIGMAX/2, TRIGMAX/2, TRIGMAX/2, TRIGMAX/2};

dd ChargeCounter = 0;		/* # of lines capacitors have been charging */

db InputLatch[2] = {0, 0};	/* INPT4 + INPT5 */

db CM_Collumn = 0;			/* Compumate key collumn to read - gets set by bankswitching */

int ResetEmulator = 0;
int StartInGUI = 0;
int LaunchedFromCommandline = 0;

int UserBankswitch = 0;			/* -gN user specified bankswitch type */
int BSType = 0;					/* override bankswitching type *EST* */

int Frame = 0;		/* Frame counter */
int PrevFrame = 0;	/* Previous value of frame counter */

int VBlanking = 0;	/* 0 if vblanking, -1 otherwise */
int VBlank = 0;		/* VBlank flag */
int VSyncFlag = 0;	/* VSync flag */

int ScanLine = 0;	/* Current scan line */
int OurBailoutLine = 0; /* Initial bailout line (fine tune if exceeded) */

db WByte = 0;		/* byte to write */

/* variables from CPU emulation - used in tracing too */

dw reg_pc = 0;		/*  program counter */
db reg_sp = 0;		/*  stack pointer */
db reg_a = 0;		/*  accumulator (stored in AL) */
db flag_C = 0;		/*  carry bit   (stored in AH) */
db reg_x = 0;		/*  x register */
db reg_y = 0;		/*  y register */
db flag_Z = 0;		/*  zero test value (Z set when 0) */
db flag_N = 0;		/*  sign test value (N set when negative) */
db flag_D = 0;		/*  decimal flag */
db flag_V = 0;		/*  overflow flag */
db flag_I = 0;		/*  interrupt disable flag */
db flag_B = 0;		/*  break flag */
db RCycles = 0;		/*  cycles per instruction */
db RClock = 0;		/*  clock cycles */

db TriggerWSYNC = 0;	/* TIA tells CPU to pause on next read cycle */




/*
** reinitialize the global variables
*/

void def_LoadDefaults(void)
{
	FPSLimit = 1;
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
	FullScreen = 0; // 1;
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
	ShowLineCount = 1;
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
	BailoutLine=320; // 500;	/* 320, 360, 380 */
//	for (i=0; i<KEYTABLESIZE; i++) KeyTable[i] = 0;
	KeyTable = 0;
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
	OurBailoutLine = 340; //500; /* Initial bailout line (fine tune if exceeded) */
	
	WByte = 0;

	DisplayPointer = (dw*) gfxGetFramebuffer(GFX_TOP, GFX_LEFT, NULL, NULL);

	FrameSkip_Counter = 0;	/* Frame skip counter */
	FrameSkip_Value = 0;	/* Frame skip parameter */
	PrevFrametime = 0;

}


/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

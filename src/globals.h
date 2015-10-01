/*
** globals.h
*/

#ifndef __GLOBALS_H__
#define __GLOBALS_H__

#include <stdio.h> 
#include <time.h>

#define Z26_RELEASE "z26 3DS - Atari 2600 Emulator"

typedef unsigned int			dd;		/* define double */
typedef unsigned short int		dw;		/* define word */
typedef unsigned char			db;		/* define byte */

#define TICKS_PER_MSEC (268.123480)

#define TICKS_PER_SEC (268123480.0)
#define TICKS_PER_FRAME_PAL (TICKS_PER_SEC/50.0)
#define TICKS_PER_FRAME_NTSC (TICKS_PER_SEC/60.0)
double  Ticks_per_Frame;


double	ctrticks;
double	Ticks;
double	FirstFlipTime;
dd FPSLimit;

db isN3DS;

dd FrameSkip_Counter;	/* Frame skip counter */
dd FrameSkip_Value;		/* Frame skip parameter */
dd DrawHack_Skipcols;
dd DrawHack_Blankpix;

int	Flips;
int	FPSflips;
double	CurrentFPS;
double	FPStime;
double  PrevFrametime;

int screen_width;
int screen_height;
int screen_bpp;
int tiawidth;
int pixelspread;
int scanlinespread;
int lines2draw;

/* controller code definitions */
#define JS 0	/* joystick */
#define PC 1	/* paddle controller */
#define KP 2	/* keypad */
#define DC 3	/* driving controller */
#define LG 4	/* lightgun */
#define CM 5	/* Compumate keyboard */
#define KV 6	/* Kid Vid tape player */
#define ML 7	/* Mindlink */
#define ST 8	/* ST mouse / CX-80 TRAK Ball */
#define TB 9	/* CX-22 TRAK Ball */
#define AM 10	/* Amiga mouse */
#define NC 11	/* no controller connected */

FILE *zlog;

int MessageCode;		/* gets message code for final output */
char msg[1000];			/* message buffer */
char stat_msg[100];		/* status message buffer */
int status_timer;		/* Counts down once per frame while status is shown,
						   status disappears when it's -1 again. */

int CartSize;			/* gets cart size */

db CartRom[0x8000f];
db PCXPalette[384];		/* palette information goes here */

//db *ScreenBuffer;			/* pointer to screen buffer (set to RealScreenBuffer 1-4) */
//db *ScreenBufferPrev;		/* pointer to screen buffer for previous frame (RSB 1-4)*/
//db *PrevScreenBuffer;		/* previous pointer to screen buffer */
//db *PrevScreenBufferPrev; /* previous pointer to previous screen buffer */

dd LinesInFrame;		/* # of lines in last frame */
dd PrevLinesInFrame;	/* # of lines in frame before that */
dd VBlankOff;			/* a valid VBlankOff was detected here */
dd VBlankOn;			/* a valid VBlankOn was detected here */
dd MaxLines;			/* # of lines in this video mode */
dd BailoutLine;			/* auto-sync occurs if game goes past this line */

dd SC_StartAddress;		/* supercharger start address */
db SC_ControlByte;		/* supercharger control byte */

dd crc;					/* holds accumulated CRC */

/* Masks (used for disabling graphics objects) */
db p0_mask;
db p1_mask;
db m0_mask;
db m1_mask;
db bl_mask;
db pf_mask;

FILE *parmfp;	// parameter file pointer

#define KEYTABLESIZE 512

//db KeyTable[KEYTABLESIZE];	/* event handler should tell z26 about keystrokes here */
dw KeyTable;	/* event handler should tell z26 about keystrokes here */

/* event handler should tell z26 about joystick states here */
int JoystickAxis[16][6];
db JoystickButton[16][32];
db Stelladaptor[16];	/* is joystick a Stealladaptor */

db ShowFPS;
db SoundQ[65537];		/* sound queue */
dd SQ_Max;

dd *RealScreenBuffer1;

/* make the output buffers big enough for 500 scanlines with tiawidth of 320 */
//db *RealScreenBuffer1[320*501];
//db RealScreenBuffer2[320*501];
//db RealScreenBuffer3[320*501];
//db RealScreenBuffer4[320*501];

//dd texture_buffer[1024*1024];

/* paddle charges (can be 1-240) */

#define TRIGMIN 1
#define TRIGMAX 240

dd ChargeTrigger0[4];

#define CHARGEMAX 0x800000;	/* don't charge capacitors over this value (MAIN.ASM)*/
dd ChargeCounter;		/* # of lines capacitors have been charging */

db InputLatch[2];	/* INPT4 + INPT5 */

db CM_Collumn;			/* Compumate key collumn to read - gets set by bankswitching */

int ExitEmulator;			/* leave the emulator when ESC or backslash are pressed */
int GamePaused;				/* toggle to pause emulator */
int GameReallyPaused;		/* ... it's a little bit complicated by the GUI */

int ResetEmulator;
int StartInGUI;
int LaunchedFromCommandline;

time_t MyTime;				/* structure used by the timer function to return 'Seconds' */
int Seconds;				/* seconds since 1.1.1970 - used to randomize RIOT timer */


/*
** The following variables are typically set by command line switches.
** They are reinitialized at startup and from the GUI.
** The GUI reinitializes them before reading command line parms.
*/

int UserLeftController;		/* -)  user specified left controller */
int LeftController;			/* controller in left port */

int UserRightController;		/* -(  user specified right controller */
int RightController;			/* controller in Right port */

int UserBankswitch;			/* -gN user specified bankswitch type */
int BSType;					/* override bankswitching type *EST* */

int UserPaletteNumber;		/* -cN user specified palette number */
int GamePaletteNumber;		/* game specific palette */
int PaletteNumber;			/* 0 = NTSC, 1 = PAL */

int UserDepth;				/* user specified Depthescence */
int Depth;					/* Depthescence */

int UserAllowAll4;			/* user specified allow all 4 directions on the joystick simultaniously */
int AllowAll4;				/* allow all 4 directions on the joystick simultaniously */

int UserSwapPortsFlag;		/* user specified port 0 to be swapped with port 1 */
int SwapPortsFlag;			/* controller port 0 to be swapped with port 1 */

int VideoMode;				/* default video mode */
int FullScreen;				/* run game full screen */
int Narrow;					/* width adjustment */
int Tall;					/* height adjustment */
int SimColourLoss;			/* simulate PAL colour loss *EST* */
int DoInterlace;			    /* simulate interlaced display *EST* */
int DoScanline;				/* do scanlines effect */

int GameOffset;				/* game specific vertical offset */
int CFirst;					/* first game line to display (zero has VBlank trigger a new frame) */
int OldCFirst;				/* remember original CFirst (for homing the display) */

db quiet;					/* set if we want no sound */
int dsp;						/* do digital signal processing */

int UserP0Diff;				/* user specified player zero difficulty */
int UserP1Diff;				/* user specified player one difficulty */
int UserConsoleBW;			/* user specified console forced to B/W */

db IOPortA;					/* IO Port A (joystick) */
db IOPortA_Controllers;		/* remember controller data throughout frame */
db IOPortA_UnusedBits;		/* bits unused by selected controller = 1 */
db IOPortA_Write;			/* value written to SWCHA */
db IOPortB;					/* IO Port B (switches) */

int UserPaddleSensitivity;
int PaddleSensitivity;		/* keyboard sensitivity for paddle emulation */

int UserTraceCount;
int TraceCount;				/* gets trace count */
int OldTraceCount;			/* for saving trace count if we turn off tracing */

int UserTraceEnabled;
int TraceEnabled;			/* if trace is enabled */

int UserMouseBaseX;
int UserMouseBaseY;
int MouseBaseX;				/* paddle to emulate with mouse X axis (0ffH = joystick) *EST* */
int MouseBaseY;				/* paddle to emulate with mouse Y axis (0ffH = joystick) *EST* */

char UserLightgun;
char UserLGadjust;
int Lightgun;				/* emulate lightgun and adjust horizontally *EST* */
int LGadjust;				/* adjust lightgun vertically *EST* */

int ShowLineCount;			/* display stats on game exit */
int theme;					/* color theme for GUI */
db KidVid;					/* ID byte on tapes for KidVid game *EST* */
db KidVidTape;				/* tape number to be played *EST* */
int MouseRude;				/* warp the mouse when running in a window */
int GrabInput; 				/* Grab keyboard/mouse? */
int PaddleAdjust;			/* wait for N lines before starting to evaluate paddle charge */

int UserJoystickEnabled;		/* user wants the joystick enabled */
int JoystickEnabled;			/* allow PC joystick input for VCS controllers with multiple PC inputs */
int MouseEnabled;			/* allow PC mouse input for VCS controllers with multiple PC inputs */
int KeyboardEnabled;			/* allow PC keyboard input for VCS controllers with multiple PC inputs */
int StelladaptorEnabled;		/* allow PC Stelladaptor input for VCS controllers with multiple PC inputs */

/*
** reinitialize the above variables
*/

void def_LoadDefaults(void);

// C-engine specific

void (* ReadAccess[0x10000])(void);
void (* WriteAccess[0x10000])(void);
void (* TIARIOTReadAccess[0x1000])(void);
void (* TIARIOTWriteAccess[0x1000])(void);

db RiotRam[128];	/* RIOT RAM (must be zero initially) */
db TIA[64];			/* TIA registers (also zeroed) */
db Ram[32768];		/* Extra RAM (used or not depends on bankswitch scheme) */

int Frame;		/* Frame counter */
int PrevFrame;	/* Previous value of frame counter */

int VBlanking;	/* 0 if vblanking, -1 otherwise */
int VBlank;		/* VBlank flag */
int VSyncFlag;	/* VSync flag */

int ScanLine;	/* Current scan line */
int OurBailoutLine; /* Initial bailout line (fine tune if exceeded) */

db WByte;		/* byte to write */

dw *DisplayPointer; // should init to RealScreenBuffer 
dd posinline;

#define CYCLESPERSCANLINE 76
#define TRIGMIN 1

db DataBus;			/* state of the data bus - used for  moving data to and from the CPU emu */
dw AddressBus;		/* state of the address bus - used for read and write accesses */
void (* ReadROMAccess)(void);	/* the bankswitching read handlers will be called though this */
void (* WriteROMAccess)(void);	/* the bankswitching write handlers will be called through this */

/* variables from CPU emulation - used in tracing too */

dw reg_pc;		/*  program counter */
db reg_sp;		/*  stack pointer */
db reg_a;		/*  accumulator (stored in AL) */
db flag_C;		/*  carry bit   (stored in AH) */
db reg_x;		/*  x register */
db reg_y;		/*  y register */
db flag_Z;		/*  zero test value (Z set when 0) */
db flag_N;		/*  sign test value (N set when negative) */
db flag_D;		/*  decimal flag */
db flag_V;		/*  overflow flag */
db flag_I;		/*  interrupt disable flag */
db flag_B;		/*  break flag */
db RCycles;		/*  cycles per instruction */
db RClock;		/*  clock cycles */

db TriggerWSYNC;	/* TIA tells CPU to pause on next read cycle */


/* 
** Init C Variables every time emulator() is called.
**
** called from init.asm
*/

void InitCVars(void);

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

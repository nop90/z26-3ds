/*
	controls.c -- handle 2600 controllers
*/

#ifndef __CONTROLS_H__
#define __CONTROLS_H__

#include <3ds.h>

#include "globals.h"


/* define control keys */

#define P1Left 		KEY_LEFT
#define P1Right 	KEY_RIGHT
#define P1Up 		KEY_UP
#define P1Down 		KEY_DOWN
#define P1Fire 		KEY_A

#define ResetKey 	KEY_START
#define SelectKey 	KEY_SELECT
#define BWKey		0 // KeyF3
#define ColorKey 	0 // KeyF4
#define P0Easy 		KEY_X
#define P0Hard 		KEY_Y

#define P1Easy 		0 // KeyF7
#define P1Hard 		0 // KeyF8


#define P1TriggerBG 	0 // KeySlash
#define P1BoosterBG 	0 // KeyRShift


#define P2Left 		0 // KeyS
#define P2Right 	0 // KeyF
#define P2Up 		0 // KeyE
#define P2Down 		0 // KeyD
#define P2Fire 		0 // KeyN
#define P2TriggerBG 	0 // KeyB
#define P2BoosterBG 	0 // KeyV


#define P1Pad1 		0 // Key7
#define P1Pad2 		0 // Key8
#define P1Pad3 		0 // Key9
#define P1Pad4 		0 // KeyU
#define P1Pad5 		0 // KeyI
#define P1Pad6 		0 // KeyO
#define P1Pad7 		0 // KeyJ
#define P1Pad8 		0 // KeyK
#define P1Pad9 		0 // KeyL
#define P1PadStar 	0 // KeyM		// * 
#define P1Pad0 		0 // KeyComma
#define P1PadPound 	0 // KeyDot		// # 

#define P2Pad1 		0 // Key1
#define P2Pad2 		0 // Key2
#define P2Pad3 		0 // Key3
#define P2Pad4 		0 // KeyQ
#define P2Pad5 		0 // KeyW
#define P2Pad6 		0 // KeyE
#define P2Pad7 		0 // KeyA
#define P2Pad8 		0 // KeyS
#define P2Pad9 		0 // KeyD
#define P2PadStar 	0 // KeyZ		// * 
#define P2Pad0 		0 // KeyX
#define P2PadPound 	0 // KeyC		// #


#define MJ_Threshold 2

unsigned char DCTable[4] = {0x0f, 0x0d, 0x0c, 0x0e};
db MLG_ShotCycle = 0;	/* cycle and line of hit - gets */
dd MLG_ShotLine = 0;	/*   checked from cpuhand.asm */

void SwapPorts();
void DoBoosterGrip_L();
void DoBoosterGrip_R();
void DoJoystick_L();
void DoJoystick_R();
void DoPaddle_L();
void DoPaddle_R();
void DoKeypad_L();
void DoKeypad_R();
void DoDriving_L();
void DoDriving_R();
void TestLightgunHit(dd RClock, dd ScanLine);
void DoLightgun_L();
void DoLightgun_R();
void DoCompumate_L();
void DoCompumate_R();

/*
** *JTZ* KidVid variables:
** TODO: "EJECT" tape when reset is pressed
*/

#define KVSMURFS 0x44
#define KVBBEARS 0x48
#define KVBLOCKS 6		/* number of bytes / block */
#define KVBLOCKBITS KVBLOCKS*8	/* number of bits / block */

//db KidVidStatus	= 0;
dd KidVidIdx = 0;
db KidVidBlock = 0;
db KidVidBlockIdx = 0;

/* number of blocks on tape: */
db KVBlocks[6] = 	{2+40,	2+21,  2+35,  /* Smurfs tapes 3, 1, 2 */
			42+60, 42+78, 42+60}; /* BBears tapes 1, 2, 3 (40 extra blocks for intro)*/

db KVData[6*8] =
{
/* KVData44 */
0x7b,	// 0111 1011b	; (1)0
0x1e,	// 0001 1110b	; 1
0xc6,	// 1100 0110b	; 00
0x31,	// 0011 0001b	; 01
0xec,	// 1110 1100b	; 0
0x60,	// 0110 0000b	; 0+

/* KVData48 */
0x7b,	// 0111 1011b	; (1)0
0x1e,	// 0001 1110b	; 1
0xc6,	// 1100 0110b	; 00
0x3d,	// 0011 1101b	; 10
0x8c,	// 1000 1100b	; 0
0x60,	// 0110 0000b	; 0+

/* KVData00 */
0xf6,	// 1111 0110b
0x31,	// 0011 0001b
0x8c,	// 1000 1100b
0x63,	// 0110 0011b
0x18,	// 0001 1000b
0xc0,	// 1100 0000b

/* KVData01 */
0xf6,	// 1111 0110b
0x31,	// 0011 0001b
0x8c,	// 1000 1100b
0x63,	// 0110 0011b
0x18,	// 0001 1000b
0xf0,	// 1111 0000b

/* KVData02 */
0xf6,	// 1111 0110b
0x31,	// 0011 0001b
0x8c,	// 1000 1100b
0x63,	// 0110 0011b
0x1e,	// 0001 1110b
0xc0,	// 1100 0000b

/* KVData03 */
0xf6,	// 1111 0110b
0x31,	// 0011 0001b
0x8c,	// 1000 1100b
0x63,	// 0110 0011b
0x1e,	// 0001 1110b
0xf0,	// 1111 0000b

/* KVPause */
0x3f,	// 0011 1111b
0xf0,	// 1111 0000b
0x00,	// 0000 0000b
0x00,	// 0000 0000b
0x00,	// 0000 0000b
0x00,	// 0000 0000b

/* KVData80 */
0xf7,	// 1111 0111b	; marks end of tape (green/yellow screen)
0xb1,	// 1011 0001b
0x8c,	// 1000 1100b
0x63,	// 0110 0011b
0x18,	// 0001 1000b
0xc0	// 1100 0000b
};

void DoKidVid_L();

void DoKidVid_R();

//db MindlinkOR = 0x80;		/* set data bit */
//db MindlinkAND = 0x3f;	/* clear Mindlink-connected bit */
//db MindlinkTEST = 0x10;	/* test next out-bit signal */
dd MindlinkPos_L = 0x2800;	/* position value in Mindlink controller */
				/* gets transferred bitwise (16 bits) */
dd MindlinkPos_R = 0x2800;
dd MindlinkShift_L = 1;		/* which bit to transfer next */
dd MindlinkShift_R = 1;		/* which bit to transfer next */


void NextMindlinkBit_L();

void NextMindlinkBit_R();

void DoMindlink_L();
void DoMindlink_R();

db TrakBallController = 0;	/* Do we use any TrakBall type controller */
dd TrakBallCountV = 0;		/* how many new vertical values this frame */
dd TrakBallCountH = 0;		/* how many new horizontal values this frame */
dd TrakBallLinesV = 1;		/* how many lines to wait before sending new vert val */
dd TrakBallLinesH = 1;		/* how many lines to wait before sending new horz val */
dd TrakBallLeft = 0;		/* was TrakBall moved left or moved right instead */
dd TrakBallDown = 0;		/* was TrakBall moved down or moved up instead */
db TrakBallTableST_V[4] = {0x00, 0x10, 0x30, 0x20};		/* ST mouse / CX-80 */
db TrakBallTableST_H[4] = {0x00, 0x80, 0xc0, 0x40};		/* ST mouse / CX-80 */
db TrakBallTableAM_V[4] = {0x00, 0x80, 0xa0, 0x20};		/* Amiga mouse */
db TrakBallTableAM_H[4] = {0x00, 0x10, 0x50, 0x40};		/* Amiga mouse */
db TrakBallTableTB_V[2][2] = {{0x00, 0x10},{0x20, 0x30}};	/* CX-22 */
db TrakBallTableTB_H[2][2] = {{0x40, 0x00},{0xc0, 0x80}};	/* CX-22 */

void UpdateTrakBall(dd ScanLine);
void CalculateTrakBall();

void DoMouseST_L();

void DoMouseST_R();

void DoTrakball_L();

void DoTrakball_R();

void DoMouseAmiga_L();

void DoMouseAmiga_R();

void InitCompuMate();

void DoCompuMate_LR();

void DoNoController_L();

void DoNoController_R();

void ControlSWCHAWrite();

void Controls();

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the
	GNU General Public License Version 2 (GPL).  
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

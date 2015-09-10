/*
	z26 command line stuff
*/

/*
	load next Starpath Rom
*/

#ifndef __CLI_H__
#define __CLI_H__

#include "globals.h"

#define SC_LOAD0_SAVE 515330    // where in ROM buffer to save Load 0

void cli_LoadNextStarpath(void);
void cli_ReloadStarpath(void);

#define CRC16_REV 0xA001		/* CRC-16 polynomial reversed */
#define CRC32_REV 0xA0000001	/* CRC-32 polynomial reversed */

dd crcrevhware(dd data, dd genpoly, dd accum);
void ucrc(dd data);
int cli_calc_CRC(char *filename);
int cli_LoadROM(char *filename);


char cli_controllers[12][3] =
	{"JS","PC","KP","DC","LG","CM","KV","ML","ST","TB","AM","NC"};

int GetController(char *p);
void cli_InterpretParm(char *p);
void cli_WriteParms(int argc, char *argv[]);
void cli_SaveParms();
void cli_ReadParms(char *Filename);

char FileName[260];
char ROMLoaded = 0; char ROMSeen = 0;

void cli_write_CRC(char *filename);
void cli_CommandLine(int argc, char *argv[]);

#endif

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

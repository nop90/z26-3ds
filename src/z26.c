/*
	z26 -- an Atari 2600 emulator
*/

#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>		// not in vc++ -- must be supplied 
#include <sys/stat.h>
#include <time.h>

#include <unistd.h>		// for chdir

#include <3ds.h>
#include "globals.h"
#include "srv.h"
#include "controls.h"
#include "sound.h"
#include "ct.h"
#include "carts.h"
#include "cli.h"
#include "kidvid.h"
#include "palette.h"
#include "text.h"
#include "pcx.h"
#include "position.h"
#include "gui.h"
#include "2600core.h"

// needed for vc++ -- works on gcc

/*int strcasecmp(const char *s1, const char *s2)
{
	while(tolower(*s1) == tolower(*s2++))
	{
		if(*s1++ == '\0') return 0;
	}
	
	return *(unsigned char *)s1 - *(unsigned char *)(s2 - 1);
}
*/

int total_ticks;
double seconds;

FS_archive sdmcArchive;
Handle dirHandle;

int main() 
{
	
	
//	u8  isN3DS = 0;

//	aptOpenSession();
//	APT_SetAppCpuTimeLimit(NULL, 30); // enables syscore usage
//	aptCloseSession();

//	APT_CheckNew3DS(NULL, &isN3DS);
	
	    // Init console for text output

    sdmcArchive = (FS_archive){ARCH_SDMC, (FS_path){PATH_EMPTY, 1, (u8*)""}};
    FSUSER_OpenArchive(NULL, &sdmcArchive);

	z26_3ds_Init(); // !!
	
//    consoleInit(GFX_BOTTOM, NULL); // !!!!!

	chdir("sdmc://Atari2600") ;

	srand(time(0));
	def_LoadDefaults();
	LaunchedFromCommandline = 0;

	StartInGUI = 1;     
	GamePaused = 1;
	cli_ReadParms("z26.gui");

	c_emulator();		   /* call emulator */

//	if(GrabInput)
//		SDL_WM_GrabInput(SDL_GRAB_OFF);
	
//	if(TraceEnabled && (zlog != NULL)) {
//		fprintf(zlog, "Exiting emulator with status %d\n", MessageCode);
//		fflush(zlog);
//		fclose(zlog);
//	}

	srv_sound_off();

//	SDL_Quit();
	z26_3ds_quit(); // !!

	fflush(parmfp);
	fclose(parmfp);
	
	return 0; //MessageCode;
}                                                         


/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

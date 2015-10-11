/*
** guiframerate.c --  menu
*/

#include <3ds.h>
#include "globals.h"
#include "guiutil.h"
#include "gui.h"

int framerate_current = 0;	/* currently selected GUI option */
int exit_framerate = 0;		/* exit menu */

char show_fps_data[52];
char enable_fpslimit_data[52];
char frameskip_data[52];


/* Handlers. You may be more familiar with the term `callback': that's what these are. */

void hand_show_fps() {
	ShowLineCount = !ShowLineCount;
	set_yesno_string(show_fps_data, ShowLineCount);
}

void hand_enable_fpslimit() {
	FPSLimit = !FPSLimit;
	set_yesno_string(enable_fpslimit_data, FPSLimit);
}

void FrameSkip_inc() {
	if (FrameSkip_Value < 9) FrameSkip_Value++;
	else FrameSkip_Value = 9;
	sprintf(frameskip_data, "%d", FrameSkip_Value);
}

void FrameSkip_dec() {
	if (FrameSkip_Value > 0) FrameSkip_Value--;
	else FrameSkip_Value = 0;
	sprintf(frameskip_data, "%d", FrameSkip_Value);
}

void hand_framerate_exit() {
	exit_framerate = 1;
}

gui_entry framerate_gui_items[] = {
	{ " FPS limiter........: %s ", enable_fpslimit_data, 0, hand_enable_fpslimit, hand_enable_fpslimit },
	{ " Show FPS...........: %s ", show_fps_data, 0, hand_show_fps, hand_show_fps },
	{ " Frameskip..........: %s ", frameskip_data, 0, FrameSkip_inc, FrameSkip_dec },
	{ " ", NULL, 0, NULL, NULL },
	{ " Exit ", NULL, 0, hand_framerate_exit, NULL },
	{ NULL, NULL, 0, NULL, NULL } // last element must always be this
};


/* Main entry point. Called by gui() */

void framerate_gui() {
//	SDL_Event ev;
    u32 keys; 
	int action;
	
	set_yesno_string(show_fps_data, ShowLineCount);
	set_yesno_string(enable_fpslimit_data, FPSLimit);
	sprintf(frameskip_data, "%d", FrameSkip_Value);

	
	exit_framerate = 0;
	while( !exit_framerate ) {
		status_timer = 0;

		sprintf(msg, "FPS Options");
		draw_gui(framerate_gui_items, framerate_current);
		
//		SDL_WaitEvent(&ev);	/* TODO: respond to SDL_QUIT events */
		hidScanInput();
		while(!hidKeysHeld()) hidScanInput();
		keys = hidKeysHeld();
		action = gui_navigation(keys); //&ev);
		if(action == GUI_NO_ACTION) continue;
		
		framerate_current = gui_handle_action(action, &exit_framerate, framerate_gui_items, framerate_current);
	}
}



/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

/*
** gui.c -- graphical user interface
*/

/* 20040530 bkw */

#include <string.h>
#include <3ds.h>
#include "gui.h"
#include "srv.h"
#include "flip.h"
#include "cli.h"
#include "video.h"

#include "guiutil.h"
#include "gui_sort.h"
#include "guifilelist.h"
#include "guiframerate.h"
#include "guigame.h"
#include "guisound.h"
#include "guitweaks.h"
#include "guiinterface.h"

#define GUI_WIDTH 38
#define FONT_WIDTH 6
#define FONT_HEIGHT 9


/*** global variables */

int exit_gui = 0;	/* handlers set this to 1 to exit the GUI */
int gui_current = 0;	/* currently selected GUI option */

gui_entry *current_gui_items = NULL;

void gui_SetVideoMode()
{
db TempVideoMode;

	TempVideoMode = VideoMode;
	VideoMode &= 3;
	srv_SetVideoMode();
	VideoMode = TempVideoMode;
}

void run_rom()
{
	if(ROMLoaded) 
	{
		cli_SaveParms();		// save parameters
		def_LoadDefaults();		// <---
		StartInGUI = 1;			// <--- not a good default
		
		cli_ReadParms("z26.gui");
		OldPaletteNumber = UserPaletteNumber;
		srv_SetPalette();
		strncpy(FileName, newfile, 255);
		exit_gui = 1;
		GamePaused = 0;
		srv_reset_timing();
	} 
}

void hand_load_rom() 
{
	int picked;
	
	ROMLoaded = 0;
	
	while (!ROMLoaded)
	{
		picked = file_selector(newfile);
		if(!picked) return;
		ROMLoaded = cli_LoadROM(newfile);
	}
	run_rom();
	ResetEmulator = 1;	// let's always do this before running a game
}

void resume_rom() {
	if(GameReallyPaused) {
		GamePaused = 0;			// resume game 
		GameReallyPaused = 0;
		exit_gui = 1;
		srv_reset_timing();		
	} 
}
void hand_exit() {

	ExitEmulator = 128;		
	exit_gui = 1;
	GamePaused = 0;
}

/* The main GUI menu. See the definition of gui_entry above. */
gui_entry gui_items[] = {
	{ " Select a Game ", NULL, 0, hand_load_rom, NULL },
	{ " Resume Game", NULL, 0, resume_rom, NULL },
	{ " ", NULL, 0, NULL, NULL },
	{ " FPS ", NULL, 0, framerate_gui, NULL },
	{ " Game ", NULL, 0, game_gui, NULL },
	{ " Sound ", NULL, 0, sound_gui, NULL },
	{ " Interface ", NULL, 0, interface_gui, NULL },
	{ " Ctrl Tweaks ", NULL, 0, tweaks_gui, NULL },
//	{ " ", NULL, 0, NULL, NULL },
	{ " Exit ", NULL, 0, hand_exit, NULL },
	{ NULL, NULL, 0, NULL, NULL }		// last element must always be this
};


/* Main entry point. Called by Controls() in controls.c, if we're in GUI mode. */

void gui() {
//	SDL_Event ev;   
    u32 keys; 

	int old_js_state;
	int action;
	
	gui_SetVideoMode();
	
//	ResetEmulator = 1;	// let's always do this before running a game

	OldPaletteNumber = PaletteNumber;
	if (PaletteNumber != UserPaletteNumber)
	{
		PaletteNumber = UserPaletteNumber;
		srv_SetPalette();
	}

	/* Turn on key repeat for the gui */
//	SDL_EnableKeyRepeat(SDL_DEFAULT_REPEAT_DELAY, SDL_DEFAULT_REPEAT_INTERVAL);

	if(current_gui_items == NULL)
	{
		current_gui_items = gui_items;
	}
	else
	{
		if(!ROMLoaded) 
		{
			hand_load_rom(KEY_A) ; //SDLK_RETURN);
			if(ROMLoaded) return;
		}
	}
	
//	old_js_state = SDL_JoystickEventState(SDL_QUERY);
//	SDL_JoystickEventState(SDL_ENABLE);

	exit_gui = 0;
	while( !exit_gui ) {
		status_timer = 0;
		sprintf(msg,"%s", Z26_RELEASE);
		draw_gui(current_gui_items, gui_current);
//		SDL_WaitEvent(&ev);		/* TODO: respond to SDL_QUIT events */
		hidScanInput();
		while(!hidKeysHeld()) hidScanInput();
		keys = hidKeysHeld();
		action = gui_navigation(keys); // &ev);
		if(action == GUI_NO_ACTION) continue;
		
		gui_current = gui_handle_action(action, &exit_gui, current_gui_items, gui_current);

	}

	/* for now, GamePaused controls whether we're in the GUI or not. */
	if(ROMLoaded)
	{
		GamePaused = 0;
		srv_reset_timing();
	}
	else
	{
		hand_exit();
	}

	/* Turn off key repeat for the game */
//	SDL_EnableKeyRepeat(0, 0);

	/* restore the old joystick event state. */
//	SDL_JoystickEventState(old_js_state);

	cli_SaveParms();			// save parameters

	srv_SetVideoMode();
	PaletteNumber = OldPaletteNumber;
	srv_SetPalette();
}

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

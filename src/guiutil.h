/*
** guiutil.c --gui utility functions
*/

#ifndef __GUIUTIL_H__
#define __GUIUTIL_H__

#include "globals.h"

/* gui_action is an abstraction layer between SDL_Event and gui code.
	This allows both gui() and file_selector() (and later on whatever
	else we have) to use the same set of key/joystick bindings. See
	gui_navigate(). If we ever allow gui key remapping, gui_navigate()
	is where the map will be applied. */
	
typedef enum {
	GUI_NO_ACTION,
	GUI_UP,
	GUI_DOWN,
	GUI_PAGEUP,
	GUI_PAGEDOWN,
	GUI_HOME,
	GUI_END,
	GUI_ACTIVATE_PRI,
	GUI_ACTIVATE_SEC,
	GUI_RANDOM,
	GUI_EXIT_GUI
} gui_action;

/* gui_entry is a struct that represents a GUI menu option.

	label is the text, which must be less than GUI_WIDTH chars. It may
	contain one %s, which will be replaced by the data (uses sprintf())

	data is NULL for a menu item with no options (like `Resume Emulator'),
	or else the string value of the currently-selected option (such as
	"Yes" or "No" for e.g. `Show FPS' option). If you like, you can think
	of an item with options as a drop-down or radio list, and an item
	with no options as a button.

	Handlers are callbacks that actually perform the menu functions.
	They are declared to return void and accept no parameters.

	Each gui_entry has one primary handler (or NULL if no handler is
	desired) which will get called whenever the user presses (Enter,
	space, rightarrow, joybutton0, or joystick-right) and optionally
	a secondary handler which will get called when the user presses
	leftarrow, joybutton1, or joystick-left. If no secondary handler
	is desired, set sec_handler to NULL.

	It is possible to define a gui_entry with a NULL primary handler and
	an actual callable sec_handler. Please don't do this, it will only
	make the GUI confusing and serves no useful purpose.

	handlers must never assume that they're the only ones that can change
	a value: there are still keystrokes that can change values while the
	emulator is running (e.g. alt-enter for fullscreen/window).
*/
typedef struct {
	char *label;
	char *data;
	int disabled;
	void (*handler)();
	void (*sec_handler)();
} gui_entry;


void set_yesno_string(char *str, int yesno);
gui_action gui_navigation(dd keys);
int set_gui_height(gui_entry *menu);
int gui_handle_action(int action, int *ptr_exit_gui, gui_entry *current_gui_items, int gui_current);
void draw_gui(gui_entry *entries, int cur);

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

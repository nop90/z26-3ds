/*
** guisound.c --  menu
*/

#ifndef __GUISOUND_H__
#define __GUISOUND_H__

int sound_current;	/* currently selected GUI option */
int exit_sound;	/* exit video menu */

char quiet_data[52];
char dsp_data[52];
char sq_data[52];

void set_dsp_string();
void hand_dsp_inc();
void hand_dsp_dec();
void set_sq_string() ;
void hand_sq_inc();
void hand_sq_dec();
void hand_quiet();
void hand_sound_exit();
void sound_gui();

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

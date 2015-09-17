/*
** sdlsound.h
*/

#ifndef __SOUND_H__
#define __SOUND_H__

#include "globals.h"

dd SQ_resample;	/* a counter for mixing sound to 44100 Hz */

db SQ_byte;	/* byte to put in the sound queue */
db *SQ_Input;	/* pointer to next available byte for storing */
db *SQ_Output;	/* pointer to next available byte for fetching */
db *SQ_Top;	/* pointer to the top of the queue */


static int sound_is_on;


void Init_SoundQ();
int SQ_Count();
int SQ_Test();
void SQ_Store();
void fillerup(void *unused, db *stream, int len);
void srv_sound_on();
void srv_sound_off();

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

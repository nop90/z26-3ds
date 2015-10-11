/*
** sdlsound.c -- SDL sound code
*/

#include <3ds.h>
#include <string.h>
#include "globals.h"
#include "sound.h"

#define SOUND_FREQUENCY	44100
#define SOUND_BUFFER_SIZE	8192


static int sound_is_on = 0;
u8 *stream;
u32 bufferpos;


void Init_SoundQ() 
{
	SQ_resample = 5;
	SQ_Input = SoundQ;
	SQ_Output = SoundQ;
	SQ_Top = SoundQ + SQ_Max;
    stream = (u8*)linearAlloc(SOUND_BUFFER_SIZE);
	bufferpos=0;

}

int SQ_Count() {
	int count = SQ_Input - SQ_Output;

	if (count < 0) count += SQ_Max;
	return(count);
}

int SQ_Test()
{
	int count = SQ_Count();
	
	if(count >= SQ_Max-4) return -1; 	/* full (with a little slop for resampling) */
	if(count <= SQ_Max/2) return 0; 	/* less than 1/2 full */
	return 1; 							/* just right */
}

/*
** Please make sure calls to SQ_Store() check for a full buffer first.
*/

void SQ_Store() 
{
	*SQ_Input++ = SQ_byte;
	if(SQ_Input >= SQ_Top) SQ_Input = SoundQ;
}

/*
** the callback function
*/

void fillerup(void *unused, db *stream, int len)
{
	int count = SQ_Count();
		
	if(count < len) 
	{
		memset(stream, 0, len);
	}
	else
	{
		while(len)	
		{
			stream[bufferpos++] = *SQ_Output++;
			len--;
			if(SQ_Output >= SQ_Top) SQ_Output = SoundQ;
			if(bufferpos >= SOUND_BUFFER_SIZE) bufferpos = 0;
		}
	}
}

void srv_sound_on()
{
	SQ_Output = SoundQ;
	bufferpos = 0;
	sound_is_on = 1;

}

void srv_sound_off()
{
	sound_is_on = 0;
}

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

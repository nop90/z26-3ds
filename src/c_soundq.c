/*
**	z26 sound stuff
*/

#include "globals.h"
#include "kidvid.h"

void QueueSoundByte() {
	SampleByte = 0;				/* default kidvid sample */
	if(KidVid) kv_GetNextSampleByte();	/* this routine puts byte into SampleByte */
	SQ_byte = (TIA_Sound_Byte() + SampleByte) >> 1;
	
	SQ_resample--;
	if (SQ_resample == 2) SQ_Store();
	if (SQ_resample == 0)
	{
		SQ_resample = 5;
		SQ_Store();
	}
	
	SQ_Store();
}


/* Put sound bytes into buffer.
	Called once per scan line.
*/
void QueueSoundBytes() {
	if (quiet) return;
	if (SQ_Test() == -1) return;
	do {
		QueueSoundByte();
		QueueSoundByte();
	} while(SQ_Test() == 0);
}


/**
 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/


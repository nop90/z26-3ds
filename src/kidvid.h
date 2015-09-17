/*
** Kid Vid sample file loading routines
*/


/*
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

#ifndef __KIDVID_H__
#define __KIDVID_H__

#include "globals.h"

FILE *SampleFile, *SharedSampleFile;
db SampleByte;
int FileOpened;
dd kv_TapeBusy;
int kv_FilePointer, kv_SharedData, kv_Beep;
unsigned long int kv_SongCounter;


unsigned char SongPositions[44+38+42+62+80+62];

unsigned long int SongStart[104];

void kv_OpenSampleFile(void);
void kv_CloseSampleFile(void);
void kv_SetNextSong(void);
void kv_GetNextSampleByte(void);

#endif
/*
** Kid Vid sample file loading routines
*/


/*
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the 
** GNU General Public License Version 2 (GPL).	z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/

#include "globals.h"
#include "kidvid.h"

void kv_OpenSampleFile(void)
{
char kvNameTable[6][9] =
   {"kvs3.wav", "kvs1.wav", "kvs2.wav", "kvb3.wav", "kvb1.wav", "kvb2.wav"};
int StartSong[6] = {44+38, 0, 44, 44+38+42+62+80, 44+38+42, 44+38+42+62};
int i;
   if(!FileOpened){
      if(KidVid==0x44) i=0;
      else i=3;
      i=i+KidVidTape-1;
      if(KidVidTape==4) i=i-3;

      if(quiet==0){
         SampleFile=fopen(&kvNameTable[i][0], "rb");
         if(SampleFile!=NULL){
            SharedSampleFile=fopen("kvshared.wav", "rb");
            if(SharedSampleFile==NULL){
               fclose(SampleFile);
               FileOpened=0;
            }else{
               FileOpened=1;
               fseek(SampleFile, 45, SEEK_SET);
            }
         }else FileOpened=0;
      }else FileOpened=0;

      kv_SongCounter=0;
      kv_TapeBusy=0;
      kv_FilePointer=StartSong[i];
   }
}

void kv_CloseSampleFile(void)
{
   if(FileOpened){
      fclose(SampleFile);
      fclose(SharedSampleFile);
      FileOpened=0;
   }
}

void kv_SetNextSong(void)
{
unsigned char Temp;
   if(FileOpened){
      if(SongPositions[kv_FilePointer] & 0x80) kv_Beep=0;
      else kv_Beep=1;
      Temp=SongPositions[kv_FilePointer] & 0x7f;
      if(Temp<10) kv_SharedData=1;
      else kv_SharedData=0;
      kv_SongCounter=((unsigned long int)(SongStart[Temp+1]-SongStart[Temp]));
      if(kv_SharedData) fseek(SharedSampleFile, SongStart[Temp], SEEK_SET);
      else fseek(SampleFile, SongStart[Temp], SEEK_SET);
      kv_FilePointer++;
      kv_TapeBusy=1;
   }else{
      kv_Beep=1;
      kv_TapeBusy=1;
      kv_SongCounter=80*262;    /* delay needed for Harmony without tape */
   }
}

void kv_GetNextSampleByte(void)
{
static int oddeven = 0;
   if(kv_SongCounter==0) SampleByte = (db) 0x80;
   else{
      oddeven=oddeven^1;
      if(oddeven&1){
         kv_SongCounter--;
         if((kv_SongCounter>262*48)||(kv_Beep==0)) kv_TapeBusy=1;
         else kv_TapeBusy=0;
         if(FileOpened){
            if(kv_SharedData) SampleByte=getc(SharedSampleFile);
            else SampleByte=getc(SampleFile);
         }else SampleByte = (db) 0x80;
         if((kv_Beep==0)&&(kv_SongCounter==0)) kv_SetNextSong();
      }
   }
}


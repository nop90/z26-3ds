/*
** ctrflip.c -- 3DS page flipping code - 3DS port complete
*/

#include <3ds.h>
#include "globals.h"
#include "srv.h"

double srv_get_microseconds()
{
	double ticks;
	
	ctrticks = svcGetSystemTick();
	ticks = ctrticks/TICKS_PER_MSEC;
	return(ticks);
}

void srv_sleep_microseconds(double wait_time)
{
	svcSleepThread((dd) wait_time*1000.0);
}

void srv_reset_timing()
{
	Flips = 0;
	Ticks = 0.0;			/* reset timing calculation */
//	FirstFlipTime = 0.0;
	CurrentFPS = 0.0;
	FPStime = 0.0;
	FPSflips = 0;

	Ticks = svcGetSystemTick();
	FPStime = Ticks;
	PrevFrame = Ticks;
}

void srv_Flip()
{
	double Now = svcGetSystemTick();
	
	if(FPSLimit && (Now - PrevFrametime < Ticks_per_Frame)) 
	{
		svcSleepThread(Ticks_per_Frame - (Now - PrevFrametime));
		Now = svcGetSystemTick();
		PrevFrametime += Ticks_per_Frame;
	} else
		PrevFrametime = Now;

	Flips++;
	++FPSflips;
	++FrameSkip_Counter;

	if (Now - FPStime > TICKS_PER_SEC)	// update FPS every 1 second
	{	
		CurrentFPS = FPSflips; // (FPSflips * TICKS_PER_SEC)/(Now - FPStime);
		FPStime = Now;
		FPSflips = 0;
	}
	
	if(FrameSkip_Counter>FrameSkip_Value) FrameSkip_Counter = 0;

}

/**
	z26 is Copyright 1997-2011 by John Saeger and contributors.  
	z26 is released subject to the terms and conditions of the 
	GNU General Public License Version 2 (GPL).	
	z26 comes with no warranty.
	Please see COPYING.TXT for details.
*/

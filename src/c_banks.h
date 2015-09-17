/*
** banks.c -- z26 bank switch stuff
*/

#ifndef __BANKS_H__
#define __BANKS_H__

#include "globals.h"

db Starpath;
db Pitfall2;

dd RomBank; /* Rom bank pointer for F8 & F16 */
/* take lower 4 bit of address and subtract this to get bank number */
dd HotspotAdjust;

/* Parker Brother's ROM Slices */

dd PBSlice0;
dd PBSlice1;
dd PBSlice2;

/* Tigervision 3E, 3F and 3F+ ROM Slices */

dd TVSlice0;
dd TVSlice1;
dd ROMorRAM3E;

/* M-Network RAM Slices */

dd MNRamSlice; /* which 256 byte ram slice */

/* CompuMate RAM state */

dd CMRamState; /*  RAM enabled - read/write state */

/* John Payson's (supercat) 4A50 ROM slices */

dd Bank4A50Low;	/* pointer for $1000-$17ff slice */
dd ROMorRAMLow;	/* 0 = ROM -- 1 = RAM at $1000-$17ff */
dd Bank4A50Middle;	/* pointer for $1800-$1dff slice */
dd ROMorRAMMiddle;	/* 0 = ROM -- 1 = RAM at $1800-$1dff */
dd Bank4A50High;	/* pointer for $1e00-$1eff slice */
dd ROMorRAMHigh;	/* 0 = ROM -- 1 = RAM at $1e00-$1eFF */
db LastDataBus4A50;	/* state of DataBus on last cycle */
dd LastAddressBus4A50;	/* state of AddressBus on last cycle */

void (* InitMemoryMap[24])(void);

void Copy64K(void);
void ReadROM2K(void);
void ReadROM4K(void);
void WriteROM4K(void);
void ReadBSFE(void);
void ReadBS4K(void);
void ReadHotspotBS4K(void);
void WriteHotspotBS4K(void);
void ReadHotspotUA(void);
void WriteHotspotUA(void);
void ReadHotspotMB(void);
void WriteHotspotMB(void);
void ReadRAM128(void);
void WriteRAM128(void);
void ReadRAM256(void);
void WriteRAM256(void);
void ReadRAM1K(void);
void WriteRAM1K(void);
void ReadCMhigh(void);
void WriteHotspotCM(void);
void Init4K(void);
void InitCV(void);
void InitF8SC(void);
void ReadHotspotE0_B0(void);
void WriteHotspotE0_B0(void);
void ReadHotspotE0_B1(void);
void WriteHotspotE0_B1(void);
void ReadHotspotE0_B2(void);
void WriteHotspotE0_B2(void);
void ReadBSE0_B0(void);
void ReadBSE0_B1(void);
void ReadBSE0_B2(void);
void ReadBSE0_B3(void);
void InitE0(void);
void ReadBS3Flow(void);
void ReadBS3Fhigh(void);
void WriteHotspot3F(void);
void Init3F(void);
void InitFE(void);
void InitF6SC(void);
void ReadBSE7(void);
void WriteBSE7(void);
void ReadBSE7RAM(void);
void WriteBSE7RAM(void);
void ReadBSE7last(void);
void ReadHotspotBSE7ROM(void);
void WriteHotspotBSE7ROM(void);
void ReadHotspotBSE7RAM(void);
void WriteHotspotBSE7RAM(void);
void InitE7(void);
void InitF4SC(void);
void InitF8(void);
void InitCM(void);
void InitUA(void);
void InitEF(void);
void ReadBS3Elow(void);
void WriteBS3E(void);
void WriteHotspot3E_E(void);
void WriteHotspot3E_F(void);
void Init3E(void);
void InitSP(void);
void InitF6(void);
void InitF4(void);
void InitMB(void);
void InitFA(void);
void InitP2(void);
void RBank4A50(void);
void WBank4A50(void);
void Init0840(void);


void DetectBySize();
void SetupBanks();

#endif
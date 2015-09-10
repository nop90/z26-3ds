/*

	tialine.c -- generate a raster line


	magic numbers:

		HBLANK starts at zero, ends at 67.
		Left Playfield starts at 68, ends at 147.
		Right Playfield starts at 148, ends at 227.
		HMOVE blank starts at 68, ends at 75.

 z26 is Copyright 1997-2011 by John Saeger and contributors.  
 contributors.	 z26 is released subject to the terms and conditions of the 
 GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
 Please see COPYING.TXT for details.
*/

#include <stdlib.h>
#include "globals.h"
#include "text.h"
#include "position.h"
#include "c_soundq.h"
#include "c_tialine.h"
#include "c_cpu.h"

void Init_TIA(void){
	
	int	i, j, k, l, m, n;

	TIACollide = 0;	// reset collision latches

 	for(i = 0; i < 0x2001; i++){
		TIA_P0_Table[i] = malloc(160);
		if(TIA_P0_Table[i] == NULL){
			sprintf(msg, "Not enough memory available to run z26.\n");
			srv_print(msg);
			exit(1);
		}
		TIA_P1_Table[i] = malloc(160);
		if(TIA_P1_Table[i] == NULL){
			sprintf(msg, "Not enough memory available to run z26.\n");
			srv_print(msg);
			exit(1);
		}
		for(j = 0; j < 160; j++){
			TIA_P0_Table[i][j] = 0;
			TIA_P1_Table[i][j] = 0;
		}
		switch(i & 0x100f){
			case 0x0000:
			// one copy, close spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
					}
				}
			break;
			case 0x0001:
			// two copies, close spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
					}
				}
			break;
			case 0x0002:
			// two copies, medium spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x0003:
			// three copies, close spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x0004:
			// two copies, far spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x0005:
			// one copy, close spacing, single width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j * 2 + 6] = 0x20;
//						TIA_P0_Table[i][j * 2 + 7] = 0x20;
//						TIA_P1_Table[i][j * 2 + 6] = 0x10;
//						TIA_P1_Table[i][j * 2 + 7] = 0x10;
					}
				}
			break;
			case 0x0006:
			// three copies, medium spacing, double width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x0007:
			// one copy, close spacing, quadrouple width,
			// not reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
//						TIA_P0_Table[i][j * 4 + 6] = 0x20;
//						TIA_P0_Table[i][j * 4 + 7] = 0x20;
//						TIA_P0_Table[i][j * 4 + 8] = 0x20;
//						TIA_P0_Table[i][j * 4 + 9] = 0x20;
//						TIA_P1_Table[i][j * 4 + 6] = 0x10;
//						TIA_P1_Table[i][j * 4 + 7] = 0x10;
//						TIA_P1_Table[i][j * 4 + 8] = 0x10;
//						TIA_P1_Table[i][j * 4 + 9] = 0x10;
					}
				}
			break;
			case 0x0008:
			// one copy, close spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
					}
				}
			break;
			case 0x0009:
			// two copies, close spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
					}
				}
			break;
			case 0x000a:
			// two copies, medium spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x000b:
			// three copies, close spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x000c:
			// two copies, far spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x000d:
			// one copy, close spacing, single width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j * 2 + 6] = 0x20;
						TIA_P0_Table[i][j * 2 + 7] = 0x20;
						TIA_P1_Table[i][j * 2 + 6] = 0x10;
						TIA_P1_Table[i][j * 2 + 7] = 0x10;
					}
				}
			break;
			case 0x000e:
			// three copies, medium spacing, double width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x000f:
			// one copy, close spacing, quadrouple width,
			// not reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0800 >> j)){
						TIA_P0_Table[i][j * 4 + 6] = 0x20;
						TIA_P0_Table[i][j * 4 + 7] = 0x20;
						TIA_P0_Table[i][j * 4 + 8] = 0x20;
						TIA_P0_Table[i][j * 4 + 9] = 0x20;
						TIA_P1_Table[i][j * 4 + 6] = 0x10;
						TIA_P1_Table[i][j * 4 + 7] = 0x10;
						TIA_P1_Table[i][j * 4 + 8] = 0x10;
						TIA_P1_Table[i][j * 4 + 9] = 0x10;
					}
				}
			break;
			case 0x1000:
			// one copy, close spacing, single width,
			// reflected, don't show first copy
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
					}
				}
			break;
			case 0x1001:
			// two copies, close spacing, single width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
					}
				}
			break;
			case 0x1002:
			// two copies, medium spacing, single width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x1003:
			// three copies, close spacing, single width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x1004:
			// two copies, far spacing, single width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x1005:
			// one copy, close spacing, single width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j * 2 + 6] = 0x20;
//						TIA_P0_Table[i][j * 2 + 7] = 0x20;
//						TIA_P1_Table[i][j * 2 + 6] = 0x10;
//						TIA_P1_Table[i][j * 2 + 7] = 0x10;
					}
				}
			break;
			case 0x1006:
			// three copies, medium spacing, double width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
//						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x1007:
			// one copy, close spacing, quadrouple width,
			// reflected, don't show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
//						TIA_P0_Table[i][j * 4 + 6] = 0x20;
//						TIA_P0_Table[i][j * 4 + 7] = 0x20;
//						TIA_P0_Table[i][j * 4 + 8] = 0x20;
//						TIA_P0_Table[i][j * 4 + 9] = 0x20;
//						TIA_P1_Table[i][j * 4 + 6] = 0x10;
//						TIA_P1_Table[i][j * 4 + 7] = 0x10;
//						TIA_P1_Table[i][j * 4 + 8] = 0x10;
//						TIA_P1_Table[i][j * 4 + 9] = 0x10;
					}
				}
			break;
			case 0x1008:
			// one copy, close spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
					}
				}
			break;
			case 0x1009:
			// two copies, close spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
					}
				}
			break;
			case 0x100a:
			// two copies, medium spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x100b:
			// three copies, close spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 16] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 16] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
					}
				}
			break;
			case 0x100c:
			// two copies, far spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x100d:
			// one copy, close spacing, single width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j * 2 + 6] = 0x20;
						TIA_P0_Table[i][j * 2 + 7] = 0x20;
						TIA_P1_Table[i][j * 2 + 6] = 0x10;
						TIA_P1_Table[i][j * 2 + 7] = 0x10;
					}
				}
			break;
			case 0x100e:
			// three copies, medium spacing, double width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j + 5] = 0x20;
						TIA_P0_Table[i][j + 5 + 32] = 0x20;
						TIA_P0_Table[i][j + 5 + 64] = 0x20;
						TIA_P1_Table[i][j + 5] = 0x10;
						TIA_P1_Table[i][j + 5 + 32] = 0x10;
						TIA_P1_Table[i][j + 5 + 64] = 0x10;
					}
				}
			break;
			case 0x100f:
			// one copy, close spacing, quadrouple width,
			// reflected, show first copy 
				for(j = 0; j < 8; j++){
					if(i & (0x0010 << j)){
						TIA_P0_Table[i][j * 4 + 6] = 0x20;
						TIA_P0_Table[i][j * 4 + 7] = 0x20;
						TIA_P0_Table[i][j * 4 + 8] = 0x20;
						TIA_P0_Table[i][j * 4 + 9] = 0x20;
						TIA_P1_Table[i][j * 4 + 6] = 0x10;
						TIA_P1_Table[i][j * 4 + 7] = 0x10;
						TIA_P1_Table[i][j * 4 + 8] = 0x10;
						TIA_P1_Table[i][j * 4 + 9] = 0x10;
					}
				}
			break;
		}
	}

	for(i = 0; i < 0x81; i++){
		TIA_M0_Table[i] = malloc(160);
		if(TIA_M0_Table[i] == NULL){
			sprintf(msg, "Not enough memory available to run z26.\n");
			srv_print(msg);
			exit(1);
		}
		TIA_M1_Table[i] = malloc(160);
		if(TIA_M1_Table[i] == NULL){
			sprintf(msg, "Not enough memory available to run z26.\n");
			srv_print(msg);
			exit(1);
		}
		for(j = 0; j < 160; j++){
			TIA_M0_Table[i][j] = 0;
			TIA_M1_Table[i][j] = 0;
		}
	}

	l = 1;
	for(i = 0; i < 8; i++){
		for(k = 0; k < 4; k++){
			for(n = 0; n < 4; n++){
				j = Object_Table[i][n];
				for(m = 0; m < l; m++){
					if(j){
						TIA_M0_Table[0x48 + (k << 4) + i][j + m] = 0x08;
						TIA_M1_Table[0x48 + (k << 4) + i][j + m] = 0x04;
					}
					if(j > 4){
						TIA_M0_Table[0x40 + (k << 4) + i][j + m] = 0x08;
						TIA_M1_Table[0x40 + (k << 4) + i][j + m] = 0x04;
					}
				}
			}
			l = l * 2;
		}
		l = 1;
	}
	for(i = 0; i < 9; i++){
		TIA_BL_Table[i] = malloc(160);
		if(TIA_BL_Table[i] == NULL){
			sprintf(msg, "Not enough memory available to run z26.\n");
			srv_print(msg);
			exit(1);
		}
		for(j = 0; j < 160; j++){
			TIA_BL_Table[i][j] = 0;
		}
	}

	TIA_BL_Table[4][4] = 0x02;

	TIA_BL_Table[5][4] = 0x02;
	TIA_BL_Table[5][5] = 0x02;

	TIA_BL_Table[6][4] = 0x02;
	TIA_BL_Table[6][5] = 0x02;
	TIA_BL_Table[6][6] = 0x02;
	TIA_BL_Table[6][7] = 0x02;

	TIA_BL_Table[7][4] = 0x02;
	TIA_BL_Table[7][5] = 0x02;
	TIA_BL_Table[7][6] = 0x02;
	TIA_BL_Table[7][7] = 0x02;
	TIA_BL_Table[7][8] = 0x02;
	TIA_BL_Table[7][9] = 0x02;
	TIA_BL_Table[7][10] = 0x02;
	TIA_BL_Table[7][11] = 0x02;

	Pointer_Index_P0 = 0;
	Pointer_Index_P1 = 0;
	Pointer_Index_M0 = 0;
	Pointer_Index_M1 = 0;
	Pointer_Index_BL = 0;

	TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
	TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
	TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
	TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
	TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
	
	TIA_Mask_Objects = 0x3f;	// display all objects

	for(i = 0; i < 8; i++){
		for(j = 0; j < 320; j++) ObjectStartTable[i][j] = 0;
	
		ObjectStartTable[i][159] = 2;	// 2 to identify main copy for RESMPx
		ObjectStartTable[i][160 + 159] = 2;
	}

	ObjectStartTable[1][15] = 1;
	ObjectStartTable[1][160 + 15] = 1;

	ObjectStartTable[2][31] = 1;
	ObjectStartTable[2][160 + 31] = 1;

	ObjectStartTable[3][15] = 1;
	ObjectStartTable[3][160 + 15] = 1;
	ObjectStartTable[3][31] = 1;
	ObjectStartTable[3][160 + 31] = 1;

	ObjectStartTable[4][63] = 1;
	ObjectStartTable[4][160 + 63] = 1;

	ObjectStartTable[6][31] = 1;
	ObjectStartTable[6][160 + 31] = 1;
	ObjectStartTable[6][63] = 1;
	ObjectStartTable[6][160 + 63] = 1;

/*
	TIA_Pixel_State:
		0x00 background
		0x01 playfield
		0x02 ball
		0x04 missile 1
		0x08 missile 0
		0x10 player 1
		0x20 player 0
		0x40 vblank
*/
	for(i = 0; i < 64; i++){
		// normal priority - P0/M0 - P1/M1 - PF/BL - BG
		TIA_Priority_Table[0][i] = BG_COLOUR;
		if(i & 0x03) TIA_Priority_Table[0][i] = PF_COLOUR;
		if(i & 0x14) TIA_Priority_Table[0][i] = P1_COLOUR;
		if(i & 0x28) TIA_Priority_Table[0][i] = P0_COLOUR;

		// playfield priority - PF/BL - P0/M0 - P1/M1 - BG
		TIA_Priority_Table[1][i] = BG_COLOUR;
		if(i & 0x14) TIA_Priority_Table[1][i] = P1_COLOUR;
		if(i & 0x28) TIA_Priority_Table[1][i] = P0_COLOUR;
		if(i & 0x03) TIA_Priority_Table[1][i] = PF_COLOUR;

		// score mode left half - PF/P0/M0 - P1/M1 - BL - BG
		TIA_Score_Priority_Table[0][i] = BG_COLOUR;
		if(i & 0x02) TIA_Score_Priority_Table[0][i] = PF_COLOUR;
		if(i & 0x14) TIA_Score_Priority_Table[0][i] = P1_COLOUR;
		if(i & 0x29) TIA_Score_Priority_Table[0][i] = P0_COLOUR;

		// score mode right half - P0/M0 - PF/P1/M1 - BL - BG
		TIA_Score_Priority_Table[1][i] = BG_COLOUR;
		if(i & 0x02) TIA_Score_Priority_Table[1][i] = PF_COLOUR;
		if(i & 0x15) TIA_Score_Priority_Table[1][i] = P1_COLOUR;
		if(i & 0x28) TIA_Score_Priority_Table[1][i] = P0_COLOUR;
	}
	
	for(i = 0; i < 64; i++){
		j = 0;
		if((i & 0x30) == 0x30) j |= 0x8000;	// P0 P1
		if((i & 0x0c) == 0x0c) j |= 0x4000;	// M0 M1
		if((i & 0x03) == 0x03) j |= 0x2000;	// BL PF
		if((i & 0x05) == 0x05) j |= 0x0800;	// M1 PF
		if((i & 0x06) == 0x06) j |= 0x0400;	// M1 BL
		if((i & 0x09) == 0x09) j |= 0x0200;	// M0 PF
		if((i & 0x0a) == 0x0a) j |= 0x0100;	// M0 BL
		if((i & 0x11) == 0x11) j |= 0x0080;	// P1 PF
		if((i & 0x12) == 0x12) j |= 0x0040;	// P1 BL
		if((i & 0x21) == 0x21) j |= 0x0020;	// P0 PF
		if((i & 0x22) == 0x22) j |= 0x0010;	// P0 BL
		if((i & 0x24) == 0x24) j |= 0x0008;	// M1 P0
		if((i & 0x14) == 0x14) j |= 0x0004;	// M1 P1
		if((i & 0x18) == 0x18) j |= 0x0002;	// M0 P1
		if((i & 0x28) == 0x28) j |= 0x0001;	// M0 P0
		TIA_Collision_Table[i] = j;
	}
}

void CatchUpPixels(void){

	if(TIA_Do_Output){
		if(TIA_VBLANK){
			for(CountLoop = TIA_Last_Pixel; CountLoop < ((RClock * 3) + TIA_Delayed_Write); CountLoop++){
		 		LoopCount = CountLoop;
				if(LoopCount > 227) LoopCount -= 228;
		
				
				if((LoopCount & 0x03) == 1){
					/* counter at H1 = HIGH */
					if(TIA_HMOVE_Setup == 1) TIA_HMOVE_Setup = 2;
					if(TIA_HMOVE_Latches){
						if(TIA_HMP0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x1e;
						if(TIA_HMP1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x2e;
						if(TIA_HMM0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x36;
						if(TIA_HMM1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3a;
						if(TIA_HMBL_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3c;
					}
				}
				if((LoopCount & 0x03) == 3){
					/* counter at H2 = HIGH */
					TIA_HMOVE_DoMove = TIA_HMOVE_Latches;
					if(TIA_HMOVE_Clock < 16) TIA_HMOVE_Clock++;
					if(TIA_HMOVE_Setup == 2){
						TIA_HMOVE_Setup = 0;
						if(TIA_HMOVE_Clock == 16) TIA_HMOVE_Clock = 0;
							/* only reset if HMOVE isn't already in process */
						TIA_HMOVE_Latches = 0x3e;
							/* enable movement for all 5 objects */
					}
				}

				if(LoopCount > 75){
					
					if(LoopCount == 147){
						
					/*
						we're at the center of the displayed line here
						-> queue a sound byte
						-> test REFPF bit
						-> fix half a pixel of last PF pixel in score mode
					*/
			
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				*DisplayPointer = 0;
				DisplayPointer++;
						 
		
						/* The PF reflect bit gets only checked at center screen. */
						if(CTRLPF_PF_Reflect) TIA_REFPF_Flag = 40;
						else TIA_REFPF_Flag = 0;
		
					}else{
		
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				*DisplayPointer = 0;
				DisplayPointer++;
						
					}	
				}else if(LoopCount < 68){
		
					
					if(TIA_HMOVE_DoMove){
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
						
				}else if(TIA_Display_HBlank){
		
					
			*DisplayPointer = 0;
			DisplayPointer++;
					if(LoopCount == 75) TIA_Display_HBlank = 0;
		
					
					if(TIA_HMOVE_DoMove){
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
		
				}else{
		
					
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				*DisplayPointer = 0;
				DisplayPointer++;
					
				}	
			}
			TIA_Last_Pixel = (RClock * 3) + TIA_Delayed_Write;
		}else{
			for(CountLoop = TIA_Last_Pixel; CountLoop < ((RClock * 3) + TIA_Delayed_Write); CountLoop++){
		 		LoopCount = CountLoop;
				if(LoopCount > 227) LoopCount -= 228;
		
				
				if((LoopCount & 0x03) == 1){
					/* counter at H1 = HIGH */
					if(TIA_HMOVE_Setup == 1) TIA_HMOVE_Setup = 2;
					if(TIA_HMOVE_Latches){
						if(TIA_HMP0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x1e;
						if(TIA_HMP1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x2e;
						if(TIA_HMM0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x36;
						if(TIA_HMM1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3a;
						if(TIA_HMBL_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3c;
					}
				}
				if((LoopCount & 0x03) == 3){
					/* counter at H2 = HIGH */
					TIA_HMOVE_DoMove = TIA_HMOVE_Latches;
					if(TIA_HMOVE_Clock < 16) TIA_HMOVE_Clock++;
					if(TIA_HMOVE_Setup == 2){
						TIA_HMOVE_Setup = 0;
						if(TIA_HMOVE_Clock == 16) TIA_HMOVE_Clock = 0;
							/* only reset if HMOVE isn't already in process */
						TIA_HMOVE_Latches = 0x3e;
							/* enable movement for all 5 objects */
					}
				}

				if(LoopCount > 75){
					
					if(LoopCount == 147){
						
					/*
						we're at the center of the displayed line here
						-> queue a sound byte
						-> test REFPF bit
						-> fix half a pixel of last PF pixel in score mode
					*/
			
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						/* let user disable objects */
					TIA_Pixel_State &= TIA_Mask_Objects;
					/* playfield doesn't use score colouring mode when it has display priority */
					if(CTRLPF_Score){
						/*
							Due to a race condition in the TIA colour encoder the last half
							pixel of the last PF quad in the left screen half will get a
							temperature dependant mix of the P0, P1 and PF colour in score mode.
							We simulate it be setting the colour of that half pixel to PF colour.
						*/
						if(TIA_Pixel_State == 0x01)	/* only playfield active? */
							*DisplayPointer =
								/* TODO: make this endian safe */
								(TIA_Colour_Table[P0_COLOUR] & 0x00ff) | (TIA_Colour_Table[PF_COLOUR] & 0xff00);
						else *DisplayPointer =
							TIA_Colour_Table[TIA_Score_Priority_Table[(LoopCount - 68) / 80][TIA_Pixel_State]];
					}else *DisplayPointer =
						TIA_Colour_Table[TIA_Priority_Table[CTRLPF_Priority][TIA_Pixel_State]];
					
					DisplayPointer++; 
		
						/* The PF reflect bit gets only checked at center screen. */
						if(CTRLPF_PF_Reflect) TIA_REFPF_Flag = 40;
						else TIA_REFPF_Flag = 0;
		
					}else{
		
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						/* let user disable objects */
					TIA_Pixel_State &= TIA_Mask_Objects;
					/* playfield doesn't use score colouring mode when it has display priority */
					if(CTRLPF_Score) *DisplayPointer =
						TIA_Colour_Table[TIA_Score_Priority_Table[(LoopCount - 68) / 80][TIA_Pixel_State]];
					else *DisplayPointer =
						TIA_Colour_Table[TIA_Priority_Table[CTRLPF_Priority][TIA_Pixel_State]];
					
					DisplayPointer++;
					}	
				}else if(LoopCount < 68){
		
					
					if(TIA_HMOVE_DoMove){
						
					TIA_Pixel_State = TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
						
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
						
				}else if(TIA_Display_HBlank){
		
					
			*DisplayPointer = 0;
			DisplayPointer++;
					if(LoopCount == 75) TIA_Display_HBlank = 0;
		
					
					if(TIA_HMOVE_DoMove){
						
					TIA_Pixel_State = TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
						
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
		
				}else{
		
					
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
					/* let user disable objects */
					TIA_Pixel_State &= TIA_Mask_Objects;
					/* playfield doesn't use score colouring mode when it has display priority */
					if(CTRLPF_Score) *DisplayPointer =
						TIA_Colour_Table[TIA_Score_Priority_Table[(LoopCount - 68) / 80][TIA_Pixel_State]];
					else *DisplayPointer =
						TIA_Colour_Table[TIA_Priority_Table[CTRLPF_Priority][TIA_Pixel_State]];
					
					DisplayPointer++;
				}	
			}
			TIA_Last_Pixel = (RClock * 3) + TIA_Delayed_Write;
		}
	}else{
		if(TIA_VBLANK){
			for(CountLoop = TIA_Last_Pixel; CountLoop < ((RClock * 3) + TIA_Delayed_Write); CountLoop++){
		 		LoopCount = CountLoop;
				if(LoopCount > 227) LoopCount -= 228;
		
				
				if((LoopCount & 0x03) == 1){
					/* counter at H1 = HIGH */
					if(TIA_HMOVE_Setup == 1) TIA_HMOVE_Setup = 2;
					if(TIA_HMOVE_Latches){
						if(TIA_HMP0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x1e;
						if(TIA_HMP1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x2e;
						if(TIA_HMM0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x36;
						if(TIA_HMM1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3a;
						if(TIA_HMBL_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3c;
					}
				}
				if((LoopCount & 0x03) == 3){
					/* counter at H2 = HIGH */
					TIA_HMOVE_DoMove = TIA_HMOVE_Latches;
					if(TIA_HMOVE_Clock < 16) TIA_HMOVE_Clock++;
					if(TIA_HMOVE_Setup == 2){
						TIA_HMOVE_Setup = 0;
						if(TIA_HMOVE_Clock == 16) TIA_HMOVE_Clock = 0;
							/* only reset if HMOVE isn't already in process */
						TIA_HMOVE_Latches = 0x3e;
							/* enable movement for all 5 objects */
					}
				}

				if(LoopCount > 75){
					
					if(LoopCount == 147){
						
					/*
						we're at the center of the displayed line here
						-> queue a sound byte
						-> test REFPF bit
						-> fix half a pixel of last PF pixel in score mode
					*/
			
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						 
		
						/* The PF reflect bit gets only checked at center screen. */
						if(CTRLPF_PF_Reflect) TIA_REFPF_Flag = 40;
						else TIA_REFPF_Flag = 0;
		
					}else{
		
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						
					}	
				}else if(LoopCount < 68){
		
					
					if(TIA_HMOVE_DoMove){
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
						
				}else if(TIA_Display_HBlank){
		
					
					if(LoopCount == 75) TIA_Display_HBlank = 0;
		
					
					if(TIA_HMOVE_DoMove){
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
		
				}else{
		
					
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
					
				}	
			}
			TIA_Last_Pixel = (RClock * 3) + TIA_Delayed_Write;
		}else{
			for(CountLoop = TIA_Last_Pixel; CountLoop < ((RClock * 3) + TIA_Delayed_Write); CountLoop++){
		 		LoopCount = CountLoop;
				if(LoopCount > 227) LoopCount -= 228;
		
				
				if((LoopCount & 0x03) == 1){
					/* counter at H1 = HIGH */
					if(TIA_HMOVE_Setup == 1) TIA_HMOVE_Setup = 2;
					if(TIA_HMOVE_Latches){
						if(TIA_HMP0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x1e;
						if(TIA_HMP1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x2e;
						if(TIA_HMM0_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x36;
						if(TIA_HMM1_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3a;
						if(TIA_HMBL_Value == (TIA_HMOVE_Clock & 0x0f)) TIA_HMOVE_Latches &= 0x3c;
					}
				}
				if((LoopCount & 0x03) == 3){
					/* counter at H2 = HIGH */
					TIA_HMOVE_DoMove = TIA_HMOVE_Latches;
					if(TIA_HMOVE_Clock < 16) TIA_HMOVE_Clock++;
					if(TIA_HMOVE_Setup == 2){
						TIA_HMOVE_Setup = 0;
						if(TIA_HMOVE_Clock == 16) TIA_HMOVE_Clock = 0;
							/* only reset if HMOVE isn't already in process */
						TIA_HMOVE_Latches = 0x3e;
							/* enable movement for all 5 objects */
					}
				}

				if(LoopCount > 75){
					
					if(LoopCount == 147){
						
					/*
						we're at the center of the displayed line here
						-> queue a sound byte
						-> test REFPF bit
						-> fix half a pixel of last PF pixel in score mode
					*/
			
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						 
		
						/* The PF reflect bit gets only checked at center screen. */
						if(CTRLPF_PF_Reflect) TIA_REFPF_Flag = 40;
						else TIA_REFPF_Flag = 0;
		
					}else{
		
						
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						
					}	
				}else if(LoopCount < 68){
		
					
					if(TIA_HMOVE_DoMove){
						
					TIA_Pixel_State = TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
						
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
						
				}else if(TIA_Display_HBlank){
		
					
					if(LoopCount == 75) TIA_Display_HBlank = 0;
		
					
					if(TIA_HMOVE_DoMove){
						
					TIA_Pixel_State = TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
						
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
						if(TIA_HMOVE_DoMove & 0x20){					
							
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x10){					
							
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
						}
						if(TIA_HMOVE_DoMove & 0x08){					
							
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x04){					
							
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
						}
						if(TIA_HMOVE_DoMove & 0x02){					
							
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
						}
						TIA_HMOVE_DoMove = 0;
					}	
		
				}else{
		
					
				
					if((LoopCount & 0x03) == 0){
						if(TIA_Playfield_Pixels[(((LoopCount - 68) >> 2) + TIA_REFPF_Flag)] & TIA_Playfield_Bits)
							Current_PF_Pixel = 0x01;
						else Current_PF_Pixel = 0x00;
					};
				
					TIA_Pixel_State = Current_PF_Pixel
					                | TIA_P0_Line_Pointer[TIA_P0_counter]
					                | TIA_P1_Line_Pointer[TIA_P1_counter]
					                | TIA_M0_Line_Pointer[TIA_M0_counter]
					                | TIA_M1_Line_Pointer[TIA_M1_counter]
					                | TIA_BL_Line_Pointer[TIA_BL_counter];
				
					TIA_P0_counter++;
					if(TIA_P0_counter == 160){
						
						TIA_P0_counter = TIA_P0_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP0
							0x0ff0 GRP0_new or GRP0_old value
							0x0008 show first copy of current NUSIZ0
							0x0007 NUSIZ0_number
						*/
						Pointer_Index_P0 = NUSIZ0_number | TIA_REFP0;
						if(TIA_P0_counter_reset == 0) Pointer_Index_P0 |= 0x0008;
						if(TIA_VDELP0) Pointer_Index_P0 |= TIA_GRP0_old;
						else Pointer_Index_P0 |= TIA_GRP0_new;
						
						TIA_P0_Line_Pointer = TIA_P0_Table[Pointer_Index_P0];
						TIA_P0_counter_reset = 0;
					/* TODO: handle RESPM0 here */
					}
				
					TIA_P1_counter++;
					if(TIA_P1_counter == 160){
						
						TIA_P1_counter = TIA_P1_counter_reset;
						/*
							0x2000 = handle hand rendered graphics
							
							0x1000 REFP1
							0x0ff0 GRP1_new or GRP1_old value
							0x0008 show first copy of current NUSIZ1
							0x0007 NUSIZ1_number
						*/
						Pointer_Index_P1 = NUSIZ1_number | TIA_REFP1;
						if(TIA_P1_counter_reset == 0) Pointer_Index_P1 |= 0x0008;
						if(TIA_VDELP1) Pointer_Index_P1 |= TIA_GRP1_old;
						else Pointer_Index_P1 |= TIA_GRP1_new;
						
						TIA_P1_Line_Pointer = TIA_P1_Table[Pointer_Index_P1];
						TIA_P1_counter_reset = 0;
					/* TODO: handle RESPM1 here */
					}
				
					TIA_M0_counter++;
					if(TIA_M0_counter == 160){
						
						TIA_M0_counter = TIA_M0_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM0
							0x30 NUSIZ_M0_width
							0x08 show first copy of current NUSIZ0
							0x07 NUSIZ0_number
						*/
						Pointer_Index_M0 = NUSIZ0_number | NUSIZ_M0_width | TIA_ENAM0;
						if(TIA_M0_counter_reset == 0) Pointer_Index_M0 |= 0x08;
						
						TIA_M0_Line_Pointer = TIA_M0_Table[Pointer_Index_M0];
						TIA_M0_counter_reset = 0;
					}
				
					TIA_M1_counter++;
					if(TIA_M1_counter == 160){
						
						TIA_M1_counter = TIA_M1_counter_reset;
						/*
							0x80 = handle hand rendered graphics
							
							0x40 TIA_ENAM1
							0x30 NUSIZ_M1_width
							0x08 show first copy of current NUSIZ1
							0x07 NUSIZ1_number
						*/
						Pointer_Index_M1 = NUSIZ1_number | NUSIZ_M1_width | TIA_ENAM1;
						if(TIA_M1_counter_reset == 0) Pointer_Index_M1 |= 0x08;
						
						TIA_M1_Line_Pointer = TIA_M1_Table[Pointer_Index_M1];
						TIA_M1_counter_reset = 0;
					}
				
					TIA_BL_counter++;
					if(TIA_BL_counter == 160){
						
						TIA_BL_counter = TIA_BL_counter_reset;
						/*
							0x08 = handle hand rendered graphics
							
							0x04 TIA_ENABL_new or TIA_ENABL_old
							0x03 CTRLPF_BL_width
						*/
						Pointer_Index_BL = CTRLPF_BL_width;
						if(TIA_VDELBL) Pointer_Index_BL |= TIA_ENABL_old;
						else Pointer_Index_BL |= TIA_ENABL_new;
						
						TIA_BL_Line_Pointer = TIA_BL_Table[Pointer_Index_BL];
						TIA_BL_counter_reset = 0;
					}
				
					/* TODO: add support for for PAL colour loss */
					
					TIACollide |= TIA_Collision_Table[TIA_Pixel_State];
					
				}	
			}
			TIA_Last_Pixel = (RClock * 3) + TIA_Delayed_Write;
		}
	}


}

void nTIALineTo(void){

	QueueSoundBytes();	//  put another 2 bytes in the sound queue

	// CFirst and MaxLines ? These need to be set in position.c from tiawrite.c
	if((ScanLine < TopLine) || (ScanLine >= BottomLine)) TIA_Do_Output = 0;
	else TIA_Do_Output = 1;
	do_Instruction_line();
	
//	if((RClock < (2 * CYCLESPERSCANLINE)) && (TIA_Last_Pixel < (RClock * 3))) CatchUpPixels();
	if(TIA_Last_Pixel < (RClock * 3)) CatchUpPixels();
	TIA_Last_Pixel = TIA_Last_Pixel % (CYCLESPERSCANLINE * 3);

/*
	int i;
	if(TIA_Do_Output){
		MyDisplayPointer = (dd*) DisplayPointer;
		TIA_Pixel_PTR = (dw*) &TIA_Pixels[0];
		for(i = 0; i < 80; i++){
			*MyDisplayPointer = TIA_Colours[TIA_Priority[*TIA_Pixel_PTR]];
			*TIA_Pixel_PTR &= 0x4040;
			TIA_Pixel_PTR++;
			MyDisplayPointer++;
		}
		DisplayPointer = (dw*) MyDisplayPointer;
	}
*/
}

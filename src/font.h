/*
** text.c -- text display
*/

#ifndef __FONT_H__
#define __FONT_H__

char simplex5[] =
{
	/* 0000 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0008 */	0x38, 0x44, 0x92, 0xba, 0x92, 0x44, 0x38, 0x00, 
	/* 0010 */	0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 
	/* 0018 */	0x3c, 0x42, 0xa1, 0x91, 0x89, 0x85, 0x42, 0x3c, 
	/* 0020 */	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0028 */	0x00, 0x78, 0x78, 0x7a, 0x7a, 0x02, 0x3e, 0x00, 
	/* 0030 */	0xe0, 0xe8, 0xe8, 0x0a, 0x7a, 0x02, 0x3e, 0x00, 
	/* 0038 */	0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 
	/* 0040 */	0xff, 0x81, 0xbd, 0xbd, 0xbd, 0xbd, 0x81, 0xff, 
	/* 0048 */	0xfe, 0x82, 0x82, 0x82, 0x82, 0x82, 0xfe, 0x00, 
	/* 0050 */	0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x00, 
	/* 0058 */	0xfe, 0x82, 0xaa, 0x92, 0xaa, 0x82, 0xfe, 0x00, 
	/* 0060 */	0xfe, 0x82, 0x8a, 0x92, 0xa2, 0x82, 0xfe, 0x00, 
	/* 0068 */	0x3e, 0x20, 0x3e, 0x20, 0x20, 0x60, 0xe0, 0xc0, 
	/* 0070 */	0x3f, 0x21, 0x3f, 0x21, 0x23, 0x67, 0xe6, 0xc0, 
	/* 0078 */	0x7c, 0x82, 0xba, 0xa2, 0xba, 0x82, 0x7c, 0x00, 
	/* 0080 */	0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
	/* 0088 */	0x10, 0x30, 0x70, 0xf0, 0x70, 0x30, 0x10, 0x00, 
	/* 0090 */	0x20, 0x70, 0xf8, 0x20, 0xf8, 0x70, 0x20, 0x00, 
	/* 0098 */	0xfe, 0x82, 0xba, 0xba, 0xba, 0x82, 0xfe, 0x00, 
	/* 00a0 */	0x06, 0x0c, 0x18, 0xe6, 0xce, 0x9e, 0xfe, 0x00, 
	/* 00a8 */	0x18, 0xa8, 0xc8, 0xe8, 0x08, 0x10, 0x20, 0x00, 
	/* 00b0 */	0x40, 0xa8, 0x98, 0xb8, 0x80, 0x40, 0x20, 0x00, 
	/* 00b8 */	0x20, 0x70, 0xf8, 0x20, 0xf8, 0x70, 0x20, 0x00, 
	/* 00c0 */	0x00, 0x20, 0x70, 0xf8, 0x20, 0x20, 0x00, 0x00, 
	/* 00c8 */	0x00, 0x20, 0x20, 0xf8, 0x70, 0x20, 0x00, 0x00, 
	/* 00d0 */	0x00, 0x20, 0x30, 0xf8, 0x30, 0x20, 0x00, 0x00, 
	/* 00d8 */	0x00, 0x20, 0x60, 0xf8, 0x60, 0x20, 0x00, 0x00, 
	/* 00e0 */	0x08, 0x10, 0x20, 0x20, 0x20, 0x20, 0x40, 0x80, 
	/* 00e8 */	0x00, 0x00, 0x50, 0xf8, 0x50, 0x00, 0x00, 0x00, 
	/* 00f0 */	0x70, 0x88, 0xa8, 0xa8, 0x88, 0x88, 0x88, 0x70, 
	/* 00f8 */	0x70, 0x88, 0xa8, 0x88, 0x88, 0x88, 0x88, 0x70, 
	/* 0100 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0108 */	0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x20, 0x00, 
	/* 0110 */	0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0118 */	0x00, 0x50, 0xf8, 0x50, 0xf8, 0x50, 0x00, 0x00, 
	/* 0120 */	0x20, 0x78, 0xa0, 0x70, 0x28, 0xf0, 0x20, 0x00, 
	/* 0128 */	0x00, 0x88, 0x10, 0x20, 0x40, 0x88, 0x00, 0x00, 
	/* 0130 */	0x60, 0x90, 0x60, 0x98, 0x90, 0x90, 0x68, 0x00, 
	/* 0138 */	0x20, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0140 */	0x10, 0x20, 0x40, 0x40, 0x40, 0x20, 0x10, 0x00, 
	/* 0148 */	0x40, 0x20, 0x10, 0x10, 0x10, 0x20, 0x40, 0x00, 
	/* 0150 */	0x00, 0x88, 0x50, 0xf8, 0x50, 0x88, 0x00, 0x00, 
	/* 0158 */	0x00, 0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00, 
	/* 0160 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 
	/* 0168 */	0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	/* 0170 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 
	/* 0178 */	0x00, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 
	/* 0180 */	0x70, 0x88, 0x88, 0xa8, 0x88, 0x88, 0x70, 0x00, 
	/* 0188 */	0x20, 0x60, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 
	/* 0190 */	0x70, 0x88, 0x08, 0x10, 0x20, 0x40, 0xf8, 0x00, 
	/* 0198 */	0x70, 0x88, 0x08, 0x30, 0x08, 0x88, 0x70, 0x00, 
	/* 01a0 */	0x90, 0x90, 0x90, 0xf8, 0x10, 0x10, 0x10, 0x00, 
	/* 01a8 */	0xf8, 0x80, 0x80, 0xf0, 0x08, 0x88, 0x70, 0x00, 
	/* 01b0 */	0x70, 0x80, 0x80, 0xf0, 0x88, 0x88, 0x70, 0x00, 
	/* 01b8 */	0xf8, 0x08, 0x08, 0x10, 0x20, 0x40, 0x40, 0x00, 
	/* 01c0 */	0x70, 0x88, 0x88, 0x70, 0x88, 0x88, 0x70, 0x00, 
	/* 01c8 */	0x70, 0x88, 0x88, 0x78, 0x08, 0x08, 0x70, 0x00, 
	/* 01d0 */	0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 
	/* 01d8 */	0x00, 0x20, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 
	/* 01e0 */	0x00, 0x10, 0x20, 0x40, 0x20, 0x10, 0x00, 0x00, 
	/* 01e8 */	0x00, 0x00, 0xf8, 0x00, 0x00, 0xf8, 0x00, 0x00, 
	/* 01f0 */	0x00, 0x40, 0x20, 0x10, 0x20, 0x40, 0x00, 0x00, 
	/* 01f8 */	0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, 0x00, 
	/* 0200 */	0x70, 0x88, 0xa8, 0xa8, 0x90, 0x80, 0x78, 0x00, 
	/* 0208 */	0x70, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x00, 
	/* 0210 */	0xf0, 0x88, 0x88, 0xf0, 0x88, 0x88, 0xf0, 0x00, 
	/* 0218 */	0x78, 0x80, 0x80, 0x80, 0x80, 0x80, 0x78, 0x00, 
	/* 0220 */	0xf0, 0x88, 0x88, 0x88, 0x88, 0x88, 0xf0, 0x00, 
	/* 0228 */	0xf8, 0x80, 0x80, 0xe0, 0x80, 0x80, 0xf8, 0x00, 
	/* 0230 */	0xf8, 0x80, 0x80, 0xf0, 0x80, 0x80, 0x80, 0x00, 
	/* 0238 */	0x78, 0x80, 0x80, 0x98, 0x88, 0x88, 0x70, 0x00, 
	/* 0240 */	0x88, 0x88, 0x88, 0xf8, 0x88, 0x88, 0x88, 0x00, 
	/* 0248 */	0x70, 0x20, 0x20, 0x20, 0x20, 0x20, 0x70, 0x00, 
	/* 0250 */	0x78, 0x08, 0x08, 0x08, 0x08, 0x08, 0xf0, 0x00, 
	/* 0258 */	0x88, 0x90, 0xa0, 0xc0, 0xa0, 0x90, 0x88, 0x00, 
	/* 0260 */	0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xf8, 0x00, 
	/* 0268 */	0x88, 0xd8, 0xa8, 0x88, 0x88, 0x88, 0x88, 0x00, 
	/* 0270 */	0x88, 0xc8, 0xa8, 0x98, 0x88, 0x88, 0x88, 0x00, 
	/* 0278 */	0x70, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 
	/* 0280 */	0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 0x80, 0x00, 
	/* 0288 */	0x70, 0x88, 0x88, 0x88, 0xa8, 0x90, 0x68, 0x00, 
	/* 0290 */	0xf0, 0x88, 0x88, 0xf0, 0xa0, 0x90, 0x88, 0x00, 
	/* 0298 */	0x78, 0x80, 0x80, 0x70, 0x08, 0x08, 0xf0, 0x00, 
	/* 02a0 */	0xf8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 
	/* 02a8 */	0x88, 0x88, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 
	/* 02b0 */	0x88, 0x88, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 
	/* 02b8 */	0x88, 0x88, 0x88, 0x88, 0xa8, 0xd8, 0x88, 0x00, 
	/* 02c0 */	0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00, 
	/* 02c8 */	0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00, 
	/* 02d0 */	0xf8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xf8, 0x00, 
	/* 02d8 */	0x70, 0x40, 0x40, 0x40, 0x40, 0x40, 0x70, 0x00, 
	/* 02e0 */	0x00, 0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 
	/* 02e8 */	0x70, 0x10, 0x10, 0x10, 0x10, 0x10, 0x70, 0x00, 
	/* 02f0 */	0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 
	/* 02f8 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfc, 
	/* 0300 */	0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0308 */	0x00, 0x00, 0x70, 0x08, 0x78, 0x88, 0x78, 0x00, 
	/* 0310 */	0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00, 
	/* 0318 */	0x00, 0x00, 0x78, 0x80, 0x80, 0x80, 0x78, 0x00, 
	/* 0320 */	0x08, 0x08, 0x78, 0x88, 0x88, 0x88, 0x78, 0x00, 
	/* 0328 */	0x00, 0x00, 0x70, 0x88, 0xf8, 0x80, 0x70, 0x00, 
	/* 0330 */	0x38, 0x40, 0x40, 0xf8, 0x40, 0x40, 0x40, 0x00, 
	/* 0338 */	0x00, 0x00, 0x70, 0x88, 0x88, 0x78, 0x08, 0x70, 
	/* 0340 */	0x80, 0x80, 0xf0, 0x88, 0x88, 0x88, 0x88, 0x00, 
	/* 0348 */	0x00, 0x20, 0x00, 0x20, 0x20, 0x20, 0x20, 0x00, 
	/* 0350 */	0x00, 0x08, 0x00, 0x08, 0x08, 0x08, 0x08, 0x70, 
	/* 0358 */	0x80, 0x80, 0x88, 0x90, 0xe0, 0x90, 0x88, 0x00, 
	/* 0360 */	0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x30, 0x00, 
	/* 0368 */	0x00, 0x00, 0x50, 0xa8, 0xa8, 0x88, 0x88, 0x00, 
	/* 0370 */	0x00, 0x00, 0xf0, 0x88, 0x88, 0x88, 0x88, 0x00, 
	/* 0378 */	0x00, 0x00, 0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 
	/* 0380 */	0x00, 0x00, 0xf0, 0x88, 0x88, 0xf0, 0x80, 0x80, 
	/* 0388 */	0x00, 0x00, 0x78, 0x88, 0x88, 0x78, 0x08, 0x08, 
	/* 0390 */	0x00, 0x00, 0x78, 0x80, 0x80, 0x80, 0x80, 0x00, 
	/* 0398 */	0x00, 0x00, 0x78, 0x80, 0x70, 0x08, 0xf0, 0x00, 
	/* 03a0 */	0x00, 0x40, 0xf8, 0x40, 0x40, 0x40, 0x38, 0x00, 
	/* 03a8 */	0x00, 0x00, 0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 
	/* 03b0 */	0x00, 0x00, 0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 
	/* 03b8 */	0x00, 0x00, 0x88, 0x88, 0xa8, 0xa8, 0x50, 0x00, 
	/* 03c0 */	0x00, 0x00, 0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 
	/* 03c8 */	0x00, 0x00, 0x88, 0x88, 0x50, 0x20, 0x40, 0x80, 
	/* 03d0 */	0x00, 0x00, 0xf8, 0x10, 0x20, 0x40, 0xf8, 0x00, 
	/* 03d8 */	0x30, 0x20, 0x20, 0x40, 0x20, 0x20, 0x30, 0x00, 
	/* 03e0 */	0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 
	/* 03e8 */	0x60, 0x20, 0x20, 0x10, 0x20, 0x20, 0x60, 0x00, 
	/* 03f0 */	0x68, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 03f8 */	0x00, 0x00, 0x20, 0x50, 0x88, 0x88, 0xf8, 0x00, 
	/* 0400 */	0x0a
};

char tiny5[] =
{
	/* 0000 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0008 */	0x38, 0x44, 0x92, 0xba, 0x92, 0x44, 0x38, 0x00, 
	/* 0010 */	0x38, 0x44, 0x82, 0x82, 0x82, 0x44, 0x38, 0x00, 
	/* 0018 */	0x3c, 0x42, 0xa1, 0x91, 0x89, 0x85, 0x42, 0x3c, 
	/* 0020 */	0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
	/* 0028 */	0x00, 0x78, 0x78, 0x7a, 0x7a, 0x02, 0x3e, 0x00, 
	/* 0030 */	0xe0, 0xe8, 0xe8, 0x0a, 0x7a, 0x02, 0x3e, 0x00, 
	/* 0038 */	0xff, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff, 
	/* 0040 */	0xff, 0x81, 0xbd, 0xbd, 0xbd, 0xbd, 0x81, 0xff, 
	/* 0048 */	0xfe, 0x82, 0x82, 0x82, 0x82, 0x82, 0xfe, 0x00, 
	/* 0050 */	0x00, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x7e, 0x00, 
	/* 0058 */	0xfe, 0x82, 0xaa, 0x92, 0xaa, 0x82, 0xfe, 0x00, 
	/* 0060 */	0xfe, 0x82, 0x8a, 0x92, 0xa2, 0x82, 0xfe, 0x00, 
	/* 0068 */	0x3e, 0x20, 0x3e, 0x20, 0x20, 0x60, 0xe0, 0xc0, 
	/* 0070 */	0x3f, 0x21, 0x3f, 0x21, 0x23, 0x67, 0xe6, 0xc0, 
	/* 0078 */	0x7c, 0x82, 0xba, 0xa2, 0xba, 0x82, 0x7c, 0x00, 
	/* 0080 */	0x80, 0xc0, 0xe0, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 
	/* 0088 */	0x10, 0x30, 0x70, 0xf0, 0x70, 0x30, 0x10, 0x00, 
	/* 0090 */	0x20, 0x70, 0xf8, 0x20, 0xf8, 0x70, 0x20, 0x00, 
	/* 0098 */	0xfe, 0x82, 0xba, 0xba, 0xba, 0x82, 0xfe, 0x00, 
	/* 00a0 */	0x06, 0x0c, 0x18, 0xe6, 0xce, 0x9e, 0xfe, 0x00, 
	/* 00a8 */	0x18, 0xa8, 0xc8, 0xe8, 0x08, 0x10, 0x20, 0x00, 
	/* 00b0 */	0x40, 0xa8, 0x98, 0xb8, 0x80, 0x40, 0x20, 0x00, 
	/* 00b8 */	0x20, 0x70, 0xf8, 0x20, 0xf8, 0x70, 0x20, 0x00, 
	/* 00c0 */	0x20, 0x70, 0xf8, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 00c8 */	0x20, 0x20, 0xf8, 0x70, 0x20, 0x00, 0x00, 0x00, 
	/* 00d0 */	0x20, 0x30, 0xf8, 0x30, 0x20, 0x00, 0x00, 0x00, 
	/* 00d8 */	0x20, 0x60, 0xf8, 0x60, 0x20, 0x00, 0x00, 0x00, 
	/* 00e0 */	0x30, 0x20, 0x20, 0x20, 0x60, 0x00, 0x00, 0x00, 
	/* 00e8 */	0x00, 0x50, 0xf8, 0x50, 0x00, 0x00, 0x00, 0x00, 
	/* 00f0 */	0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 00f8 */	0x70, 0x88, 0xa8, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 0100 */	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0108 */	0x20, 0x20, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 
	/* 0110 */	0x48, 0x48, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0118 */	0x50, 0xf8, 0x50, 0xf8, 0x50, 0x00, 0x00, 0x00, 
	/* 0120 */	0x78, 0xa0, 0x70, 0x28, 0xf0, 0x00, 0x00, 0x00, 
	/* 0128 */	0x88, 0x10, 0x20, 0x40, 0x88, 0x00, 0x00, 0x00, 
	/* 0130 */	0x60, 0x90, 0x60, 0x98, 0x70, 0x00, 0x00, 0x00, 
	/* 0138 */	0x20, 0x20, 0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0140 */	0x10, 0x20, 0x20, 0x20, 0x10, 0x00, 0x00, 0x00, 
	/* 0148 */	0x40, 0x20, 0x20, 0x20, 0x40, 0x00, 0x00, 0x00, 
	/* 0150 */	0x88, 0x50, 0xf8, 0x50, 0x88, 0x00, 0x00, 0x00, 
	/* 0158 */	0x20, 0x20, 0xf8, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 0160 */	0x00, 0x00, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 
	/* 0168 */	0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0170 */	0x00, 0x00, 0x00, 0x00, 0x20, 0x00, 0x00, 0x00, 
	/* 0178 */	0x08, 0x10, 0x20, 0x40, 0x80, 0x00, 0x00, 0x00, 
	/* 0180 */	0x70, 0x88, 0xa8, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 0188 */	0x20, 0x60, 0x20, 0x20, 0x70, 0x00, 0x00, 0x00, 
	/* 0190 */	0x70, 0x88, 0x10, 0x60, 0xf8, 0x00, 0x00, 0x00, 
	/* 0198 */	0xf0, 0x08, 0x70, 0x08, 0xf0, 0x00, 0x00, 0x00, 
	/* 01a0 */	0x90, 0x90, 0xf8, 0x10, 0x10, 0x00, 0x00, 0x00, 
	/* 01a8 */	0xf8, 0x80, 0xf0, 0x08, 0xf0, 0x00, 0x00, 0x00, 
	/* 01b0 */	0x70, 0x80, 0xf0, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 01b8 */	0xf8, 0x08, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 
	/* 01c0 */	0x70, 0x88, 0x70, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 01c8 */	0x70, 0x88, 0x78, 0x08, 0x70, 0x00, 0x00, 0x00, 
	/* 01d0 */	0x00, 0x20, 0x00, 0x20, 0x00, 0x00, 0x00, 0x00, 
	/* 01d8 */	0x00, 0x20, 0x00, 0x20, 0x20, 0x40, 0x00, 0x00, 
	/* 01e0 */	0x10, 0x20, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 
	/* 01e8 */	0x00, 0xf8, 0x00, 0xf8, 0x00, 0x00, 0x00, 0x00, 
	/* 01f0 */	0x40, 0x20, 0x10, 0x20, 0x40, 0x00, 0x00, 0x00, 
	/* 01f8 */	0x70, 0x88, 0x10, 0x20, 0x00, 0x20, 0x00, 0x00, 
	/* 0200 */	0x70, 0x88, 0xa8, 0x90, 0x80, 0x78, 0x00, 0x00, 
	/* 0208 */	0x70, 0x88, 0xf8, 0x88, 0x88, 0x00, 0x00, 0x00, 
	/* 0210 */	0xf0, 0x88, 0xf0, 0x88, 0xf0, 0x00, 0x00, 0x00, 
	/* 0218 */	0x78, 0x80, 0x80, 0x80, 0x78, 0x00, 0x00, 0x00, 
	/* 0220 */	0xf0, 0x88, 0x88, 0x88, 0xf0, 0x00, 0x00, 0x00, 
	/* 0228 */	0xf8, 0x80, 0xe0, 0x80, 0xf8, 0x00, 0x00, 0x00, 
	/* 0230 */	0xf8, 0x80, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 
	/* 0238 */	0x78, 0x80, 0xb8, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 0240 */	0x88, 0x88, 0xf8, 0x88, 0x88, 0x00, 0x00, 0x00, 
	/* 0248 */	0x70, 0x20, 0x20, 0x20, 0x70, 0x00, 0x00, 0x00, 
	/* 0250 */	0x78, 0x08, 0x08, 0x08, 0xf0, 0x00, 0x00, 0x00, 
	/* 0258 */	0x88, 0x90, 0xe0, 0x90, 0x88, 0x00, 0x00, 0x00, 
	/* 0260 */	0x80, 0x80, 0x80, 0x80, 0xf8, 0x00, 0x00, 0x00, 
	/* 0268 */	0x88, 0xd8, 0xa8, 0x88, 0x88, 0x00, 0x00, 0x00, 
	/* 0270 */	0x88, 0xc8, 0xa8, 0x98, 0x88, 0x00, 0x00, 0x00, 
	/* 0278 */	0x70, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 0280 */	0xf0, 0x88, 0xf0, 0x80, 0x80, 0x00, 0x00, 0x00, 
	/* 0288 */	0x70, 0x88, 0xa8, 0x90, 0x68, 0x00, 0x00, 0x00, 
	/* 0290 */	0xf0, 0x88, 0xf0, 0x90, 0x88, 0x00, 0x00, 0x00, 
	/* 0298 */	0x78, 0x80, 0x70, 0x08, 0xf0, 0x00, 0x00, 0x00, 
	/* 02a0 */	0xf8, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 02a8 */	0x88, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 02b0 */	0x88, 0x88, 0x88, 0x50, 0x20, 0x00, 0x00, 0x00, 
	/* 02b8 */	0x88, 0x88, 0xa8, 0xd8, 0x88, 0x00, 0x00, 0x00, 
	/* 02c0 */	0x88, 0x50, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 
	/* 02c8 */	0x88, 0x50, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 02d0 */	0xf8, 0x10, 0x20, 0x40, 0xf8, 0x00, 0x00, 0x00, 
	/* 02d8 */	0x70, 0x40, 0x40, 0x40, 0x70, 0x00, 0x00, 0x00, 
	/* 02e0 */	0x80, 0x40, 0x20, 0x10, 0x08, 0x00, 0x00, 0x00, 
	/* 02e8 */	0x70, 0x10, 0x10, 0x10, 0x70, 0x00, 0x00, 0x00, 
	/* 02f0 */	0x00, 0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 
	/* 02f8 */	0x00, 0x00, 0x00, 0x00, 0xf8, 0x00, 0x00, 0x00, 
	/* 0300 */	0x40, 0x40, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 0308 */	0x00, 0x70, 0x90, 0x90, 0x78, 0x00, 0x00, 0x00, 
	/* 0310 */	0x80, 0x80, 0xf0, 0x88, 0xf0, 0x00, 0x00, 0x00, 
	/* 0318 */	0x00, 0x78, 0x80, 0x80, 0x78, 0x00, 0x00, 0x00, 
	/* 0320 */	0x08, 0x08, 0x78, 0x88, 0x78, 0x00, 0x00, 0x00, 
	/* 0328 */	0x70, 0x88, 0xf8, 0x80, 0x70, 0x00, 0x00, 0x00, 
	/* 0330 */	0x38, 0x40, 0xf8, 0x40, 0x40, 0x00, 0x00, 0x00, 
	/* 0338 */	0x00, 0x70, 0x88, 0x78, 0x08, 0x70, 0x00, 0x00, 
	/* 0340 */	0x80, 0x80, 0xf0, 0x88, 0x88, 0x00, 0x00, 0x00, 
	/* 0348 */	0x20, 0x00, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 0350 */	0x08, 0x00, 0x08, 0x08, 0x48, 0x30, 0x00, 0x00, 
	/* 0358 */	0x80, 0x80, 0x90, 0xe0, 0x90, 0x00, 0x00, 0x00, 
	/* 0360 */	0x60, 0x20, 0x20, 0x20, 0x30, 0x00, 0x00, 0x00, 
	/* 0368 */	0x00, 0x50, 0xa8, 0xa8, 0x88, 0x00, 0x00, 0x00, 
	/* 0370 */	0x00, 0xf0, 0x88, 0x88, 0x88, 0x00, 0x00, 0x00, 
	/* 0378 */	0x00, 0x70, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 0380 */	0x00, 0xf0, 0x88, 0xf0, 0x80, 0x80, 0x00, 0x00, 
	/* 0388 */	0x00, 0x78, 0x88, 0x78, 0x08, 0x08, 0x00, 0x00, 
	/* 0390 */	0x00, 0x78, 0x80, 0x80, 0x80, 0x00, 0x00, 0x00, 
	/* 0398 */	0x30, 0x40, 0x20, 0x10, 0x60, 0x00, 0x00, 0x00, 
	/* 03a0 */	0x40, 0xf8, 0x40, 0x40, 0x38, 0x00, 0x00, 0x00, 
	/* 03a8 */	0x00, 0x88, 0x88, 0x88, 0x70, 0x00, 0x00, 0x00, 
	/* 03b0 */	0x00, 0x88, 0x88, 0x50, 0x20, 0x00, 0x00, 0x00, 
	/* 03b8 */	0x00, 0x88, 0xa8, 0xa8, 0x50, 0x00, 0x00, 0x00, 
	/* 03c0 */	0x00, 0xd8, 0x20, 0x20, 0xd8, 0x00, 0x00, 0x00, 
	/* 03c8 */	0x00, 0x88, 0x88, 0x50, 0x20, 0xc0, 0x00, 0x00, 
	/* 03d0 */	0x00, 0xf0, 0x20, 0x40, 0xf0, 0x00, 0x00, 0x00, 
	/* 03d8 */	0x30, 0x20, 0x40, 0x20, 0x30, 0x00, 0x00, 0x00, 
	/* 03e0 */	0x20, 0x20, 0x20, 0x20, 0x20, 0x00, 0x00, 0x00, 
	/* 03e8 */	0x60, 0x20, 0x10, 0x20, 0x60, 0x00, 0x00, 0x00, 
	/* 03f0 */	0x68, 0xb0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 
	/* 03f8 */	0x20, 0x50, 0x88, 0x88, 0xf8, 0x00, 0x00, 0x00, 
	/* 0400 */	0x0a
};

#endif

/**
** z26 is Copyright 1997-2011 by John Saeger and contributors.  
** z26 is released subject to the terms and conditions of the
** GNU General Public License Version 2 (GPL).  z26 comes with no warranty.
** Please see COPYING.TXT for details.
*/
#ifndef EMUDRAW_H
#define EMUDRAW_H

#define BUF_WIDTH 512
#define BUF_HEIGHT 288

#define COLORMIX(a, b) ( ((((a & 0xF81F) + (b & 0xF81F)) >> 1) & 0xF81F) | ((((a & 0x07E0) + (b & 0x07E0)) >> 1) & 0x07E0) )
//#define COLORMIX(a, b) (((a & 0xF7DE) >> 1) + ((b & 0xF7DE) >> 1))

#include "include/osd_cpu.h"

typedef struct sprite_t
{
	u32 src;
    u32 dst;
	u8 color;
	u8 attr;//
	u8 type;
	u8 rows;
    u32 x;
} SPRITE;

enum
{
	SPRITE_END = 0,
	SPRITE_8,//1
	SPRITE_16,//2
	SPRITE_16_ROWS,//3
	SPRITE_32,//4
	SPRITE_PART//5
};

#endif /* EMUDRAW_H */

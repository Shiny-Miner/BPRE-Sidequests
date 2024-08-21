#ifndef OAM_TABLE_H
#define OAM_TABLE_H

#include <pokeagb/pokeagb.h>
#include "../config.h"


#define SHAPE_SQUARE 0
#define SHAPE_HORIZONTAL 1
#define SHAPE_VERTICAL 2

//sizeof: 0x24
struct OamTableEntry {
	u16 starterBytes;
	u16 palTag;
	u16 tilesTag;
	u16 len;
	u16 width;
	u16 height;
	u8  slot;
	u8  footprint;
	u16 unused;
	u32 distribution;
	u32 sizedraw;
	u32 animation;
	void *sprites;
	u32 ramstore;
};

struct ShapeSize {
	u8 shape;
	u8 size;
};

extern struct OamTableEntry * const oam_tbl;

extern struct ShapeSize shapeSizeFromWidthAndHeight(u8 w, u8 h);

#endif
#ifndef OAM_PAL_TABLE_H
#define OAM_PAL_TABLE_H

#include <pokeagb/pokeagb.h>
#include "../config.h"

struct OamPalTbl {
	void *pal_ptr;
	u16 pal_tag;
	u16 filler;
};


extern struct OamPalTbl * const oam_pal_tbl;

extern struct OamPalTbl* findOamPalEntryByTag(u16 pal_tag);

#endif
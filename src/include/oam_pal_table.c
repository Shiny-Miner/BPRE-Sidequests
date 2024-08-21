#ifndef OAM_PAL_TABLE_C
#define OAM_PAL_TABLE_C

#include "oam_pal_table.h"
 
struct OamPalTbl * const oam_pal_tbl = (struct OamPalTbl *)OAM_PAL_TABLE_START;

struct OamPalTbl* findOamPalEntryByTag(u16 pal_tag){
	struct OamPalTbl* tbl_i = oam_pal_tbl;
	while(tbl_i->pal_ptr != 0){
		if(tbl_i->pal_tag == pal_tag){
			return tbl_i;
		}
		tbl_i++;
	}
	return (struct OamPalTbl*)0;
}
#endif
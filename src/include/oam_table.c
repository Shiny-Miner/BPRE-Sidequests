#ifndef OAM_TABLE_C
#define OAM_TABLE_C

#include "oam_table.h"

struct OamTableEntry * const oam_tbl = (struct OamTableEntry *)OAM_TABLE_START;

struct ShapeSize shapeSizeFromWidthAndHeight(u8 w, u8 h){
	struct ShapeSize returnValue = {};
	if(w == h){
		returnValue.shape=SHAPE_SQUARE;
		switch(w) {
			case 8:
				returnValue.size = 0;
				break;
			case 16:
				returnValue.size = 1;
				break;
			case 32:
				returnValue.size = 2;
				break;
			case 64:
				returnValue.size = 3;
				break;
		}
	} else if (w > h){
		returnValue.shape=SHAPE_HORIZONTAL;
		if (w == 16) {
			returnValue.size = 0;
		}else if (w == 32) {
			if (h == 8) {
				returnValue.size = 1;
			} else {
				returnValue.size = 2;
			}
		} else {
			returnValue.size = 3;
		}
		
	} else {
		returnValue.shape=SHAPE_VERTICAL;
		if (h == 16) {
			returnValue.size = 0;
		}else if (h == 32) {
			if (w == 8) {
				returnValue.size = 1;
			} else {
				returnValue.size = 2;
			}
		} else {
			returnValue.size = 3;
		}
	}
	
	return returnValue;
}
#endif
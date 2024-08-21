#ifndef RBOX_HANDLER_C
#define RBOX_HANDLER_C

#include "rbox_handler.h"

void write_to_quest_title(u8 id, u8 font, struct TextColor* color, u8 speed, const pchar* s){
	rboxid_print(id, font, 3, 0, color, speed, s);
}

void write_to_quest_desc(u8 font, struct TextColor* color, u8 speed, const pchar* s){
	rboxid_clear_pixels(QUEST_DESC_RBOX_ID, 0);
	rboxid_print(QUEST_DESC_RBOX_ID, font, 0, 6, color, speed, s);
	rboxid_update(QUEST_DESC_RBOX_ID, 1);
	rboxid_tilemap_update(QUEST_DESC_RBOX_ID);
}

#endif
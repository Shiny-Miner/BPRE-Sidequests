#ifndef RBOX_HANDLER_H
#define RBOX_HANDLER_H

#include <pokeagb/pokeagb.h>
#include "../config.h"
#include "quest_table.h"

#define QUEST_DESC_RBOX_ID 4

extern void write_to_quest_title(u8 id, u8 font, struct TextColor* color, u8 speed, const pchar* s);

extern void write_to_quest_desc(u8 font, struct TextColor* color, u8 speed, const pchar* s);

#endif
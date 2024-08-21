#ifndef GUI_H
#define GUI_H

#include <pokeagb/pokeagb.h>
#include "../config.h"
#define rgb5(r, g, b) (u16)((r >> 3) | ((g >> 3) << 5) | ((b >> 3) << 10))

#define QUEST_GUI_ACTIVE	1
#define QUEST_GUI_COMPLETED	0
				

struct QuestGuiInfo {
	u8 cursor_i;
	u8 page_start_quest_i;
	u8 page_end_quest_i;
	u8 cursor_oam_id;
	u8 mode;
	u8 npc_oam_ids[GUI_ENTRIES_PER_PAGE];
	struct QuestTableEntry *page_quests[GUI_ENTRIES_PER_PAGE];
};

#include "quest_table.h"
#include "rbox_handler.h"

extern const u16 dnav_text_pal[];
						
extern struct TextColor dnav_text_black;
extern struct TextColor dnav_text_white;
extern struct TextColor dnav_text_red;
extern struct TextColor dnav_text_green;
extern struct Object * const objects_start;
#define gui_completedPalLen 28
extern const unsigned char gui_completedPal[28];
		
extern const struct BgConfig bg_config_quest_gui[4];

//larghezza salta di 8px in 8 px
// lunghezza sempre di 8px in 8 px ma รจ come se ci aggiungessi sempre 1 (parte da 8 px)
extern struct TextboxTemplate quest_boxes_base[];

extern const u8 cursor_positions[][2];

extern void c2_quest_gui();
extern void vblank_cb_spq();
extern void quest_gui_exit();
extern void update_cursor_position();
extern void turn_page();

#endif

#include <pokeagb/pokeagb.h>
#include "img_built/gui.h"
#include "include/agb_debug/debug.c"
#include "include/oam_table.h"
#include "include/rbox_handler.h"
#include "include/rbox_handler.h"
#include "include/gui.h"
#include "include/quest_table.h"
#include "include/setup.h"
#include "include/oam_pal_table.h"
#include "include/sprite_util.h"
#include "include/deleteme.h"
#include "config.h"

#if USE_C_QUESTS
#include "include/debug_quests.h"
#else
#include "quests.h"
#endif

#define CURSOR_TILES_TAG 0x6F
#define CURSOR_PALS_TAG 0x08

void close_startmenu() {
	safari_stepscount_close();
	sm_close_description();
	sm_close_menu();
}

int main() {
    close_startmenu();
    fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
    void quest_gui_handler(void);
    set_callback1(quest_gui_handler);
    super.multi_purpose_state_tracker = 0;
	return 1;
}


void quest_gui_handler(){
	struct QuestGuiInfo *quest_gui_info = (struct QuestGuiInfo *)GUI_INFO_START;
	struct FadeControl pal_fade_control = *((struct FadeControl *)0x02037ab8);

	switch(super.multi_purpose_state_tracker){
		case 0:
            if (!pal_fade_control.active) {
				setup(); 					//clear all graphics
				rboxes_free(); 				//clear rboxes
				bgid_mod_x_offset(0, 0, 0);	//config bgs independently of their previous state
				bgid_mod_y_offset(0, 0, 0);
				bgid_mod_x_offset(1, 0, 0);
				bgid_mod_y_offset(1, 0, 0);
				gpu_tile_bg_drop_all_sets(0);
				bg_vram_setup(0, (struct BgConfig *)&bg_config_quest_gui, 4);
				//Clear VRAM
				u32 set = 0;
				CpuFastSet((void*)&set, (void*)ADDR_VRAM, CPUModeFS(0x10000, CPUFSSET));
				//Hide BGs
				gpu_sync_bg_hide(1);
				gpu_sync_bg_hide(0);	
				//Set callbacks
				set_callback2(c2_quest_gui);
				vblank_handler_set(vblank_cb_spq);
				set_callback1(quest_gui_handler);
				//Init quest_gui struct
				quest_gui_info->cursor_i = 0;
				quest_gui_info->page_start_quest_i = 0;
				quest_gui_info->page_end_quest_i = 0;
				quest_gui_info->mode = QUEST_GUI_ACTIVE;
				
				super.multi_purpose_state_tracker++;;
			}
			break;
		case 1: { //Load backgground image, init rboxes and quest list
			//Load bg image
			void *quest_gbackbuffer = malloc(0x800);
			//(*DNavState)->backbuffer = dexnav_gbackbuffer;
			gpu_pal_apply((void *)(&dnav_text_pal), 15 * 16, 32);
			gpu_pal_apply_compressed((void *)guiPal, 0, 32);
			LZ77UnCompWram((void *)guiMap, (void *)quest_gbackbuffer);
			lz77UnCompVram((void *)guiTiles, (void *)0x06000000);
			bgid_set_tilemap(1, quest_gbackbuffer);
			bgid_mark_for_sync(1);
			bgid_mark_for_sync(0);
			//init rboxes
			rbox_init_from_templates(quest_boxes_base);
			//init quests list
			initGuiQuests(quest_gui_info);
			findNextAvailableQuests(quest_gui_info);
			
			super.multi_purpose_state_tracker++;
		}
			break;
		case 2: //fill rboxes
            if (!pal_fade_control.active) { //Wait for fadescreen to stop
				// clean boxes
				for (u32 i = 0; i < 5; ++i) {
					rboxid_clear_pixels(i, 0);
				}
				//write quests titles
				for (u8 i = 0; i < 4; ++i) {
					write_to_quest_title(i, 0, &dnav_text_black, 0, quest_gui_info->page_quests[i]->quest_name_ptr);
					rboxid_update(i, 1);
					rboxid_tilemap_update(i);
				}
				
				write_to_quest_desc (0, &dnav_text_black, 0, quest_gui_info->page_quests[0]->quest_desc_ptr);
				
				super.multi_purpose_state_tracker++;
			}
		case 3: {//Display OWs (cursor and npcs)
			//Display cursor
			u8 cursor_oam_id = display_compressed_sprite(16, 16, cursor_positions[0][0], cursor_positions[0][1], CURSOR_TILES_TAG, (void *)CURSOR_TILE_ADDR, CURSOR_PALS_TAG, (void *)0x08463308, 1, 0);	
			quest_gui_info->cursor_oam_id = cursor_oam_id;
			//Display all the needed NPCs
			for(u8 i=0;
					i<GUI_ENTRIES_PER_PAGE && quest_gui_info->page_quests[i]->oam_id != 0xFF;
					i++){
					
				u8 npc_oam_id = display_npc(quest_gui_info->page_quests[i]->oam_id, 52, 24*i + 25, i);
				quest_gui_info->npc_oam_ids[i] = npc_oam_id;
				
			}
			super.multi_purpose_state_tracker++;
		}
		case 4: // Show screen
            fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
			gpu_sync_bg_show(0);
			gpu_sync_bg_show(1);
            super.multi_purpose_state_tracker++;
			break;
		case 5: //Input control NOTE: L and R ARE INVERTED IN POKEAGB
			if (!pal_fade_control.active) { //Wait for fadescreen to end
                switch (super.buttons_new_remapped & (KEY_B | KEY_DOWN | KEY_UP | KEY_L | KEY_R | KEY_SELECT)) {
					case KEY_SELECT:
						if(quest_gui_info->mode == QUEST_GUI_ACTIVE){
							gpu_pal_apply_compressed((void *)gui_completedPal, 0, 32);
							quest_gui_info->mode = QUEST_GUI_COMPLETED;
						} else {
							gpu_pal_apply_compressed((void *)guiPal, 0, 32);
							quest_gui_info->mode = QUEST_GUI_ACTIVE;
						}
						quest_gui_info->cursor_i = 0;
						quest_gui_info->page_start_quest_i = 0;
						quest_gui_info->page_end_quest_i = 0;
						initGuiQuests(quest_gui_info);
						findNextAvailableQuests(quest_gui_info);
						turn_page();
						break;
                    case KEY_R:
						if(!findNextAvailableQuests(quest_gui_info)){ //Fill the gui_info struct with the next quests, if none is available, play a "denied" sound effect
							audio_play(SOUND_WALLRUN);
						} else {
							turn_page();
						}
                        break;
                    case KEY_L: 
						if(!findPrevAvailableQuests(quest_gui_info)){ //Fill the gui_info struct with the previous quests, if none is available, play a "denied" sound effect
							audio_play(SOUND_WALLRUN);
						} else {
							turn_page();
						}
                        break;
                    case KEY_B:
                        // exit to start menu
                        set_callback1(quest_gui_exit);
                        super.multi_purpose_state_tracker = 0;
                        return;
                    case KEY_DOWN:
						quest_gui_info->cursor_i = quest_gui_info->cursor_i == GUI_ENTRIES_PER_PAGE-1 ? 0 : quest_gui_info->cursor_i+1;
						audio_play(SOUND_GENERIC_CLINK);
                        break;
                    case KEY_UP:
						quest_gui_info->cursor_i = quest_gui_info->cursor_i == 0 ? GUI_ENTRIES_PER_PAGE-1 : quest_gui_info->cursor_i-1;
						audio_play(SOUND_GENERIC_CLINK);	
                        break;
                };
                update_cursor_position();
            }
            break;
			
	}
	
	
}
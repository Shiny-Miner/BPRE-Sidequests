#ifndef GUI_C
#define GUI_C

#include "gui.h"
	
const u16 dnav_text_pal[] = {
	rgb5(255, 0, 255), rgb5(248, 248, 248), rgb5(112, 112, 112),
	rgb5(0, 0, 0), rgb5(208, 208, 208), rgb5(76, 154, 38),
	rgb5(102, 194, 66), rgb5(168, 75, 76), rgb5(224, 114, 75),
	rgb5(180, 124, 41), rgb5(241, 188, 60), rgb5(255, 0, 255),
    rgb5(255, 0, 255), rgb5(255, 0, 255), rgb5(255, 133, 200), rgb5(64, 200, 248)};
						
struct TextColor dnav_text_black = {0, 3, 4};
struct TextColor dnav_text_white = {0, 1, 2};
struct TextColor dnav_text_red = {0, 7, 8};
struct TextColor dnav_text_green = {0, 5, 6};
struct Object * const objects_start = (struct Object * const)0x0202063c;
const unsigned char gui_completedPal[28] __attribute__((aligned(4)))=
{
	0x10,0x20,0x00,0x00,0x00,0x00,0x00,0x16,0x29,0x5A,0x67,0xFF,0x7F,0x00,0xFF,0x7F,
	0xAD,0x35,0xB9,0x39,0xFF,0x7F,0x20,0x00,0x00,0xB0,0x01,0x00,
};

		
const struct BgConfig bg_config_quest_gui[4] = {
					{
						.padding = 0,
						.b_padding = 0,
						.priority = 2,
						.palette = 0,
						.size = 0,
						.map_base = 29,
						.character_base = 2,
						.bgid = 0,
					},
					{
						.padding = 0,
						.b_padding = 0,
						.priority = 3,
						.palette = 0,
						.size = 0,
						.map_base = 28,
						.character_base = 0,
						.bgid = 1,
					},
					{
						.padding = 0,
						.b_padding = 0,
						.priority = 3,
						.palette = 0,
						.size = 0,
						.map_base = 30,
						.character_base = 2,
						.bgid = 2,
					},
					{
						.padding = 0,
						.b_padding = 0,
						.priority = 3,
						.palette = 0,
						.size = 1,
						.map_base = 31,
						.character_base = 3,
						.bgid = 3,
					},
				};

//larghezza salta di 8px in 8 px
// lunghezza sempre di 8px in 8 px ma è come se ci aggiungessi sempre 1 (parte da 8 px)
struct TextboxTemplate quest_boxes_base[] = {
    {
        /*q1Title */
        .bg_id = 0,
        .x = 8,
        .y = 3,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 1,
    },
    {
        //q2Title 
        .bg_id = 0,
        .x = 8,
        .y = 6,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 71,
    },
    {
        //q3Title 
        .bg_id = 0,
        .x = 8,
        .y = 9,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 141,
    },
    {
        //q4Title 
        .bg_id = 0,
        .x = 8,
        .y = 12,
        .width = 20,
        .height = 2,
        .pal_id = 15,
        .charbase = 211,
    },
    {
        // desc 
        .bg_id = 0,
        .x = 2,
        .y = 15,
        .width = 20,
        .height = 5,
        .pal_id = 15,
        .charbase = 281,
    },
    {
        .bg_id = 0xFF, // marks the end of the tb array 
    },

};

const u8 cursor_positions[][2] = {
	{
		31,
		32 + 24*0
	},
	{
		31,
		32 + 24*1
	},
	{
		31,
		32 + 24*2
	},
	{
		31,
		32 + 24*3
	}
};
	
void c2_quest_gui(){
    obj_sync_superstate();
    objc_exec();
    process_palfade();
    task_exec();
    tilemaps_sync();
    // merge textbox and text tile maps
    remoboxes_upload_tilesets();
}

void vblank_cb_spq(){
	gpu_sprites_upload();
	copy_queue_process();
	gpu_pal_upload();
}


void quest_gui_exit() {
    switch (super.multi_purpose_state_tracker) {
        case 0:
			fade_screen(0xFFFFFFFF, 0, 0, 16, 0x0000);
			gpu_sync_bg_hide(1);
			gpu_sync_bg_hide(0);	
			super.multi_purpose_state_tracker++;
            break;
        case 1:
            m4aMPlayVolumeControl(&mplay_BGM, 0xFFFF, 256);
            set_callback1(c1_overworld);
            set_callback2(c2_overworld_switch_start_menu);
			super.multi_purpose_state_tracker++;
            break;
		case 2:
            fade_screen(0xFFFFFFFF, 0, 16, 0, 0x0000);
			gpu_sync_bg_show(0);
			gpu_sync_bg_show(1);
			super.multi_purpose_state_tracker++;
		break;
	}
}

void update_cursor_position(){
	struct QuestGuiInfo *quest_gui_info = (struct QuestGuiInfo *)GUI_INFO_START;
	
	objects[quest_gui_info->cursor_oam_id].pos1.x = cursor_positions[quest_gui_info->cursor_i][0];
	objects[quest_gui_info->cursor_oam_id].pos1.y = cursor_positions[quest_gui_info->cursor_i][1];
	
	
	write_to_quest_desc (0, &dnav_text_black, 0, quest_gui_info->page_quests[quest_gui_info->cursor_i]->quest_desc_ptr);
}


void turn_page(){
	struct QuestGuiInfo *quest_gui_info = (struct QuestGuiInfo *)GUI_INFO_START;
	gpu_sync_bg_hide(1);
	gpu_sync_bg_hide(0);	
	quest_gui_info->cursor_i = 0;
	super.multi_purpose_state_tracker = 2;
	for(u8 i=0; i<sizeof(quest_gui_info->npc_oam_ids); i++){
		obj_free(&objects[quest_gui_info->npc_oam_ids[i]]);
		obj_delete(&objects[quest_gui_info->npc_oam_ids[i]]);
	}
	obj_free(&objects[quest_gui_info->cursor_oam_id]);
	obj_delete(&objects[quest_gui_info->cursor_oam_id]);
	audio_play(SOUND_GENERIC_CLINK);
}

#endif
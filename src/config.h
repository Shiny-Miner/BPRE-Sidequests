#ifndef CONFIG_H
#define CONFIG_H

#define QUEST_TABLE_START 0x9FC3E30	//Customizable
#define GUI_ENTRIES_PER_PAGE 4		//Make sure to change the graphics, cursor and rboxes position

#define USE_C_QUESTS 1				//If this is 1, this will use quests from debug_quests.c, otherwise the code will look quests up from QUEST_TABLE_START



#define GUI_INFO_START 0x0202402C //By default this is the opponent's party
#define OAM_TABLE_START 0x83A3BB0 		//Default BPRE
#define OAM_TABLE_SIZE 0x99 			//Default BPRE
#define OAM_PAL_TABLE_START 0x83A5158 	//Default BPRE
#define OAM_PAL_TABLE_SIZE 18 			//Default BPRE

#define CURSOR_TILE_ADDR 0x08463328 	//Default BPRE
#define CURSOR_PALS_ADDR 0x08463308 	//Default BPRE

#endif

#ifndef QUEST_TABLE_C
#define QUEST_TABLE_C

#include "quest_table.h"

struct QuestTableEntry empty_quest = {
	.oam_id = 0xFF,
	.quest_name_ptr = &no_info,
	.quest_desc_ptr = &no_info
};

void initGuiQuests(struct QuestGuiInfo * const quest_gui_info) {
	for (u8 i=0; i<GUI_ENTRIES_PER_PAGE; i++){ //Init to empty
		quest_gui_info->page_quests[i] = &empty_quest;
	}
}

u8 findNextAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	if(quest_gui_info->mode == QUEST_GUI_ACTIVE){
		return findNextActiveAvailableQuests(quest_gui_info);
	} else {
		return findNextCompletedAvailableQuests(quest_gui_info);
	}
}

u8 findPrevAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	if(quest_gui_info->mode == QUEST_GUI_ACTIVE){
		return findPrevActiveAvailableQuests(quest_gui_info);
	} else {
		return findPrevCompletedAvailableQuests(quest_gui_info);
	}
}

// ------------------- ACTIVE QUESTS ------------------- //

//returns true if and only if at least one more quest was available, false otherwise
u8 findNextActiveAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	u8 quest_list_i = quest_gui_info->page_end_quest_i;
	struct QuestTableEntry * quest_iterator = quest_list + quest_list_i;

	u8 page_quests_i=0;

	while (quest_iterator->oam_id != 0xFF && page_quests_i < GUI_ENTRIES_PER_PAGE){
		if(check_flag(quest_iterator->flag_is_available)){ //if it's available
			if(!check_flag(quest_iterator->flag_is_completed)){ //if it's not completed
				if(page_quests_i == 0){	
					initGuiQuests(quest_gui_info); //Initialize quest list only when we know the next page will contain at least 1 quest, otherwise we should not allow page turning
					quest_gui_info->page_start_quest_i = quest_list_i;
				}
				quest_gui_info->page_quests[page_quests_i] = quest_iterator;
				page_quests_i++;
			}
		}
		quest_iterator++;
		quest_list_i++;
	}
	
	quest_gui_info->page_end_quest_i = quest_list_i;
	
	return page_quests_i != 0;
	
}

//returns true if and only if at least one more quest was available, false otherwise
u8 findPrevActiveAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	u8 quest_list_i = quest_gui_info->page_start_quest_i;
	struct QuestTableEntry * quest_iterator = quest_list + quest_list_i -1 ;

	s8 page_quests_i = GUI_ENTRIES_PER_PAGE-1;

	while (quest_iterator >= quest_list && page_quests_i >= 0){
		if(check_flag(quest_iterator->flag_is_available)){ //if it's available
			if(!check_flag(quest_iterator->flag_is_completed)){ //if it's not completed
				if(page_quests_i == GUI_ENTRIES_PER_PAGE-1){	
					quest_gui_info->page_end_quest_i = quest_list_i;
				}
				quest_gui_info->page_quests[page_quests_i] = quest_iterator;
				page_quests_i--;
			}
		}
		quest_iterator--;
		quest_list_i--;
	}
	
	quest_gui_info->page_start_quest_i = quest_list_i;
	
	return page_quests_i != GUI_ENTRIES_PER_PAGE-1;
	
}







// ------------------- COMPLETED QUESTS ------------------- //




//returns true if and only if at least one more quest was available, false otherwise
u8 findNextCompletedAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	u8 quest_list_i = quest_gui_info->page_end_quest_i;
	struct QuestTableEntry * quest_iterator = quest_list + quest_list_i;

	u8 page_quests_i=0;

	while (quest_iterator->oam_id != 0xFF && page_quests_i < GUI_ENTRIES_PER_PAGE){
		if(check_flag(quest_iterator->flag_is_completed)){ //if it's completed
			if(page_quests_i == 0){	
				initGuiQuests(quest_gui_info); //Initialize quest list only when we know the next page will contain at least 1 quest, otherwise we should not allow page turning
				quest_gui_info->page_start_quest_i = quest_list_i;
			}
			quest_gui_info->page_quests[page_quests_i] = quest_iterator;
			page_quests_i++;
		}
		quest_iterator++;
		quest_list_i++;
	}
	
	quest_gui_info->page_end_quest_i = quest_list_i;
	
	return page_quests_i != 0;
	
}

//returns true if and only if at least one more quest was available, false otherwise
u8 findPrevCompletedAvailableQuests(struct QuestGuiInfo * const quest_gui_info){
	u8 quest_list_i = quest_gui_info->page_start_quest_i;
	struct QuestTableEntry * quest_iterator = quest_list + quest_list_i -1 ;

	s8 page_quests_i = GUI_ENTRIES_PER_PAGE-1;

	while (quest_iterator >= quest_list && page_quests_i >= 0){
		if(check_flag(quest_iterator->flag_is_completed)){ //if it's completed
			if(page_quests_i == GUI_ENTRIES_PER_PAGE-1){	
				quest_gui_info->page_end_quest_i = quest_list_i;
			}
			quest_gui_info->page_quests[page_quests_i] = quest_iterator;
			page_quests_i--;
		}
		quest_iterator--;
		quest_list_i--;
	}
	
	quest_gui_info->page_start_quest_i = quest_list_i;
	
	return page_quests_i != GUI_ENTRIES_PER_PAGE-1;
	
}


#endif
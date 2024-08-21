#ifndef QUESTS_C
#define QUESTS_C

#include "quests.h"

struct QuestTableEntry * const quest_list = (struct QuestTableEntry * const)QUEST_TABLE_START;
u8 no_info[] =    {0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xAE, 0xFE, 0xFF};

#endif
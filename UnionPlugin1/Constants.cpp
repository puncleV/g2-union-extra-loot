// Supported with union (c) 2020 Union team
// Union SOURCE file

#include<set>
namespace GOTHIC_ENGINE {
	auto const AIV_BOSS = 90;
	auto const AIV_SUMMON = 91;
	auto const AIVRX_NPC_LP = 53;
	auto const ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX = 390;

	auto JSON_FILE_NAME = "punclev-utils.json";

	auto EXTRA_LOOT_BASE_CHANCE = 100;
	auto TRADERS_LOOT_PER_CHAPTER = TRUE;

	auto EXTRA_LOOT_CHEST_BASE_CHANCE = 100;

	auto EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER = 250;
	auto MAX_STRENGHTEN_VALUE = 3000;
	auto MIN_STRENGHTEN_VALUE = 250;

	auto ENEMY_STATS_PER_MULTIPLIER = 25;
	auto ENEMY_DEFENCE_PER_MULTIPLIER = 3;
	auto ENEMY_HP_PERCENT_INCREASE_PER_MULTIPLIER = 10;

	auto ENEMY_HP_GROW_LIMIT_PERCENT = 125;
	auto ENEMY_STATS_GROW_LIMIT_PERCENT = 30;
	auto ENEMY_DEFENCE_GROW_LIMIT_PERCENT = 30;

	auto CHAMPION_CHANCE = 5;
	auto CHAMPION_STRENGTHEN_VALUE = 2000;
	auto CHAMPION_EXTRA_LEVEL = 5;
	auto CHAMPION_LP_CHANCE = 35;
	auto CHAMPION_LP_INCREASE = 1;
	auto CHAMPION_STRENGHTEN_VALUE_PER_LP = 350;
	auto CHAMPION_MIN_STATS = 150;
	auto CHAMPION_MAX_STATS = 1250;
	auto CHAMPION_MIN_HP = 1000;
	auto CHAMPION_MAX_HP = 30000;
	auto SHOULD_ADD_LOOT_TO_PLAYER = FALSE;
	auto SHOULD_IGNORE_CHECK_TO_ADD_LOOT = FALSE;
	auto SHOULD_ADD_LOOT_TO_NPC = FALSE;
	auto SHOULD_ADD_LOOT_TO_CHESTS = FALSE;
	auto SHOULD_USE_NPC_LOOT_FOR_CHESTS = TRUE;
	auto SHOULD_STRENGHTEN_ENEMIES = TRUE;
	auto BOSSIFY_CHAMPIONS = FALSE;
	auto IS_DEBUG = FALSE;

	zSTRING REMOVE_ITEMS_VOB_NAME = "";

	auto AIVAR_FOR_NPC_ID = 99;

	std::vector<zSTRING> ignoreLootNpcList = { "TOTEM", "CRAIT", "KHUBA", "SUMKHUBI", "PET_JINA", "LARES", "BILGOT", "PC_TH", "PC_PSIO", "PC_FIG", "PC_MAGE", "ALLIGATORJACK" };
	auto AIV_IS_SUMMON_NPC = 91;
	auto AIV_PARTYMEMBER = 15;

	int getCurrentChapter() {
		int retVal = 0;
		zCPar_Symbol* ps = parser->GetSymbol("kapitel");
		if (ps)
			ps->GetValue(retVal, 0);
		else
			return -1;
		return retVal;
	}

	bool ignoredNpcForLoot(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		if (npc->aiscriptvars[AIV_IS_SUMMON_NPC] == 13771 || npc->aiscriptvars[AIV_PARTYMEMBER]) {
			return TRUE;
		}

		for (auto i = 0; i < ignoreLootNpcList.size(); i += 1) {
			if (npcName.HasWordI(ignoreLootNpcList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}
}
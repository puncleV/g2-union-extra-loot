// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Create a champion NPC with enhanced stats and loot
	bool makeChampion(oCNpc* npc) {
		if (ignoredNpcForLoot(npc)) {
			return false;
		}
		if (npc->isSummon() || npc->isBoss()) {
			return false;
		}

		auto addedValue = 150;
		npc->level += CHAMPION_EXTRA_LEVEL;

		int npcId = npc->getNpcId();
		npcVariables.setVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT, NpcVariables::CHAMPION);

		// Chance to give LP when killed
		if (randomizer.Random(0, 100) < CHAMPION_LP_CHANCE) {
			npcVariables.setVariable(npcId, NpcVariables::LP_INCREASE, CHAMPION_LP_INCREASE);
			addedValue += CHAMPION_STRENGHTEN_VALUE_PER_LP * CHAMPION_LP_INCREASE;
		}

		minChampionStats(npc);
		strengthenNpc(npc, CHAMPION_STRENGTHEN_VALUE + addedValue * 1.25);
		maxChampionStats(npc);

		if (BOSSIFY_CHAMPIONS) {
			npc->aiscriptvars[AIV_BOSS] = 1;
		}

		return true;
	}
}

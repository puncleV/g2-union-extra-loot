// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void minChampionStats(oCNpc* npc) {
		if (npc->attribute[NPC_ATR_HITPOINTSMAX] < CHAMPION_MIN_HP) {
			npc->attribute[NPC_ATR_HITPOINTSMAX] = CHAMPION_MIN_HP;
			npc->attribute[NPC_ATR_HITPOINTS] = CHAMPION_MIN_HP;
		}
		if (npc->attribute[NPC_ATR_STRENGTH] < CHAMPION_MIN_STATS) {
			npc->attribute[NPC_ATR_STRENGTH] = CHAMPION_MIN_STATS;
		}
		if (npc->attribute[NPC_ATR_DEXTERITY] < CHAMPION_MIN_STATS) {
			npc->attribute[NPC_ATR_DEXTERITY] = CHAMPION_MIN_STATS;
		}
	}		

	void maxChampionStats(oCNpc* npc) {
		if (npc->attribute[NPC_ATR_HITPOINTSMAX] > CHAMPION_MAX_HP) {
			npc->attribute[NPC_ATR_HITPOINTSMAX] = CHAMPION_MAX_HP;
			npc->attribute[NPC_ATR_HITPOINTS] = CHAMPION_MAX_HP;
		}
		if (npc->attribute[NPC_ATR_STRENGTH] > CHAMPION_MAX_STATS) {
			npc->attribute[NPC_ATR_STRENGTH] = CHAMPION_MAX_STATS;
		}
		if (npc->attribute[NPC_ATR_DEXTERITY] > CHAMPION_MAX_STATS) {
			npc->attribute[NPC_ATR_DEXTERITY] = CHAMPION_MAX_STATS;
		}
	}

	bool makeChampion(oCNpc* npc) {
		if (ignoredNpcForLoot(npc)) {
			return false;
		}
		if (npc->isSummon() || npc->isBoss()) {
			return false;
		}
		auto addedValue = 150;
		npc->level += CHAMPION_EXTRA_LEVEL;

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, CHAMPION_VALUE);

		if (randomizer.Random(0, 100) < CHAMPION_LP_CHANCE) {
			npc->setNpcVar(AIVRX_NPC_LP, CHAMPION_LP_INCREASE);

			addedValue += CHAMPION_STRENGHTEN_VALUE_PER_LP * CHAMPION_LP_INCREASE;
		}

		minChampionStats(npc);
		strengthenNpc(npc, CHAMPION_STRENGTHEN_VALUE + addedValue * 1.25);
		maxChampionStats(npc);
		
		npc->aiscriptvars[AIV_BOSS] = 1;

		return true;
	}
}
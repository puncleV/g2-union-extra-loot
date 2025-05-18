// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	int addRandomLootToNpc(oCNpc* npc, const std::vector<Loot>& lootTable) {
		auto addedLoot = -1;
		
		for (size_t i = 0; i < lootTable.size(); i++)
		{
			addedLoot += lootTable[i].tryAddToNpc(npc);
		}

		return addedLoot;
	}

	bool npcCanWearWeapon(oCItem* item, oCNpc* npc) {
		for (size_t i = 0; i < ITM_COND_MAX; i++)
		{
			if (item->cond_atr[i] <= 0 && item->cond_atr[i] >= NPC_ATR_MAX) {
				return false;
			}

			if (npc->attribute[item->cond_atr[i]] < item->cond_value[i])
			{
				return false;
			}
		}

		return true;
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


	bool RX_IsBoss(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_BOSS] == TRUE);
	}

	bool RX_IsSummon(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_SUMMON] == TRUE);
	}

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
		if (RX_IsTrader(npc) || RX_IsSummon(npc) || RX_IsBoss(npc)) {
			return false;
		}

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, 10);

		auto addedValue = 0;
		if (randomizer.Random(0, 100) < CHAMPION_LOOT_CHANCE) {
			for (const auto& lootTable : lootTables) {
			    // todo check if champ loot
			    addedValue += addRandomLootToNpc(npc, lootTable);
			}
			npc->level += CHAMPION_EXTRA_LEVEL;
		}

		if (randomizer.Random(0, 100) < CHAMPION_LP_CHANCE) {
			npc->setNpcVar(AIVRX_NPC_LP, CHAMPION_LP_INCREASE);

			addedValue += CHAMPION_STRENGHTEN_VALUE_PER_LP * CHAMPION_LP_INCREASE;
		}

		for (const auto& lootTable : lootTables) {
		    addedValue += addRandomLootToNpc(npc, lootTable);
		}

		minChampionStats(npc);
		strengthenNpc(npc, CHAMPION_STRENGTHEN_VALUE + addedValue * 1.25);
		maxChampionStats(npc);
		
		npc->aiscriptvars[AIV_BOSS] = 1;

		return true;
	}
}
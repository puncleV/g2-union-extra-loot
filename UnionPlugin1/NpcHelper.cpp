// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	int addRandomLootToNpc(oCNpc* npc, std::vector<Loot>& lootTable = NPC_LOOT_TABLE) {
		auto addedLoot = -1;
		
		for (size_t i = 0; i < lootTable.size(); ++i)
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

	bool makeChampion(oCNpc* npc) {
		if (ignoredNpcForLoot(npc)) {
			return false;
		}
		if (RX_IsTrader(npc) || RX_IsSummon(npc) || RX_IsBoss(npc)) {
			return false;
		}

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, 2);
		auto addedValue = 0;

		if (randomizer.Random(0, 100) < CHAMPION_LOOT_CHANCE) {
			addedValue += addRandomLootToNpc(npc, championLoot);
			npc->level += CHAMPION_EXTRA_LEVEL;
		}

		if (randomizer.Random(0, 100) < CHAMPION_LP_CHANCE) {
			npc->setNpcVar(AIVRX_NPC_LP, CHAMPION_LP_INCREASE);

			if (CHAMPION_STRENGHTEN_VALUE_PER_LP) {
				strengthenNpc(npc, CHAMPION_STRENGHTEN_VALUE_PER_LP * CHAMPION_LP_INCREASE);
			}
		}

		addedValue += addRandomLootToNpc(npc, NPC_LOOT_TABLE);

		npc->attribute[NPC_ATR_HITPOINTSMAX] += 150;
		npc->attribute[NPC_ATR_HITPOINTS] += 150;

		if (addedValue > 0) {
			strengthenNpc(npc, addedValue * 1.25);
		}

		strengthenNpc(npc, CHAMPION_STRENGTHEN_VALUE);
		npc->aiscriptvars[AIV_BOSS] = 1;

		return true;
	}
}
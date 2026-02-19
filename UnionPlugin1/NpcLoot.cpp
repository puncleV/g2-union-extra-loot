// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add loot to an NPC and strengthen them based on loot value
	bool addLootToNPC(oCNpc* npc, bool isChampion) {
		auto lootGiven = false;
		auto addedValue = 0;

		for (auto& lootTable : lootTableList) {
			if (lootTable.steal) {
				continue;
			}
			addedValue += lootTable.addToNpc(npc, isChampion);
		}

		addedValue = max(addedValue, 0);

		if (addedValue > 0) {
			lootGiven = true;
			strengthenNpc(npc, addedValue);
		}

		return lootGiven;
	}

	// Process NPC to determine if they should receive loot
	void goThroughNpcHandlers(oCNpc* npc) {
		if (!npc || npc->aiscriptvars[AIVAR_FOR_NPC_ID] == -1) {
			return;
		}

		if (npc != oCNpc::player) {
			int npcId = assignIdToNpc(npc);
			auto chapterLootWasGiven = npcVariables.getVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT);
			auto isChampion = false;

			// Skip if already has loot for this chapter or is dead
			if (chapterLootWasGiven == NpcVariables::CHAMPION || 
				chapterLootWasGiven >= getCurrentChapter() || 
				npc->IsDead()) {
				return;
			}

			// Chance to become a champion
			if (chapterLootWasGiven == NpcVariables::Value::NOT_GIVEN && 
				randomizer.Random(0, 1000) < CHAMPION_CHANCE) {
				isChampion = true;
			}

			addLootToNPC(npc, isChampion);

			if (isChampion) {
				makeChampion(npc);
			}
			else if (chapterLootWasGiven != getCurrentChapter() && 
					 chapterLootWasGiven != NpcVariables::CHAMPION) {
				npcVariables.setVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT, getCurrentChapter());
			}
		}
	}
}

// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	bool addLootToNPC(oCNpc* npc, bool isChampion) {
		auto lootGiven = false;
		auto addedValue = 0;

		for (auto& lootTable : lootTableList) {
			if(lootTable.steal) {
				continue;
			}
			addedValue += lootTable.addToNpc(npc, isChampion);
		}

		addedValue = max(addedValue, 0);

		if (addedValue > 0) {
			lootGiven = true;
			// todo maybe dont make champions too strong
			strengthenNpc(npc, addedValue);
		}

		return lootGiven;
	}

	int addStealLoot() {
		auto lootGiven = false;
		auto addedValue = 0;


		for (auto& lootTable : lootTableList) {
			if (!lootTable.steal) {
				continue;
			}
			addedValue += lootTable.addToNpc(player, 0, 1);
		}

		return 0;
	}

	void RegisterExternals_punclev() {
		parser->DefineExternal("punclev_loot_steal", addStealLoot, zPAR_TYPE_STRING, 0);
	}

	int oCNpc::getNpcId() {
		return this->aiscriptvars[AIVAR_FOR_NPC_ID];
	}

	bool oCNpc::isChampion() {
		return npcVariables.getVariable(this->getNpcId(), NpcVariables::CHAPTER_LOOT_GIVEN_AT) == NpcVariables::CHAMPION;
	}

	bool oCNpc::isBoss() {
		return(this->aiscriptvars[AIV_BOSS] == TRUE);
	}

	bool oCNpc::isSummon() {
		return (this->aiscriptvars[AIV_SUMMON] == TRUE);
	}

	void goThroughNpcHandlers(oCNpc* npc) {
		if (!npc) {
			return;
		}

		if (npc != oCNpc::player) {
			int npcId = assignIdToNpc(npc);;
			auto chapterLootWasGiven = npcVariables.getVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT);
			auto isChampion = false;
			
			
			if (chapterLootWasGiven == NpcVariables::CHAMPION || chapterLootWasGiven >= getCurrentChapter()) {
				return;
			}

			if (chapterLootWasGiven == NpcVariables::Value::NOT_GIVEN && randomizer.Random(0, 1000) < CHAMPION_CHANCE) {
				isChampion = true;
			}

			addLootToNPC(npc, isChampion);

			if (isChampion) {
				makeChampion(npc);
			} else if (chapterLootWasGiven != getCurrentChapter() && chapterLootWasGiven != NpcVariables::CHAMPION) {
				npcVariables.setVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT, getCurrentChapter());
			}
		}
	}

	zCArray<oCNpc*> oCNpc::goThroughNpcsInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCNpc*> npcList;
		zCVob* pVob = NULL;
		oCNpc* npc = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			npc = zDYNAMIC_CAST<oCNpc>(pVob);
			if (!npc)
				continue;
			if (npc->IsDead())
				continue;

			goThroughNpcHandlers(npc);
		}

		return npcList;
	}

	void oCNpc::randomizeChestsInRadius(float radius) {
		ClearVobList();
		CreateVobList(radius);

		zCArray<zCVob*> vobList = this->vobList;
		zCArray<oCMobContainer*> chestsList;
		zCVob* pVob = NULL;
		oCMobContainer* chest = NULL;

		for (int i = 0; i < vobList.GetNum(); i++) {
			pVob = vobList.GetSafe(i);
			if (!pVob)
				continue;
			chest = zDYNAMIC_CAST<oCMobContainer>(pVob);
			if (!chest)
				continue;
			if (chest->lootAdded())
				continue;

			chest->addLoot();
		}
	}
}
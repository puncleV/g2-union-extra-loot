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

	void oCNpc::setNpcVar(int varIdx, int value = 1) {
		parser->SetInstance("NPCVARINST", this);
		parser->CallFunc(parser->GetIndex("SetNpcVar"), varIdx, value);
	}

	int oCNpc::getNpcVar(int varIdx) {
		parser->SetInstance("NPCVARINST", this);
		auto value = *(int*)parser->CallFunc(parser->GetIndex("GetNpcVar"), varIdx);

		return value;
	}

	bool oCNpc::isChampion() {
		return this->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX) == CHAMPION_VALUE;
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
			assignIdToNpc(npc);
			auto chapterLootWasGiven = npc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX);
			auto isChampion = false;
			
			if (chapterLootWasGiven == CHAMPION_VALUE || chapterLootWasGiven >= getCurrentChapter()) {
				return;
			}

			if (chapterLootWasGiven == 0 && randomizer.Random(0, 1000) < CHAMPION_CHANCE) {
				isChampion = true;
			}

			addLootToNPC(npc, isChampion);

			if (isChampion) {
				makeChampion(npc);
			} else if (chapterLootWasGiven != getCurrentChapter() && chapterLootWasGiven != CHAMPION_VALUE) {
				npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, getCurrentChapter());
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
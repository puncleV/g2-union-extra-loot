// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	bool addLootToNPC(oCNpc* npc, bool perChapterLoot = false) {
		if (ignoredNpcForLoot(npc)) {
			return FALSE;
		}

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, getCurrentChapter());

		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto lootGiven = -1;
		auto loot = lootTables;
		
		if (npc->isBoss()) {
			loot = bossLootTables;
		} else if (npc->isChampion()) {
			loot = championLootTables;
		} else if (perChapterLoot) {
			loot = perChapterLootTables;
		}

		for (const auto& lootTable : loot) {
		    lootGiven += addRandomLootToNpc(npc, lootTable);
		}

		return lootGiven;
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
			auto chapterLootWasGiven = npc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX);
			
			if (randomizer.Random(0, 1000) < CHAMPION_CHANCE && chapterLootWasGiven == 0) {
				makeChampion(npc);
				addLootToNPC(npc);
			}

			if (chapterLootWasGiven < getCurrentChapter() && getCurrentChapter() >= 1 && SHOULD_ADD_LOOT_TO_NPC || SHOULD_IGNORE_CHECK_TO_ADD_LOOT) {
				if (chapterLootWasGiven == 0) {
					addLootToNPC(npc);
				}
				else if (chapterLootWasGiven < getCurrentChapter() && TRADERS_LOOT_PER_CHAPTER) {
					addLootToNPC(npc, true);
				}
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
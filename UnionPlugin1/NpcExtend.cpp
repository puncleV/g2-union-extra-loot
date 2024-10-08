// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	bool addLootToNPC(oCNpc* npc) {
		if (ignoredNpcForLoot(npc)) {
			return FALSE;
		}

		npc->setNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX, TRUE);

		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto lootGiven = -1;

		if (RX_IsMageTrader(npc)) {
			lootGiven += addRandomLootToNpc(npc, magicLoot) ;
		}
		else if (RX_IsAlchemistTrader(npc)) {
			lootGiven += addRandomLootToNpc(npc, alchemistLoot) ;
		}
		else if (RX_IsHunterTrader(npc)) {
			lootGiven += addRandomLootToNpc(npc, hunterLoot) ;
		}
		else if (RX_IsSmithTrader(npc)) {
			lootGiven += addRandomLootToNpc(npc, smithLoot) ;
		}
		else if (RX_IsTrader(npc)) {
			lootGiven += addRandomLootToNpc(npc, tradersLoot) ;
		}
		else if (RX_IsBoss(npc)) {
			lootGiven += addRandomLootToNpc(npc) ;
			lootGiven += addRandomLootToNpc(npc, bossLoot) ;
		}
		else if (npc->IsHuman()) {
			lootGiven += addRandomLootToNpc(npc, humanLoot) ;
		}
		else {
			lootGiven += addRandomLootToNpc(npc, NPC_LOOT_TABLE) ;
		}

		if (!RX_IsTrader(npc) && lootGiven >= 0) {
			strengthenNpc(npc, lootGiven);
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

	void goThroughNpcHandlers(oCNpc* npc) {
		if (!npc) {
			return;
		}

		if (!npc->IsDead() && npc != oCNpc::player) {
			if (!npc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX) && SHOULD_ADD_LOOT_TO_NPC || SHOULD_IGNORE_CHECK_TO_ADD_LOOT) {
				if (randomizer.Random(0, 1000) < CHAMPION_CHANCE) {
					makeChampion(npc);
				}
				else {
					addLootToNPC(npc);
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
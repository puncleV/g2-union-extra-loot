// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// oCNpc extension methods

	// Get NPC's unique ID
	int oCNpc::getNpcId() {
		return this->aiscriptvars[AIVAR_FOR_NPC_ID];
	}

	// Check if NPC is a champion
	bool oCNpc::isChampion() {
		return npcVariables.getVariable(this->getNpcId(), NpcVariables::CHAPTER_LOOT_GIVEN_AT) == NpcVariables::CHAMPION;
	}

	// Check if NPC is a boss
	bool oCNpc::isBoss() {
		return (this->aiscriptvars[AIV_BOSS] == TRUE);
	}

	// Check if NPC is a summon
	bool oCNpc::isSummon() {
		return (this->aiscriptvars[AIV_SUMMON] == TRUE);
	}

	// Process all NPCs in radius for loot distribution
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

			// Handle dead NPCs
			if (npc->IsDead()) {
				giveLpToKiller(npc);
				deleteNpcVariables(npc);
				continue;
			}

			// Handle living NPCs
			goThroughNpcHandlers(npc);
		}

		return npcList;
	}

	// Randomize loot in all chests in radius
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

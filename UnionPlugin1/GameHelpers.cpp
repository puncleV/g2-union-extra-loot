// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Get current game chapter
	int getCurrentChapter() {
		int retVal = 0;
		zCPar_Symbol* ps = parser->GetSymbol("kapitel");
		if (ps)
			ps->GetValue(retVal, 0);
		else
			return -1;
		return retVal;
	}

	// Check if NPC should be ignored for loot
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
}

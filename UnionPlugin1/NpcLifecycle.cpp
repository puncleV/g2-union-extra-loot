// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Assign unique ID to NPC for tracking variables
	int assignIdToNpc(oCNpc* npc) {
		auto currentId = npc->aiscriptvars[AIVAR_FOR_NPC_ID];
		if (currentId == 0) {
			npc->aiscriptvars[AIVAR_FOR_NPC_ID] = npcVariables.getNextNpcId();
			npcVariables.setVariable(npc->aiscriptvars[AIVAR_FOR_NPC_ID], NpcVariables::CHAPTER_LOOT_GIVEN_AT, -1);
		}

		return npc->aiscriptvars[AIVAR_FOR_NPC_ID];
	}

	// Give LP to player if NPC was killed by player or companion
	void giveLpToKiller(oCNpc* npc) {
		int npcId = npc->getNpcId();

		if (npcId <= 0) {
			return;
		}

		oCNpc* killer = npc->enemy;

		// Only give LP if killed by player or companion
		if (killer == NULL || (killer != player && !killer->aiscriptvars[AIV_PARTYMEMBER])) {
			return;
		}

		if (npcVariables.getVariable(npcId, NpcVariables::VariableKey::LP_INCREASE) > 0) {
			player->learn_points += npcVariables.getVariable(npcId, NpcVariables::VariableKey::LP_INCREASE);

			zCPar_Symbol* sym = parser->GetSymbol("PV_LP_GIVEN");
			if (sym) {
				sym->SetValue(Z npcVariables.getVariable(npcId, NpcVariables::VariableKey::LP_INCREASE), 0);
			}
			parser->CallFunc(parser->GetIndex("print_pv_lp"));
			npcVariables.setVariable(npcId, NpcVariables::VariableKey::LP_INCREASE, 0);
		}
	}

	// Delete NPC variables and clean up
	int deleteNpcVariables(oCNpc* npc) {
		if (!CLEANUP_NPCS) {
			return 0;
		}
		if (!npc) {
			return 0;
		}

		int npcId = npc->getNpcId();
		if (npcId <= 0) {
			return 0;
		}

		npcVariables.deleteNpc(npcId);
		npc->aiscriptvars[AIVAR_FOR_NPC_ID] = -1;
		return 1;
	}
}

// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {
	void Game_Entry() {
	}

	void fillLootTables() {
		jsonConfig.lootTable();
	}

	string GetEngineVersionName(TEngineVersion version) {
		switch (version) {
		case Engine_G1:  return "Gothic I Classic";
		case Engine_G1A: return "Gothic I Addon";
		case Engine_G2:  return "Gothic II Classic";
		case Engine_G2A: return "Gothic II Addon";
		}
		return "Unknown";
	}

	void Game_Init() {
		RegisterCommands();
		updateConstantsWithOptions();
		jsonConfig.loadConfig();
		fillLootTables();
	}
	void Game_Exit() {
	}

	void Game_PreLoop() {
	}

	void Game_Loop() {
		player->goThroughNpcsInRadius(3500);
		player->randomizeChestsInRadius(1500);

		auto focusNpc = player->GetFocusNpc();
		if (IS_DEBUG) {

			if (focusNpc) {
				int npcId = focusNpc->getNpcId();
				int lootGiven = npcVariables.getVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT);
				ogame->game_text->Printwin("Loot given: " + Z lootGiven);
				ogame->game_text->Printwin("Debug mode: " + Z IS_DEBUG);
				ogame->game_text->Printwin("Npc Name: " + Z focusNpc->GetObjectName());
				ogame->game_text->Printwin("Npc ID: " + Z npcId);
			}

			auto focusVob = player->GetFocusVob();

			if (focusVob) {
				ogame->game_text->Printwin("Vob name: " + focusVob->GetObjectName());
			}
		}

		if (focusNpc) {
			if (focusNpc->isChampion() && !focusNpc->name[0].HasWordI("Champ")) {
				focusNpc->name[0] += Z " Champion";
			}
		}
	}

	void Game_PostLoop() {
	}

	void Game_MenuLoop() {
	}

	void Game_SaveBegin() {
		string rootDir = zoptions->GetDirString(DIR_ROOT);
		string dir = zoptions->GetDirString(zTOptionPaths::DIR_SAVEGAMES);
		string savePath = string::Combine("%s\\%s\\current\\EXTRALOOTNPCDATA.SAV", rootDir, dir);
		npcVariables.saveToFile(savePath.ToChar());
	}

	void Game_SaveEnd() {
	}

	TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;
	int slot = SaveLoadGameInfo.slotID;

	void LoadBegin() {
		
	}

	void LoadEnd() {
		npcVariables.clear();
		string rootDir = zoptions->GetDirString(DIR_ROOT);
		string dir = zoptions->GetDirString(zTOptionPaths::DIR_SAVEGAMES);
		string savePath = string::Combine("%s\\%s\\current\\EXTRALOOTNPCDATA.SAV", rootDir, dir);
		npcVariables.loadFromFile(savePath.ToChar());
	}

	void Game_LoadBegin_NewGame() {
		LoadBegin();
	}

	void Game_LoadEnd_NewGame() {
		LoadEnd();
	}

	void Game_LoadBegin_SaveGame() {
		LoadBegin();

	}

	void Game_LoadEnd_SaveGame() {
		LoadEnd();
	}

	void Game_LoadBegin_ChangeLevel() {
		LoadBegin();
	}

	void Game_LoadEnd_ChangeLevel() {
		LoadEnd();
	}

	void Game_LoadBegin_Trigger() {
	}

	void Game_LoadEnd_Trigger() {
	}

	void Game_Pause() {
	}

	void Game_Unpause() {
	}

	void Game_DefineExternals() {
		RegisterExternals_punclev();
	}

	void Game_ApplyOptions() {
	}

	/*
	Functions call order on Game initialization:
	  - Game_Entry           * Gothic entry point
	  - Game_DefineExternals * Define external script functions
	  - Game_Init            * After DAT files init

	Functions call order on Change level:
	  - Game_LoadBegin_Trigger     * Entry in trigger
	  - Game_LoadEnd_Trigger       *
	  - Game_Loop                  * Frame call window
	  - Game_LoadBegin_ChangeLevel * Load begin
	  - Game_SaveBegin             * Save previous level information
	  - Game_SaveEnd               *
	  - Game_LoadEnd_ChangeLevel   *

	Functions call order on Save game:
	  - Game_Pause     * Open menu
	  - Game_Unpause   * Click on save
	  - Game_Loop      * Frame call window
	  - Game_SaveBegin * Save begin
	  - Game_SaveEnd   *

	Functions call order on Load game:
	  - Game_Pause              * Open menu
	  - Game_Unpause            * Click on load
	  - Game_LoadBegin_SaveGame * Load begin
	  - Game_LoadEnd_SaveGame   *
	*/

#define AppDefault True
	CApplication* lpApplication = !CHECK_THIS_ENGINE ? Null : CApplication::CreateRefApplication(
		Enabled(AppDefault) Game_Entry,
		Enabled(AppDefault) Game_Init,
		Enabled(AppDefault) Game_Exit,
		Enabled(AppDefault) Game_PreLoop,
		Enabled(AppDefault) Game_Loop,
		Enabled(AppDefault) Game_PostLoop,
		Enabled(AppDefault) Game_MenuLoop,
		Enabled(AppDefault) Game_SaveBegin,
		Enabled(AppDefault) Game_SaveEnd,
		Enabled(AppDefault) Game_LoadBegin_NewGame,
		Enabled(AppDefault) Game_LoadEnd_NewGame,
		Enabled(AppDefault) Game_LoadBegin_SaveGame,
		Enabled(AppDefault) Game_LoadEnd_SaveGame,
		Enabled(AppDefault) Game_LoadBegin_ChangeLevel,
		Enabled(AppDefault) Game_LoadEnd_ChangeLevel,
		Enabled(AppDefault) Game_LoadBegin_Trigger,
		Enabled(AppDefault) Game_LoadEnd_Trigger,
		Enabled(AppDefault) Game_Pause,
		Enabled(AppDefault) Game_Unpause,
		Enabled(AppDefault) Game_DefineExternals,
		Enabled(AppDefault) Game_ApplyOptions
	);
}
// This file added in headers queue
// File: "Sources.h"
#include "resource.h"

namespace GOTHIC_ENGINE {
	auto initialized = 0;

	void Game_Entry() {
	}

	void fillLootTables(){
		bossLoot = jsonConfig.lootTable("boss-loot");
		alchemistLoot = jsonConfig.lootTable("alchemist-loot");
		magicLoot = jsonConfig.lootTable("magic-loot");
		tradersLoot = jsonConfig.lootTable("traders-loot");
		NPC_LOOT_TABLE = jsonConfig.lootTable("base-table");
		humanLoot = jsonConfig.lootTable("human-loot");
		smithLoot = jsonConfig.lootTable("smith-loot");
		hunterLoot = jsonConfig.lootTable("hunter-loot");
		
		if (SHOULD_USE_NPC_LOOT_FOR_CHESTS) {
			chestsLoot = NPC_LOOT_TABLE;
		}
		else {
			chestsLoot = jsonConfig.lootTable("chest-loot");
		}

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
		initialized = 1;
	}
	void Game_Exit() {
	}

	void Game_PreLoop() {
	}

	void Game_Loop() {
		/*if (!initialized) {
			RegisterCommands();
			updateConstantsWithOptions();
			jsonConfig.loadConfig();
			fillLootTables();
			initialized = 1;
		}*/

		player->getNpcInRadius(3500);

		if (IS_DEBUG) {
			auto focusNpc = player->GetFocusNpc();

			if (focusNpc) {
				screen->PrintCY(500, Z JSON_FILE_NAME + " L: " + Z focusNpc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX));
			}

			auto focusVob = player->GetFocusVob(); 

			if (focusVob) {
				screen->PrintCY(1000, focusVob->GetObjectName());
			}
		}
	}

	void Game_PostLoop() {
	}

	void Game_MenuLoop() {
	}

	// Information about current saving or loading world
	TSaveLoadGameInfo& SaveLoadGameInfo = UnionCore::SaveLoadGameInfo;

	void Game_SaveBegin() {
	}

	void Game_SaveEnd() {
	}

	void LoadBegin() {
	}

	void LoadEnd() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;

		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);

				if (npc == oCNpc::player || !npc->IsHuman())
					continue;

				goThroughNpcHandlers(npc);
			}
		}
		
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
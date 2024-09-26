// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	int (*innerEvalFunc)(const zSTRING&, zSTRING&);

	bool lootRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("IGNORE_LOOT_CHECKS")) {
			SHOULD_IGNORE_CHECK_TO_ADD_LOOT = SHOULD_IGNORE_CHECK_TO_ADD_LOOT ? 0 : 1;
			return true;
		}

		if (inpstr.HasWordI("ADD_LOOT_TO_PLAYER")) {
			SHOULD_ADD_LOOT_TO_PLAYER = SHOULD_ADD_LOOT_TO_PLAYER ? 0 : 1;

			msg = "Should add to player value: " + Z SHOULD_ADD_LOOT_TO_PLAYER;
			return true;
		}

		if (inpstr.HasWordI("LOOT_NPCS")) {
			auto result = addRandomNpcLoot();
			msg = "Changed drop of: " + Z result + " npcs.";

			return true;
		}

		return false;
	}

	bool chestsRandomizerHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("LOOT_CHESTS")) {
			auto result = addRandomChestsLoot();

			msg = "Added: " + Z result + " items.";

			return true;
		}

		return false;
	}

	bool makeChampionHandler(const zSTRING& inpstr, zSTRING& msg) {
		if (inpstr.HasWordI("MAKE_CHAMPION")) {
			auto focusNpc = player->GetFocusNpc();

			if (focusNpc) {
				msg = "Made a champion from: " + focusNpc->GetObjectName() + ".";
				makeChampion(focusNpc);
			}

			return true;
		}

		return false;
		
	}

	int ConsoleEvalFunc(const zSTRING& inpstr, zSTRING& msg) {
		if (innerEvalFunc && innerEvalFunc(inpstr, msg))
			return true;

		if (inpstr.HasWordI("punclevutils")) {
			if (inpstr.HasWordI("debug")) {
				IS_DEBUG = IS_DEBUG ? 0 : 1;
				msg = "Debug: " + IS_DEBUG;
				return true;
			}

			return lootRandomizerHandler(inpstr, msg) || chestsRandomizerHandler(inpstr, msg) || makeChampionHandler(inpstr, msg);
		}

		return false;
	}

	void RegisterEvalFunc() {
		int evalNum = 0;

		for (int i = 1; i < zCON_MAX_EVAL; i++)
			if (zcon->evalfunc[i])
				evalNum = i;

		innerEvalFunc = zcon->evalfunc[evalNum];
		zcon->evalfunc[evalNum] = &ConsoleEvalFunc;
	}

	void RegisterCommands() {
		RegisterEvalFunc();
		zcon->Register("punclevutils LOOT_CHESTS", "Adds loot to chests");
		zcon->Register("punclevutils LOOT_NPCS", "Adds loot to NPCs");
		zcon->Register("punclevutils ADD_LOOT_TO_PLAYER", "Toggle add loot to a player");
		zcon->Register("punclevutils IGNORE_LOOT_CHECKS", "Toggle ignore loot checks");
		zcon->Register("punclevutils MAKE_CHAMPION", "Makes a target npc a champion");
	}
}
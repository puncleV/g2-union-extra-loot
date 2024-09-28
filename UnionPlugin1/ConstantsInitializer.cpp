// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		EXTRA_LOOT_BASE_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootChance", 100);
		EXTRA_LOOT_CHEST_BASE_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ChestsExtraLootChance", 450);
		EXTRA_LOOT_CHEST_UPPERBOUND = zoptions->ReadInt("PUNCLEVUTILS", "ChestsExtraLootUpperbound", 1000);
		CHESTS_BOSS_DROP_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ChestsBossDropChance", 10);
		EXTRA_LOOT_BASE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "BaseStrengthMultiplierForAddedLoot", 1);
		EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "ValueBasedStrengthMultiplier", 250);
		ENEMY_STATS_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyStatsPerMultiplier", 25);
		ENEMY_DEFENCE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyDefencePerMultiplier", 3);
		ENEMY_HP_FACTOR = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyBaseHP", 150);

		CHAMPION_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ChampionChance", 5);
		CHAMPION_LOOT_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ChampionLootChance", 25);
		CHAMPION_STRENGTHEN_VALUE = zoptions->ReadInt("PUNCLEVUTILS", "ChampionStrengthenValue", 2000);

		MAX_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEVUTILS", "MaxStrengthenValue", 2000);
		MIN_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEVUTILS", "MinStrengthenValue", 100);

		SHOULD_ADD_LOOT_TO_NPC = zoptions->ReadBool("PUNCLEVUTILS", "ShouldAddLootToNpc", FALSE);
		SHOULD_ADD_LOOT_TO_CHESTS = zoptions->ReadBool("PUNCLEVUTILS", "ShouldAddLootToChests", FALSE);
		SHOULD_USE_NPC_LOOT_FOR_CHESTS = zoptions->ReadBool("PUNCLEVUTILS", "ShouldUseNpcLootForChests", FALSE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEVUTILS", "Debug", FALSE);
		JSON_FILE_NAME = zoptions->ReadString("PUNCLEVUTILS", "JsonFileName", "punclev-utils.json");
	}
}
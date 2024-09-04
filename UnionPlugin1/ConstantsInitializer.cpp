// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		EXTRA_LOOT_BASE_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootChance", 15);
		EXTRA_LOOT_HP_FACTOR_HORINIS = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorHorinis", 400);
		EXTRA_LOOT_HP_FACTOR_OTHER = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorOther", 700);
		EXTRA_LOOT_HP_FACTOR_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHpFactorMultiplier", 25);
		EXTRA_LOOT_HORINIS_FACTOR = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootHorinisFactor", 1000);
		EXTRA_LOOT_OTHER_FACTOR = zoptions->ReadInt("PUNCLEVUTILS", "ExtraLootOtherFactor", 1250);
		EXTRA_LOOT_CHEST_BASE_CHANCE = zoptions->ReadInt("PUNCLEVUTILS", "ChestsExtraLootChance", 450);
		EXTRA_LOOT_BASE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "BaseStrengthMultiplierForAddedLoot", 1);
		EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "ValueBasedStrengthMultiplier", 250);
		ENEMY_STATS_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyStatsPerMultiplier", 25);
		ENEMY_DEFENCE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyDefencePerMultiplier", 3);
		ENEMY_HP_FACTOR = zoptions->ReadInt("PUNCLEVUTILS", "StrengthenEnemyBaseHP", 150);

		SHOULD_ADD_LOOT_TO_NPC = zoptions->ReadBool("PUNCLEVUTILS", "ShouldAddLootToNpc", FALSE);
		SHOULD_ADD_LOOT_TO_CHESTS = zoptions->ReadBool("PUNCLEVUTILS", "ShouldAddLootToChests", FALSE);
		SHOULD_USE_NPC_LOOT_FOR_CHESTS = zoptions->ReadBool("PUNCLEVUTILS", "ShouldUseNpcLootForChests", TRUE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEVUTILS", "Debug", FALSE);
		JSON_FILE_NAME = zoptions->ReadString("PUNCLEVUTILS", "JsonFileName", "punclev-utils.json");
	}
}
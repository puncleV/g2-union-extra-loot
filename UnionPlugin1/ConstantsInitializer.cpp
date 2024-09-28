// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		EXTRA_LOOT_BASE_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ExtraLootChance", 100);
		EXTRA_LOOT_CHEST_BASE_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChestsExtraLootChance", 450);
		EXTRA_LOOT_CHEST_UPPERBOUND = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChestsExtraLootUpperbound", 1000);
		CHESTS_BOSS_DROP_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChestsBossDropChance", 10);
		EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ValueBasedStrengthMultiplier", 250);
		
		ENEMY_STATS_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyStatsPerMultiplier", 25);
		ENEMY_DEFENCE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyDefencePerMultiplier", 3);
		ENEMY_HP_PERCENT_INCREASE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyHpPercentIncreasePerMultiplier", 10);

		ENEMY_HP_GROW_LIMIT_PERCENT	 = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitHpGrowPercent", 125);
		ENEMY_STATS_GROW_LIMIT_PERCENT	 = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitStatsGrowPercent", 30);
		ENEMY_DEFENCE_GROW_LIMIT_PERCENT = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitDefenceGrowPercent", 30);

		CHAMPION_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionChance", 5);
		CHAMPION_LOOT_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionLootChance", 25);
		CHAMPION_STRENGTHEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionStrengthenValue", 3000);

		MAX_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "MaxStrengthenValue", 3000);
		MIN_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "MinStrengthenValue", 250);

		SHOULD_ADD_LOOT_TO_NPC = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldAddLootToNpc", TRUE);
		SHOULD_ADD_LOOT_TO_CHESTS = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldAddLootToChests", TRUE);
		SHOULD_USE_NPC_LOOT_FOR_CHESTS = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldUseNpcLootForChests", FALSE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "Debug", FALSE);
		JSON_FILE_NAME = zoptions->ReadString("PUNCLEV_ADDITIONAL_LOOT", "JsonFileName", "punclev-utils.json");
	}
}
// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void updateConstantsWithOptions() {
		EXTRA_LOOT_BASE_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ExtraLootChance", 100);
		EXTRA_LOOT_CHEST_BASE_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChestsExtraLootChance", 100);
		EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ValueBasedStrengthMultiplier", 250);
		
		ENEMY_STATS_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyStatsPerMultiplier", 25);
		ENEMY_DEFENCE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyDefencePerMultiplier", 3);
		ENEMY_HP_PERCENT_INCREASE_PER_MULTIPLIER = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenEnemyHpPercentIncreasePerMultiplier", 10);

		ENEMY_HP_GROW_LIMIT_PERCENT	 = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitHpGrowPercent", 125);
		ENEMY_STATS_GROW_LIMIT_PERCENT	 = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitStatsGrowPercent", 30);
		ENEMY_DEFENCE_GROW_LIMIT_PERCENT = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "StrengthenLimitDefenceGrowPercent", 30);

		CHAMPION_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionChance", 5);
		CHAMPION_STRENGTHEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionStrengthenValue", 3000);
		CHAMPION_EXTRA_LEVEL = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionExtraLevel", 5);
		CHAMPION_LP_CHANCE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionLpChance", 35);
		CHAMPION_LP_INCREASE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionLpIncrease", 1);
		CHAMPION_STRENGHTEN_VALUE_PER_LP = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionStrentghenPerLpValue", 350);
		
		CHAMPION_MIN_STATS = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionMinStats", 175);
		CHAMPION_MAX_STATS = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionMaxStats", 1250);
		CHAMPION_MIN_HP = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionMinHp", 1000);
		CHAMPION_MAX_HP = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "ChampionMaxHp", 35000);

		MAX_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "MaxStrengthenValue", 3000);
		MIN_STRENGHTEN_VALUE = zoptions->ReadInt("PUNCLEV_ADDITIONAL_LOOT", "MinStrengthenValue", 250);

		TRADERS_LOOT_PER_CHAPTER = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "TradersLootPerChapter", TRUE);
		SHOULD_ADD_LOOT_TO_NPC = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldAddLootToNpc", TRUE);
		SHOULD_ADD_LOOT_TO_CHESTS = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldAddLootToChests", TRUE);
		SHOULD_USE_NPC_LOOT_FOR_CHESTS = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "ShouldUseNpcLootForChests", FALSE);
		BOSSIFY_CHAMPIONS = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "BossifyChampions", FALSE);
		IS_DEBUG = zoptions->ReadBool("PUNCLEV_ADDITIONAL_LOOT", "Debug", FALSE);
		JSON_FILE_NAME = zoptions->ReadString("PUNCLEV_ADDITIONAL_LOOT", "JsonFileName", "punclev-utils.json");
	}
}
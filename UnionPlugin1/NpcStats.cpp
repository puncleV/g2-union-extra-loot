// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Increase NPC protection for a specific damage type
	void increaseProtection(oCNpc* npc, oEIndexDamage protectionType, int strengthMultiplier) {
		if (npc->protection[protectionType] != -1) {
			auto maxIncreased = npc->protection[protectionType] * (ENEMY_DEFENCE_GROW_LIMIT_PERCENT / 100.);
			auto increasedProtection = ENEMY_DEFENCE_PER_MULTIPLIER * strengthMultiplier;
			npc->protection[protectionType] += min(increasedProtection, maxIncreased);
		}
	}

	// Increase NPC attribute (strength, dexterity, etc.)
	void increaseAttribute(oCNpc* npc, int attributeType, int strengthMultiplier) {
		auto maxIncreased = npc->attribute[attributeType] * (ENEMY_STATS_GROW_LIMIT_PERCENT / 100.);
		auto increasedAttribute = ENEMY_STATS_PER_MULTIPLIER * strengthMultiplier;

		npc->attribute[attributeType] += min(increasedAttribute, maxIncreased);
	}

	// Ensure champion has minimum stats
	void minChampionStats(oCNpc* npc) {
		if (npc->attribute[NPC_ATR_HITPOINTSMAX] < CHAMPION_MIN_HP) {
			npc->attribute[NPC_ATR_HITPOINTSMAX] = CHAMPION_MIN_HP;
			npc->attribute[NPC_ATR_HITPOINTS] = CHAMPION_MIN_HP;
		}
		if (npc->attribute[NPC_ATR_STRENGTH] < CHAMPION_MIN_STATS) {
			npc->attribute[NPC_ATR_STRENGTH] = CHAMPION_MIN_STATS;
		}
		if (npc->attribute[NPC_ATR_DEXTERITY] < CHAMPION_MIN_STATS) {
			npc->attribute[NPC_ATR_DEXTERITY] = CHAMPION_MIN_STATS;
		}
	}

	// Cap champion stats at maximum values
	void maxChampionStats(oCNpc* npc) {
		if (npc->attribute[NPC_ATR_HITPOINTSMAX] > CHAMPION_MAX_HP) {
			npc->attribute[NPC_ATR_HITPOINTSMAX] = CHAMPION_MAX_HP;
			npc->attribute[NPC_ATR_HITPOINTS] = CHAMPION_MAX_HP;
		}
		if (npc->attribute[NPC_ATR_STRENGTH] > CHAMPION_MAX_STATS) {
			npc->attribute[NPC_ATR_STRENGTH] = CHAMPION_MAX_STATS;
		}
		if (npc->attribute[NPC_ATR_DEXTERITY] > CHAMPION_MAX_STATS) {
			npc->attribute[NPC_ATR_DEXTERITY] = CHAMPION_MAX_STATS;
		}
	}

	// Strengthen NPC based on loot value given
	void strengthenNpc(oCNpc* npc, int itemValue = 1) {
		if (npc == player || !SHOULD_STRENGHTEN_ENEMIES) {
			return;
		}

		auto adjustedItemValue = itemValue;

		if (adjustedItemValue < MIN_STRENGHTEN_VALUE) {
			adjustedItemValue = MIN_STRENGHTEN_VALUE;
		}
		else if (adjustedItemValue > MAX_STRENGHTEN_VALUE) {
			adjustedItemValue = MAX_STRENGHTEN_VALUE;
		}
		else {
			adjustedItemValue = adjustedItemValue * 1.25;
		}

		auto addStrengthMultiplier = (int)(adjustedItemValue / EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER);

		if (addStrengthMultiplier == 0) {
			addStrengthMultiplier = 1;
		}

		int hpMultiplier = npc->attribute[NPC_ATR_HITPOINTSMAX] * (ENEMY_HP_PERCENT_INCREASE_PER_MULTIPLIER / 100.);
		int additionalHp = randomizer.Random(hpMultiplier, hpMultiplier * addStrengthMultiplier);

		int limitedAdditionalHp = min((npc->attribute[NPC_ATR_HITPOINTSMAX] * (ENEMY_HP_GROW_LIMIT_PERCENT / 100.)), additionalHp);

		npc->attribute[NPC_ATR_HITPOINTSMAX] += limitedAdditionalHp;
		npc->attribute[NPC_ATR_HITPOINTS] += limitedAdditionalHp;

		increaseAttribute(npc, NPC_ATR_STRENGTH, addStrengthMultiplier);
		increaseAttribute(npc, NPC_ATR_DEXTERITY, addStrengthMultiplier);

		increaseProtection(npc, oEDamageIndex_Blunt, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Edge, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Fire, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Point, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Magic, addStrengthMultiplier);
	}
}

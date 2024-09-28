// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	void increaseProtection(oCNpc* npc, oEIndexDamage protectionType, int strengthMultiplier) {
		if (npc->protection[protectionType] != -1) {
			auto maxIncreased = npc->protection[protectionType] * (ENEMY_DEFENCE_GROW_LIMIT_PERCENT / 100.);
			auto increasedProtection = ENEMY_DEFENCE_PER_MULTIPLIER * strengthMultiplier;
			npc->protection[protectionType] += min(increasedProtection, maxIncreased);
		}
	}

	void increaseAtribute(oCNpc* npc, int attributeType, int strengthMultiplier) {
		auto maxIncreased = npc->attribute[attributeType] * (ENEMY_STATS_GROW_LIMIT_PERCENT / 100.);
		auto increasedAttribute =ENEMY_STATS_PER_MULTIPLIER * strengthMultiplier;

		npc->attribute[attributeType] += min(increasedAttribute, maxIncreased);
	}


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

		increaseAtribute(npc, NPC_ATR_STRENGTH, addStrengthMultiplier);
		increaseAtribute(npc, NPC_ATR_DEXTERITY, addStrengthMultiplier);

		increaseProtection(npc, oEDamageIndex_Blunt, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Edge, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Fire, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Point, addStrengthMultiplier);
		increaseProtection(npc, oEDamageIndex_Magic, addStrengthMultiplier);
	}
}
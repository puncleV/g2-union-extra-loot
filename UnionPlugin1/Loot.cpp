// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {

	class Loot {
	private:
		std::set <zSTRING> npcIgnoreList;
		int probability;
		int probabilityOutOf;
		int minAmount;
		int maxAmount;

		int getRandomItemAmount(oCItem* item) {
			auto itemName = item->GetObjectName();

			if (minAmount == maxAmount) {
				return minAmount;
			}

			return randomizer.Random(minAmount, maxAmount);
		}

		oCItem* getItemWithAmount(zSTRING name) {
			oCItem* item = static_cast<oCItem*>(ogame->GetGameWorld()->CreateVob_novt(zVOB_TYPE_ITEM, name));

			if (!item) {
				return nullptr;
			}

			if (item->HasFlag(ITM_FLAG_MULTI)) {
				item->amount = getRandomItemAmount(item);
			}

			return item;
		}
	public:
		std::vector <zSTRING> possibleLootNames;

		Loot(int _chanceWeight, int _chanceUpperbound, std::vector <zSTRING> _possibleLootNames, int _minAmount = 1, int _maxAmount = 1) {
			possibleLootNames = _possibleLootNames;
			probability = _chanceWeight;
			probabilityOutOf = _chanceUpperbound;
			minAmount = _minAmount;
			maxAmount = _maxAmount;
		};

		bool tryAddToNpc(oCNpc* npc) {
			if (!npc) {
				return FALSE;
			}

			if (randomizer.Random(0, probabilityOutOf) <= probability) {
				auto itemName = randomizer.getRandomArrayElement(possibleLootNames);
				auto item = getItemWithAmount(itemName);

				if (item == nullptr) {
					return FALSE;
				}

				if (SHOULD_ADD_LOOT_TO_PLAYER) {
					player->PutInInv(item);
				}
				else {
					npc->PutInInv(item);
					strengthenNpc(npc, item->value * item->amount);
				}

				item->Release();

				return TRUE;
			}

			return FALSE;
		};

		void strengthenNpc(oCNpc* npc, int itemValue = 1) {
			if (npc == player || !SHOULD_STRENGHTEN_ENEMIES) {
				return;
			}

			auto addStrengthMultiplier = (int)(itemValue / EXTRA_LOOT_VALUE_STRENGTH_PER_LOOT_MULTIPLIER) + EXTRA_LOOT_BASE_STRENGTH_PER_LOOT_MULTIPLIER;
			auto extaHpBasePercent = ENEMY_HP_FACTOR / npc->attribute[NPC_ATR_HITPOINTSMAX];
			int additionalHp = randomizer.Random(50 * addStrengthMultiplier, npc->attribute[NPC_ATR_HITPOINTSMAX] * extaHpBasePercent * addStrengthMultiplier);

			npc->attribute[NPC_ATR_HITPOINTSMAX] += additionalHp;
			npc->attribute[NPC_ATR_HITPOINTS] += additionalHp;
			npc->attribute[NPC_ATR_STRENGTH] += ENEMY_STATS_PER_MULTIPLIER * addStrengthMultiplier;
			npc->attribute[NPC_ATR_DEXTERITY] += ENEMY_STATS_PER_MULTIPLIER * addStrengthMultiplier;

			if (npc->protection[oEDamageIndex_Blunt] != -1) {
				npc->protection[oEDamageIndex_Blunt] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Edge] != -1) {
				npc->protection[oEDamageIndex_Edge] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}
			
			if (npc->protection[oEDamageIndex_Fire] != -1) {
				npc->protection[oEDamageIndex_Fire] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Point] != -1) {
				npc->protection[oEDamageIndex_Point] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}

			if (npc->protection[oEDamageIndex_Magic] != -1) {
				npc->protection[oEDamageIndex_Magic] += ENEMY_DEFENCE_PER_MULTIPLIER * addStrengthMultiplier;
			}
		}

		bool tryAddToChest(oCMobContainer* chest) {
			if (!chest) {
				return FALSE;
			}

			if (randomizer.Random(0, probabilityOutOf) <= probability) {
				auto itemName = randomizer.getRandomArrayElement(possibleLootNames);

				auto item = getItemWithAmount(itemName);

				if (SHOULD_ADD_LOOT_TO_PLAYER) {
					player->PutInInv(item);
				}
				else {
					chest->Insert(item);
				}

				item->Release();

				return TRUE;
			}

			return FALSE;
		};
	};
}
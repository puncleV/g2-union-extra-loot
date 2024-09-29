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
		bool amountMeansPicks;

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

			if (item->HasFlag(ITM_FLAG_MULTI) && !amountMeansPicks) {
				item->amount = getRandomItemAmount(item);
			}
			else {
				item->amount = 1;
			}

			return item;
		}
	public:
		std::vector <zSTRING> possibleLootNames;

		Loot(int _chanceWeight, int _chanceUpperbound, std::vector <zSTRING> _possibleLootNames, int _minAmount = 1, int _maxAmount = 1, bool _amountMeansPicks = 1) {
			possibleLootNames = _possibleLootNames;
			probability = _chanceWeight;
			probabilityOutOf = _chanceUpperbound;
			minAmount = _minAmount;
			maxAmount = _maxAmount;
			amountMeansPicks = _amountMeansPicks;
		};

		int addItemToNpc(oCNpc* npc) {
			auto itemName = randomizer.getRandomArrayElement(possibleLootNames);
			auto item = getItemWithAmount(itemName);
			auto value = -1;

			if (item == nullptr) {
				return value;
			}

			value = item->value ? item->value: 1;

			if (SHOULD_ADD_LOOT_TO_PLAYER) {
				player->PutInInv(item);
			}
			else {
				npc->PutInInv(item);
			}

			item->Release();

			return value;
		}

		int tryAddToNpc(oCNpc* npc) {
			if (!npc) {
				return 0;
			}
			auto sumValue = 0;
			if (randomizer.Random(0, probabilityOutOf) <= (probability * (EXTRA_LOOT_BASE_CHANCE / 100.))) {
				if (amountMeansPicks) {
					auto picks = randomizer.Random(1, maxAmount);
					for (auto i = minAmount - 1; i < picks; i += 1) {
						sumValue += addItemToNpc(npc);
					}
				}
				else {
					sumValue += addItemToNpc(npc);
				}
			}

			return sumValue;
		};

		bool addItemToChest(oCMobContainer* chest) {
			auto itemName = randomizer.getRandomArrayElement(possibleLootNames);
			auto item = getItemWithAmount(itemName);
			
			if (item == nullptr) {
				return false;
			}

			if (SHOULD_ADD_LOOT_TO_PLAYER) {
				player->PutInInv(item);
			}
			else {
				chest->Insert(item);
			}

			item->Release();

			return true;
		}

		bool tryAddToChest(oCMobContainer* chest) {
			if (!chest) {
				return false;
			}

			if (randomizer.Random(0, probabilityOutOf) <= probability) {
				if (amountMeansPicks) {
					auto addedSomething = false;
					auto picks = randomizer.Random(1, maxAmount);

					for (auto i = minAmount - 1; i < picks; i += 1) {
						addedSomething = addItemToChest(chest) || addedSomething;
					}
					return addedSomething;
				}
				else {
					return addItemToChest(chest);
				}
			}

			return false;
		};
	};
}
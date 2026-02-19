// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {

    class Loot {
    private:
        std::set <zSTRING> npcs;
        int probability;
        int probabilityOutOf;
        int minAmount;
        int maxAmount;
        int maxPerLocation;
        int valueOverride;
        bool amountMeansPicks;

        int getRandomItemAmount(oCItem* item) const {
            if (minAmount == maxAmount) {
                return minAmount;
            }

            return randomizer.Random(minAmount, maxAmount);
        }

        oCItem* getItemWithAmount(zSTRING name) const {
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

        // Get available items (not at maxPerLocation limit)
        std::vector<zSTRING> getAvailableItems() const {
            if (maxPerLocation <= 0) {
                return possibleLootNames; // No limit, return all
            }

            std::vector<zSTRING> available;
            for (const auto& itemName : possibleLootNames) {
                if (saveData.canGiveItem(itemName, maxPerLocation)) {
                    available.push_back(itemName);
                }
            }
            return available;
        }

    public:
        std::vector <zSTRING> possibleLootNames;

        Loot(int _chanceWeight, int _chanceUpperbound, std::vector <zSTRING> _possibleLootNames, int _minAmount = 1, int _maxAmount = 1, bool _amountMeansPicks = 1, int _valueOverride = -1, int _maxPerLocation = -1) {
            possibleLootNames = _possibleLootNames;
            probability = _chanceWeight;
            probabilityOutOf = _chanceUpperbound;
            minAmount = _minAmount;
            maxAmount = _maxAmount;
            amountMeansPicks = _amountMeansPicks;
            valueOverride = _valueOverride;
            maxPerLocation = _maxPerLocation;
        };

        int addItemToNpc(oCNpc* npc, bool steal = false) const {
            auto lootNames = getAvailableItems();
			
            if (lootNames.empty()) {
                if (IS_DEBUG) {
                    ogame->game_text->Printwin("No available items to add (all at limit)");
                }
                return -1; // No items available
			}

            auto itemName = randomizer.getRandomArrayElement(lootNames);
            
            if (IS_DEBUG && maxPerLocation > 0) {
                int currentCount = saveData.getItemGivenCount(itemName);
                ogame->game_text->Printwin("Trying " + itemName + " - current: " + Z currentCount + "/" + Z maxPerLocation);
            }
            
            // Check maxPerLocation limit if set
            if (maxPerLocation > 0 && !saveData.canGiveItem(itemName, maxPerLocation)) {
                if (IS_DEBUG) {
                    ogame->game_text->Printwin("BLOCKED: " + itemName + " at limit");
                }
                return -1; // Item limit reached
            }
            
            auto item = getItemWithAmount(itemName);
            auto value = -1;

            if (item == nullptr) {
                return value;
            }

            // Adjust amount if it would exceed maxPerLocation limit
            if (maxPerLocation > 0) {
                int currentCount = saveData.getItemGivenCount(itemName);
                int remainingAllowed = maxPerLocation - currentCount;
                
                if (remainingAllowed <= 0) {
                    item->Release();
                    return -1;
                }
                
                // Cap the amount to not exceed limit
                if (item->amount > remainingAllowed) {
                    item->amount = remainingAllowed;
                }
            }

            if (valueOverride >= 0) {
                value = valueOverride * item->amount;
            }
            else {
                value = (item->value ? item->value : 1) * item->amount;
            }

            if (SHOULD_ADD_LOOT_TO_PLAYER) {
                player->PutInInv(item);
            }
            else {
                npc->PutInInv(item);
            }

            // Track the actual amount given
            if (maxPerLocation > 0) {
                saveData.incrementItemGiven(itemName, item->amount);
                if (IS_DEBUG) {
                    int newCount = saveData.getItemGivenCount(itemName);
                    ogame->game_text->Printwin("SUCCESS: Gave " + Z item->amount + "x " + itemName + " (total: " + Z newCount + "/" + Z maxPerLocation + ")");
                }
            }

            if (steal) {
                zCPar_Symbol* sym = parser->GetSymbol("PV_STEAL_ITEM_NAME");

                if (sym) {
                    sym->SetValue(Z item->GetName(0), 0);
                }
                parser->CallFunc(parser->GetIndex("PRINT_STOLEN_ITEM"));
            }

            item->Release();

            return value;
        }

        int tryAddToNpc(oCNpc* npc, bool steal = false) const {
            if (!npc) {
                return 0;
            }

            if (IS_DEBUG && maxPerLocation > 0) {
                ogame->game_text->Printwin("tryAddToNpc for " + npc->GetObjectName() + " (maxPerLocation: " + Z maxPerLocation + ")");
            }

            auto sumValue = 0;
            if (randomizer.Random(0, probabilityOutOf) <= (probability * (EXTRA_LOOT_BASE_CHANCE / 100.))) {
                if (amountMeansPicks) {
                    auto picks = randomizer.Random(1, maxAmount);
                    for (auto i = minAmount - 1; i < picks; i += 1) {
                        auto result = addItemToNpc(npc, steal);
                        if (result > 0) {
                            sumValue += result;
                        }
                    }
                }
                else {
                    sumValue += addItemToNpc(npc, steal);
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

            if (randomizer.Random(0, probabilityOutOf) <= (probability * (EXTRA_LOOT_CHEST_BASE_CHANCE / 100.))) {
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
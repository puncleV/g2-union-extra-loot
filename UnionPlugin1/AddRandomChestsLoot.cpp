// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
    int addRandomChestsLoot() {
        oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
        auto itemsCounter = 0;

        if (world) {
            zCArray<zCVob*> arrMob;

            world->SearchVobListByClass(oCMobContainer::classDef, arrMob, NULL);

            for (size_t i = 0; i < arrMob.GetNumInList(); ++i)
            {
                oCMobContainer* chest = dynamic_cast<oCMobContainer*> (arrMob[i]);

                 if (randomizer.Random(0, EXTRA_LOOT_CHEST_UPPERBOUND) <= EXTRA_LOOT_CHEST_BASE_CHANCE) {
                    for (const auto& lootTable : lootTables) {
                        // todo check if chests loot
                        addRandomLootToChest(chest, lootTable);
                        itemsCounter += 1;
                    }
                }

                if (randomizer.Random(0, EXTRA_LOOT_CHEST_UPPERBOUND) <= CHESTS_BOSS_DROP_CHANCE) {
                    for (const auto& lootTable : lootTables) {
                        // todo check if boss loot
                        addRandomLootToChest(chest, lootTable);
                        itemsCounter += 1;
                    }
                }
            }
        }

        return itemsCounter;
    }
}
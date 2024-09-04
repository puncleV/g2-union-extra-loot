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
                oCMobContainer* firstChest = dynamic_cast<oCMobContainer*> (arrMob[i]);

                if (randomizer.Random(0, getRandomLootUpperound(world)) <= EXTRA_LOOT_CHEST_BASE_CHANCE) {
                    addRandomLootToChest(firstChest, chestsLoot);
                    itemsCounter += 1;
                }

                if (randomizer.Random(0, getRandomLootUpperound(world)) <= 10) {
                    addRandomLootToChest(firstChest, bossLoot);
                    itemsCounter += 1;
                }
            }
        }

        return itemsCounter;
    }
}
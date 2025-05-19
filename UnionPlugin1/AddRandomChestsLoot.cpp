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

                for (auto& lootTable : lootTableList) {
                    lootTable.addRandomLootToChest(chest);
                }

                chest->hitp |= LOOT_ADDED_HITP_FLAG;
            }
        }

        return itemsCounter;
    }
}
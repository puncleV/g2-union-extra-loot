// Supported with union (c) 2020 Union team
// Union SOURCE file

#include<array>
namespace GOTHIC_ENGINE {
	auto const LOOT_ADDED_HITP_FLAG = 32;

    bool oCMobContainer::isRandomized() {
        return (this->hitp & LOOT_ADDED_HITP_FLAG) == LOOT_ADDED_HITP_FLAG;
    }

    void addRandomLootToChest(oCMobContainer* chest, std::vector<Loot> lootTable = NPC_LOOT_TABLE) {
        for (size_t i = 0; i < lootTable.size(); ++i)
        {
            auto loot = lootTable[i];
            loot.tryAddToChest(chest);
        }
    }

	void oCMobContainer::randomize() {
		if (!isRandomized()) {
			oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
            
            if (SHOULD_ADD_LOOT_TO_CHESTS) {
                if (randomizer.Random(0, getRandomLootUpperound(world)) <= EXTRA_LOOT_CHEST_BASE_CHANCE) {
                    addRandomLootToChest(this);
                }

                if (randomizer.Random(0, getRandomLootUpperound(world)) <= 10) {
                    addRandomLootToChest(this, bossLoot);
                }

                this->hitp |= LOOT_ADDED_HITP_FLAG;
            }
		}
	};
}
// Supported with union (c) 2020 Union team
// Union SOURCE file

#include<array>
namespace GOTHIC_ENGINE {
	auto const LOOT_ADDED_HITP_FLAG = 32;

	bool oCMobContainer::lootAdded() {
		return (this->hitp & LOOT_ADDED_HITP_FLAG) == LOOT_ADDED_HITP_FLAG;
	}

	void oCMobContainer::addLoot() {
		if (!lootAdded()) {
			oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());

			if (SHOULD_ADD_LOOT_TO_CHESTS) {
				for (auto& lootTable : lootTableList) {
					lootTable.addRandomLootToChest(this);
				}

				this->hitp |= LOOT_ADDED_HITP_FLAG;
			}
		}
	};
}
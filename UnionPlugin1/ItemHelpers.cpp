// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	const int BIT_ITEM_QUESTITEM = (1 << 19);

	bool IsQuestItem(oCItem* item) {
		if ((item->hitp & BIT_ITEM_QUESTITEM) != 0) {
			return true;
		}
		return false;
	}

	std::vector<std::vector<Loot>> lootTables;
	std::vector<std::vector<Loot>> bossLootTables;
	std::vector<std::vector<Loot>> championLootTables;
	std::vector<std::vector<Loot>> chestsLootTables;
	std::vector<std::vector<Loot>> perChapterLootTables;
}
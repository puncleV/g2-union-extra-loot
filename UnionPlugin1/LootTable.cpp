// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	class LootTable {
	private:
		std::vector<zSTRING> npcs;
		std::vector<Loot> loots;
	public:
		//npcNames, _lootTable, bossessLoot, championsLoot, perChapter, chestsLoot
		LootTable(std::vector <zSTRING> _npcs, std::vector<Loot> _loots, bool _boss, bool _champion, bool _perChapter, bool _chest, bool _steal) {
			npcs = _npcs;
			loots = _loots;
			boss = _boss;
			champion = _champion;
			perChapter = _perChapter;
			chest = _chest;
			steal = _steal;
		};

		bool boss;
		bool champion;
		bool perChapter;
		bool chest;
		bool steal;

		int addRandomLootToNpc(oCNpc* npc, const std::vector<Loot>& lootTable) {
			auto addedLoot = -1;

			for (size_t i = 0; i < lootTable.size(); i++)
			{
				addedLoot += lootTable[i].tryAddToNpc(npc, steal);
			}

			return addedLoot;
		}

		int addToNpc(oCNpc* npc, bool isChampion = false, bool isSteal = false) {
			if (ignoredNpcForLoot(npc) || chest) {
				return 0;
			}

			if (boss && !npc->isBoss()) {
				return 0;
			}

			if (champion && !isChampion) {
				return 0;
			}

			int npcId = npc->getNpcId();
			auto chapterLootWasGiven = npcVariables.getVariable(npcId, NpcVariables::CHAPTER_LOOT_GIVEN_AT);

			if (!perChapter && chapterLootWasGiven != 0 && chapterLootWasGiven != -1) {
				return 0;
			}

			if (perChapter && chapterLootWasGiven == getCurrentChapter()) {
				return 0;
			}

			auto nameMatch = true;

			for (auto name : npcs) {
				nameMatch = npc->GetObjectName().HasWordI(name);

				if (nameMatch) {
					break;
				}
			}

			if (!nameMatch && !isSteal) {
				return 0;
			}

			oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());

			auto lootGiven = addRandomLootToNpc(npc, loots);

			return lootGiven;
		}

		void addRandomLootToChest(oCMobContainer* chestForLoot) {
			if (!chest) {
				return;
			}

			auto nameMatch = true;

			for (auto name : npcs) {
				nameMatch = chestForLoot->GetObjectName().HasWordI(name);

				if (nameMatch) {
					break;
				}
			}

			if (!nameMatch) {
				return;
			}

			for (auto loot : loots)
			{
				loot.tryAddToChest(chestForLoot);
			}
		}
	};
}
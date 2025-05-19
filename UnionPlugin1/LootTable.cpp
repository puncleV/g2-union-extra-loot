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
		LootTable(std::vector <zSTRING> _npcs, std::vector<Loot> _loots, bool _boss, bool _champion, bool _perChapter, bool _chest) {
			npcs = _npcs;
			loots = _loots;
			boss = _boss;
			champion = _champion;
			perChapter = _perChapter;
			chest = _chest;
		};

		bool boss;
		bool champion;
		bool perChapter;
		bool givenToEveryone;
		bool shouldStrengthen;
		bool chest;

		int addRandomLootToNpc(oCNpc* npc, const std::vector<Loot>& lootTable) {
			auto addedLoot = -1;

			for (size_t i = 0; i < lootTable.size(); i++)
			{
				addedLoot += lootTable[i].tryAddToNpc(npc);
			}

			return addedLoot;
		}

		bool addToNpc(oCNpc* npc, bool isChampion = false) {
			if (ignoredNpcForLoot(npc) || chest) {
				return FALSE;
			}

			if (boss && !npc->isBoss()) {
				return FALSE;
			}

			if (champion && !isChampion) {
				return FALSE;
			}

			if (champion)
				ogame->game_text->Printwin("Champion trying");
			auto chapterLootWasGiven = npc->getNpcVar(ADDITIONAL_LOOT_GIVEN_NPC_VAR_IDX);

			if (!perChapter && chapterLootWasGiven != 0) {
				return FALSE;
			}

			if (perChapter && chapterLootWasGiven == getCurrentChapter()) {
				return FALSE;
			}

			auto nameMatch = true;

			for (auto name : npcs) {
				nameMatch = npc->GetObjectName().HasWordI(name);

				if (nameMatch) {
					break;
				}
			}

			if (!nameMatch) {
				return FALSE;
			}



			oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());

			auto lootGiven = addRandomLootToNpc(npc, loots);
			if (champion)
				ogame->game_text->Printwin("Champion adding: " + Z lootGiven);

			return shouldStrengthen ? lootGiven : 0;
		}

		void addRandomLootToChest(oCMobContainer* chestForLoot) {
			if (!chest) {
				return;
			}

			for (auto loot : loots)
			{
				loot.tryAddToChest(chestForLoot);
			}
		}
	};
}
// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	class LootTable {
	private:
		std::set <zSTRING> npcs;
		std::vector<Loot> loots;
	public:
		bool boss;
		bool champion;
		bool perChapter;
	};
}
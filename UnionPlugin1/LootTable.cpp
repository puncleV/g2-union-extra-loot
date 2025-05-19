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
		LootTable(std::vector <zSTRING> _npcs, std::vector<Loot> _loots, bool _boss, bool _champion, bool _perChapter, bool _givenToEveryone, bool _shouldStrengthen) {
			npcs = _npcs;
			loots = _loots;
			boss = _boss;
			champion = _champion;
			perChapter = _perChapter;
			givenToEveryone = _givenToEveryone;
			shouldStrengthen = _shouldStrengthen;
		};

		bool boss;
		bool champion;
		bool perChapter;
		bool givenToEveryone;
		bool shouldStrengthen;
	};
}
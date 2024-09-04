#include <array>
#include <set>
namespace GOTHIC_ENGINE {
	int addRandomNpcLoot() {
		oCWorld* world = dynamic_cast<oCWorld*>(ogame->GetWorld());
		auto npcsCount = 0;
		if (world) {
			auto list = world->voblist_npcs;
			for (size_t i = 0; i < list->GetNumInList(); ++i)
			{
				oCNpc* npc = list->Get(i);
				npcsCount += addLootToNPC(npc) ? 1 : 0;
			}
		}

		return npcsCount;
	}
}
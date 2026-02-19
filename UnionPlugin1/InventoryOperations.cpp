// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	// Add steal loot to player
	int addStealLoot() {
		auto lootGiven = false;
		auto addedValue = 0;

		for (auto& lootTable : lootTableList) {
			if (!lootTable.steal) {
				continue;
			}
			addedValue += lootTable.addToNpc(player, 0, 1);
		}

		return 0;
	}

	// Remove all items from chest or NPC (excluding equipped items for NPCs)
	int removeAllItemsFromChest() {
		if (!ogame || !ogame->GetGameWorld()) {
			return 0;
		}

		oCWorld* world = ogame->GetGameWorld();
		zCVob* vob = world->SearchVobByName(REMOVE_ITEMS_VOB_NAME);

		if (!vob) {
			return 0;
		}

		// Try as chest first
		oCMobContainer* chest = zDYNAMIC_CAST<oCMobContainer>(vob);
		if (chest) {
			if (chest->items && chest->items->contents) {
				chest->items->contents->DeleteList();
			}

			while (chest->containList.GetNumInList() > 0) {
				oCItem* item = chest->containList[0];
				if (item) {
					chest->Remove(item);
				}
			}
			return 1;
		}

		// Try as NPC
		oCNpc* npc = zDYNAMIC_CAST<oCNpc>(vob);
		if (npc) {
			int skipped = 0;
			while (npc->inventory2.inventory.GetNumInList() > 0) {
				oCItem* item = npc->inventory2.inventory[0 + skipped];
				if (item && skipped < 4) {
					// Don't remove equipped items
					if (item != npc->GetEquippedArmor() && 
						item != npc->GetEquippedMeleeWeapon() && 
						item != npc->GetEquippedRangedWeapon()) {
						npc->RemoveFromInv(item, 1);
					}
					else {
						skipped++;
					}
				}
				else {
					break;
				}
			}
			return 1;
		}

		return 0;
	}

	// Register external functions for Daedalus scripts
	void RegisterExternals_punclev() {
		parser->DefineExternal("punclev_loot_steal", addStealLoot, zPAR_TYPE_STRING, 0);
		parser->DefineExternal("punclev_remove_all_items", removeAllItemsFromChest, zPAR_TYPE_INT, 0);
	}
}

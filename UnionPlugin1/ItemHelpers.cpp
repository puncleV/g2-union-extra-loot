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

	bool IsIgnoredOrTestItem(oCItem* item) {
		return item == nullptr || item->GetObjectName().HasWordI("ITMW_TEST") || item->GetObjectName().HasWordI("BELIAR") || item->GetObjectName().HasWordI("URIZEL") || item->GetObjectName().HasWordI("FERROSSWORD") ||
			item->GetObjectName().HasWordI("ABIGEILSPAGE") || item->GetObjectName().HasWordI("TRIBUTEDAGGER") || item->GetObjectName().HasWordI("ITNW_2H_KATANA") || item->GetObjectName().HasWordI("TARACOT") ||
			item->GetObjectName().HasWordI("ADANOSMOLOT") || item->GetObjectName().HasWordI("ASSBLADE") || item->GetObjectName().HasWordI("HOLY_HAMMER") || item->GetObjectName().HasWordI("ALRIKSSWORD") ||
			item->GetObjectName().HasWordI("ITMW_2H_ROD") || item->GetObjectName().HasWordI("DS_MONWEAPON_HALLOWEEN") || item->GetObjectName().HasWordI("GREATARBALET") || item->GetObjectName().HasWordI("MAGICCOSSBOW") ||
			item->GetObjectName().HasWordI("FAKESWORD") || item->GetObjectName().HasWordI("PAL_CLOACK") || item->GetObjectName().HasWordI("SENYAK") || item->GetObjectName().HasWordI("HALLEBERDE_CLAW") || item->GetObjectName().HasWordI("ITMW_STAFF_CLAW") ||
			item->GetObjectName().HasWordI("ITMW_1H_THIEF_01_RIGHT") || item->GetObjectName().StartWith("ITKE_") || item->GetObjectName().StartWith("LUTERO") || item->GetObjectName().StartWith("SNC_SPEC") || item->GetObjectName().HasWordI("ITWR_TALIASANRECOMENDEDLETTERS");
	}

	int getRandomLootUpperound(oCWorld* world) {
		return world->m_strlevelName.HasWordI("NEWWORLD") ? EXTRA_LOOT_HORINIS_FACTOR : EXTRA_LOOT_OTHER_FACTOR;
	}

	std::vector<Loot> NPC_LOOT_TABLE;
	std::vector<Loot> bossLoot;
	std::vector<Loot> alchemistLoot;
	std::vector<Loot> magicLoot;
	std::vector<Loot> tradersLoot;
	std::vector<Loot> humanLoot;
	std::vector<Loot> smithLoot;
	std::vector<Loot> hunterLoot;
	std::vector<Loot> chestsLoot;
}
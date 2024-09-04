// Supported with union (c) 2020 Union team
// Union SOURCE file

namespace GOTHIC_ENGINE {
	std::vector<zSTRING> alchemistsList = { "NONE_1192_FREGEAL", "VLK_498_IGNAZ", "BAU_980_SAGITTA", "VLK_409_ZURIS", "VLK_417_CONSTANTINO", "KDF_506_NEORAS", "NONE_100_XARDAS", "VLK_422_SALANDRIL", "WC_DRUID_TEACHER", "XBS_7501_CAMPER", "VLK_411_GAERTNER" };
	std::vector<zSTRING> magicTraderList = { 
		"VLK_6027_TALIASAN",
		"GUR_8003_TYON",
		"KDW_1401_ADDON_CRONOS_NW",
		"KDF_509_ISGAROTH",
		"KDF_508_GORAX",
		"KDF_506_NEORAS",
		"NONE_100_XARDAS", 
		"KDW_14010_ADDON_CRONOS_ADW",
		"WC_DRUID_TEACHER",
		"DMT_DARKTEACHER ",
	};
	std::vector<zSTRING> miscTradersList = {
		"VLK_458_RUPERT",
		"BDT_1091_ADDON_LUCIA",
		"PIR_1351_ADDON_SAMUEL",
		"PIR_50087",
		"BDT_1086_ADDON_SCATTY",
		"VLK_407_HAKON",
		"VLK_431_KARDIF",
		"VLK_412_HARAD",
		"VLK_410_BALTRAM",
		"VLK_408_JORA",
		"VLK_420_CORAGON",
		"BAU_970_ORLAN",
		"BAU_911_ELENA",
		"BAU_936_ROSI",
		"VLK_476_FENIA",
		"BDT_1097_ADDON_FISK",
		"BDT_10022_ADDON_MIGUEL",
		"VLK_416_MATTEO",
		"VLK_4301_ADDON_FARIM",
		"VLK_468_CANTHAR",
		"VLK_469_HALVOR",
		"VLK_484_LEHMAR",
		"VLK_4303_ADDON_EROL",
		"VLK_404_LUTERO",
		"VLK_6134_VALERAN",
		"VLK_6110_NIGEL",
		"SLD_823_KHALED",
		"VLK_462_THORBEN",
		"VLK_437_BRAHIM",
		"VLK_470_SARAH",
		"VLK_424_ALWIN",
		"VLK_492_RENGARU",
		"NOV_11114_HOLGER",
		"MIL_350_ADDON_MARTIN",
		"PIR_1357_ADDON_GARETT",
		"PIR_50087",
		"AL_NPC_TAVERN",
		"AL_NPC_HERMIT",
		"AL_INNKEEPR",
		"ORC_8549_TRADEORC",
		"VLK_4108_ENGOR",
		"PAL_260_TANDOR",
		"PAL_267_SENGRATH",
		"XBS_7508_GORNABAR",
		"DJG_710_KJORN",
		"SLD_803_CIPHER"
	};
	std::vector<zSTRING> smithTradersList = {
		"SLD_809_BENNET",
		"BAU_908_HODGES",
		"VLK_457_BRIAN",
		"BDT_1099_ADDON_HUNO",
		"AL_SMITH",
		"AL_COMMON_SMITH",
		"XBS_7513_DARRION",
		"MIL_314_MORTIS"
	};
	std::vector<zSTRING> hunterList = {
		"VLK_413_BOSPER",
		"HUN_745_RAFFA",
	};
	std::vector<zSTRING> ignoreLootNpcList = { "TOTEM", "CRAIT", "KHUBA", "SUMKHUBI", "PET_JINA" };

	bool addRandomLootToNpc(oCNpc* npc, std::vector<Loot>& lootTable = NPC_LOOT_TABLE) {
		auto addedLoot = false;
		
		for (size_t i = 0; i < lootTable.size(); ++i)
		{
			addedLoot = lootTable[i].tryAddToNpc(npc) || addedLoot;
		}

		return addedLoot;
	}

	bool npcCanWearWeapon(oCItem* item, oCNpc* npc) {
		for (size_t i = 0; i < ITM_COND_MAX; i++)
		{
			if (item->cond_atr[i] <= 0 && item->cond_atr[i] >= NPC_ATR_MAX) {
				return false;
			}

			if (npc->attribute[item->cond_atr[i]] < item->cond_value[i])
			{
				return false;
			}
		}

		return true;
	}

	bool RX_IsBoss(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_BOSS] == TRUE);
	}

	bool RX_IsSummon(oCNpc* npc) {
		return (npc && npc->aiscriptvars[AIV_SUMMON] == TRUE);
	}

	bool RX_IsAlchemistTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < alchemistsList.size(); i += 1) {
			if (npcName.HasWordI(alchemistsList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}

	bool RX_IsMageTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < magicTraderList.size(); i += 1) {
			if (npcName.HasWordI(magicTraderList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}

	bool RX_IsSmithTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < smithTradersList.size(); i += 1) {
			if (npcName.HasWordI(smithTradersList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}

	bool RX_IsHunterTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < hunterList.size(); i += 1) {
			if (npcName.HasWordI(hunterList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}


	bool RX_IsTrader(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < miscTradersList.size(); i += 1) {
			if (npcName.HasWordI(miscTradersList[i])) {
				return TRUE;
			}
		}

		return RX_IsMageTrader(npc) || RX_IsAlchemistTrader(npc) || RX_IsSmithTrader(npc) || RX_IsHunterTrader(npc);
	}

	bool ignoredNpcForLoot(oCNpc* npc) {
		auto npcName = npc->GetObjectName();

		for (auto i = 0; i < ignoreLootNpcList.size(); i += 1) {
			if (npcName.HasWordI(ignoreLootNpcList[i])) {
				return TRUE;
			}
		}

		return FALSE;
	}
}
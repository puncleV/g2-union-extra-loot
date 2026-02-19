// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <codecvt>
#include<array>
namespace GOTHIC_ENGINE {
	class JsonConfig {
	private:
		nlohmann::json jsonFile;

		std::string utf8_to_ansi(const std::string& str, const std::locale& loc = std::locale("." + std::to_string(ANSI_CODEPAGE_DEFAULT))) {
			using wcvt = std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>;
			auto wstr = wcvt{}.from_bytes(str);
			std::string result(wstr.size(), '0');
			std::use_facet<std::ctype<wchar_t>>(loc).narrow(wstr.data(), wstr.data() + wstr.size(), '?', &result[0]);
			return result;
		}
	public:
		void loadConfig() {
			zoptions->ChangeDir(DIR_SYSTEM);
			zFILE_VDFS* originFile = new zFILE_VDFS(JSON_FILE_NAME);

			if (!originFile->Exists()) {
				delete originFile;
				return;
			}

			originFile->Open(false);

			zSTRING line, buffer;
			do {
				originFile->Read(line);
				buffer += line;
			} while (!originFile->Eof());

			originFile->Close();
			jsonFile = nlohmann::json::parse(buffer.ToChar());
		}

		void lootTable() {
			for (auto it = jsonFile.begin(); it != jsonFile.end(); ++it) {
				std::vector<Loot> _lootTable = {};
				std::string name = it.key();

				if (!jsonFile[name].is_object()) {
					return;
				}

				if (!jsonFile[name]["loot"].is_array()) {
					return;
				}
				std::vector <zSTRING> npcNames;
				for (auto j = 0; j < jsonFile[name]["npcs"].size(); j += 1) {
					npcNames.push_back(utf8_to_ansi(jsonFile[name]["npcs"][j].get<std::string>()).c_str());
				}

				std::vector <zSTRING> ignoreNpcNames;
				if (jsonFile[name].contains("ignore_npcs") && jsonFile[name]["ignore_npcs"].is_array()) {
					for (auto j = 0; j < jsonFile[name]["ignore_npcs"].size(); j += 1) {
						ignoreNpcNames.push_back(utf8_to_ansi(jsonFile[name]["ignore_npcs"][j].get<std::string>()).c_str());
					}
				}

				zSTRING worldName = "";
				if (jsonFile[name].contains("world") && jsonFile[name]["world"].is_string()) {
					worldName = utf8_to_ansi(jsonFile[name]["world"].get<std::string>()).c_str();
				}

				for (auto i = 0; i < jsonFile[name]["loot"].size(); i += 1) {
					int chance = jsonFile[name]["loot"][i]["chance"];
					int chanceOutOf = jsonFile[name]["loot"][i].value("chanceOutOf", 1000);

					std::vector <zSTRING> lootNames;
					for (auto j = 0; j < jsonFile[name]["loot"][i]["itemNames"].size(); j += 1) {
						lootNames.push_back(utf8_to_ansi(jsonFile[name]["loot"][i]["itemNames"][j].get<std::string>()).c_str());
					}

				int minAmount = jsonFile[name]["loot"][i].value("minAmount", 1);
				int maxAmount = jsonFile[name]["loot"][i].value("maxAmount", 1);
				int maxPerLocation = jsonFile[name]["loot"][i].value("maxPerLocation", -1);
				auto amountMeansPicks = jsonFile[name]["loot"][i].value("amountMeansPicks", false);
				int valueOverride = jsonFile[name]["loot"][i].value("valueOverride", -1);

				_lootTable.push_back(Loot(chance, chanceOutOf, lootNames, minAmount, maxAmount, amountMeansPicks, valueOverride, maxPerLocation));
				}

				auto championsLoot = jsonFile[name].value("champion", false);
				auto bossessLoot = jsonFile[name].value("boss", false);
				auto chestsLoot = jsonFile[name].value("chest", false);
				auto perChapter = jsonFile[name].value("oncePerChapter", false);
				auto stealLoot = jsonFile[name].value("steal", false);

				lootTableList.push_back(LootTable(npcNames, _lootTable, bossessLoot, championsLoot, perChapter, chestsLoot, stealLoot, ignoreNpcNames, worldName));
			}
		}
	};

	JsonConfig jsonConfig;
}
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

		std::vector<Loot> lootTable(const char* name) {
			std::vector<Loot> _lootTable = {};

			if (!jsonFile["loot-tables"].is_object()) {
				return _lootTable;
			}

			if (!jsonFile["loot-tables"][name].is_array()) {
				return _lootTable;
			}

			for (auto i = 0; i < jsonFile["loot-tables"][name].size(); i += 1) {
				int chance = jsonFile["loot-tables"][name][i]["chance"];
				int chanceOutOf = jsonFile["loot-tables"][name][i].value("chanceOutOf", 1000);
				std::vector <zSTRING> lootNames;

				for (auto j = 0; j < jsonFile["loot-tables"][name][i]["itemNames"].size(); j += 1) {
					lootNames.push_back(utf8_to_ansi(jsonFile["loot-tables"][name][i]["itemNames"][j].get<std::string>()).c_str());
				}

				int minAmount = jsonFile["loot-tables"][name][i].value("minAmount", 1); 
				int maxAmount = jsonFile["loot-tables"][name][i].value("maxAmount", 1);

				_lootTable.push_back(Loot(chance, chanceOutOf, lootNames, minAmount, maxAmount));
			}

			return _lootTable;
		}
	};

	JsonConfig jsonConfig;
}
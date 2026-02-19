// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <map>

namespace GOTHIC_ENGINE {
    class SaveData {
    public:
        enum VariableKey {
            CHAPTER_LOOT_GIVEN_AT = 0,
            LP_INCREASE = 1
        };
        enum Value {
            CHAMPION = 10,
            NOT_GIVEN = -1
        };
    private:
        std::map<int, std::map<int, int>> npcIntVars;
        std::map<std::string, int> itemsGivenCount;
        int lastGivenNpcId = 1;
        bool initialized = false;
    public:
        void setVariable(int npcId, int key, int value) {
            npcIntVars[npcId][key] = value;
        }
        
        int getVariable(int npcId, int key) {
            if (npcIntVars.count(npcId) && npcIntVars[npcId].count(key)) {
                return npcIntVars[npcId][key];
            }
            return -1;
        }
        
        int getNextNpcId() {
            while (npcIntVars.count(lastGivenNpcId)) {
                lastGivenNpcId++;
            }
            return lastGivenNpcId;
        }

        // Item tracking methods
        std::string getItemKey(const zSTRING& itemName) {
            // Combine world name with item name for per-location tracking
            oCWorld* currentWorld = ogame->GetGameWorld();
            std::string worldName = "";
            if (currentWorld) {
                worldName = currentWorld->GetWorldName().ToChar();
            }
            std::string key = worldName + "_" + std::string(itemName.ToChar());
            return key;
        }

        int getItemGivenCount(const zSTRING& itemName) {
            std::string key = getItemKey(itemName);
            if (itemsGivenCount.count(key)) {
                return itemsGivenCount[key];
            }
            return 0;
        }

        void incrementItemGiven(const zSTRING& itemName, int amount = 1) {
            std::string key = getItemKey(itemName);
            itemsGivenCount[key] += amount;
        }

        bool canGiveItem(const zSTRING& itemName, int maxPerLocation) {
            if (maxPerLocation <= 0) {
                return true; // No limit
            }
            return getItemGivenCount(itemName) < maxPerLocation;
        }

        void clear() {
            npcIntVars.clear();
            itemsGivenCount.clear();
            lastGivenNpcId = 1;
        }

        void deleteNpc(int npcId) {
            if (npcIntVars.count(npcId)) {
                npcIntVars.erase(npcId);
            }
        }

        bool saveToFile(const char* filepath) {
            FILE* file = fopen(filepath, "wb");
            if (!file) {
                return false;
            }

            // Save NPC ID counter
            fwrite(&lastGivenNpcId, sizeof(int), 1, file);

            // Save NPC variables
            int npcCount = npcIntVars.size();
            fwrite(&npcCount, sizeof(int), 1, file);

            for (auto& npcPair : npcIntVars) {
                int npcId = npcPair.first;
                fwrite(&npcId, sizeof(int), 1, file);

                int varCount = npcPair.second.size();
                fwrite(&varCount, sizeof(int), 1, file);

                for (auto& varPair : npcPair.second) {
                    int key = varPair.first;
                    int value = varPair.second;
                    fwrite(&key, sizeof(int), 1, file);
                    fwrite(&value, sizeof(int), 1, file);
                }
            }

            // Save items given count
            int itemsCount = itemsGivenCount.size();
            fwrite(&itemsCount, sizeof(int), 1, file);

            for (auto& itemPair : itemsGivenCount) {
                // Save item name length (std::string)
                int nameLen = itemPair.first.length();
                fwrite(&nameLen, sizeof(int), 1, file);
                
                // Save item name (std::string)
                fwrite(itemPair.first.c_str(), sizeof(char), nameLen, file);
                
                // Save count
                int count = itemPair.second;
                fwrite(&count, sizeof(int), 1, file);
            }

            fclose(file);
            return true;
        }

        bool loadFromFile(const char* filepath) {
            FILE* file = fopen(filepath, "rb");
            if (!file) {
                return false;
            }

            clear();

            // Load NPC ID counter
            fread(&lastGivenNpcId, sizeof(int), 1, file);

            // Load NPC variables
            int npcCount = 0;
            fread(&npcCount, sizeof(int), 1, file);

            for (int i = 0; i < npcCount; i++) {
                int npcId = 0;
                fread(&npcId, sizeof(int), 1, file);

                int varCount = 0;
                fread(&varCount, sizeof(int), 1, file);

                for (int j = 0; j < varCount; j++) {
                    int key = 0;
                    int value = 0;
                    fread(&key, sizeof(int), 1, file);
                    fread(&value, sizeof(int), 1, file);
                    
                    npcIntVars[npcId][key] = value;
                }
            }

            // Load items given count
            int itemsCount = 0;
            fread(&itemsCount, sizeof(int), 1, file);

            for (int i = 0; i < itemsCount; i++) {
                // Load item name length
                int nameLen = 0;
                fread(&nameLen, sizeof(int), 1, file);
                
                // Load item name as std::string
                char* nameBuffer = new char[nameLen + 1];
                fread(nameBuffer, sizeof(char), nameLen, file);
                nameBuffer[nameLen] = '\0';
                std::string itemName = nameBuffer;
                delete[] nameBuffer;
                
                // Load count
                int count = 0;
                fread(&count, sizeof(int), 1, file);
                
                itemsGivenCount[itemName] = count;
            }

            fclose(file);
            return true;
        }
    };

    SaveData saveData;
    
    // Backward compatibility alias
    #define npcVariables saveData
    #define NpcVariables SaveData
}

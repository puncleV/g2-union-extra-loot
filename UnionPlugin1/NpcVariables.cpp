// Supported with union (c) 2020 Union team
// Union SOURCE file

#include <array>
#include <map>

namespace GOTHIC_ENGINE {
    class NpcVariables {
    public:
        enum VariableKey {
            CHAPTER_LOOT_GIVEN_AT = 0
        };
        enum Value {
            CHAMPION = 10
        };
    private:
        std::map<int, std::map<int, int>> npcIntVars;
		int lastGivenNpcId = 1;

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

        void clear() {
            npcIntVars.clear();
            lastGivenNpcId = 1;
        }

        bool saveToFile(const char* filepath) {
            FILE* file = fopen(filepath, "wb");
            if (!file) {
                return false;
            }

            fwrite(&lastGivenNpcId, sizeof(int), 1, file);

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

            fclose(file);
            return true;
        }

        bool loadFromFile(const char* filepath) {
            FILE* file = fopen(filepath, "rb");
            if (!file) {
                return false;
            }

            clear();

            fread(&lastGivenNpcId, sizeof(int), 1, file);

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

            fclose(file);
            return true;
        }
    };

	NpcVariables npcVariables;
}
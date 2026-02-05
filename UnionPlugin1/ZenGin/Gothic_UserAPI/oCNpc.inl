// Supported with union (c) 2020 Union team

// User API for oCNpc
// Add your methods here

int addLootOnAssessEnemy(oCNpc*);
int addLootOnAssessPlayer(oCNpc*);

int getNpcId();
bool isChampion();
bool isBoss();
bool isSummon();
zCArray<oCNpc*> goThroughNpcsInRadius(float);
void randomizeChestsInRadius(float);


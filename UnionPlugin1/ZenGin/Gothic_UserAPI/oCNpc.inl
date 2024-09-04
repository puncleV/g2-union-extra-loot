// Supported with union (c) 2020 Union team

// User API for oCNpc
// Add your methods here

int addLootOnAssessEnemy(oCNpc*);
int addLootOnAssessPlayer(oCNpc*);

void setNpcVar(int, int);

int getNpcVar(int);
zCArray<oCNpc*> goThroughNpcsInRadius(float);
void randomizeChestsInRadius(float);

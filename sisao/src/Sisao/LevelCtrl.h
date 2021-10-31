#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Player.h"
#include "Flag.h"
#include "DynamicObject.h"

class LevelCtrl
{
public:
	void init(Player *p1, Player *p2, vector<pair<string, DynamicObject*>> &d_objects, int lvl);
	void update(int deltaTime);
	void render();

private:
	int currentLevel;
	Player *player1, *player2;
	DynamicObject *flag1, *flag2;
	TileMap *map;
};

#endif // _LEVEL_INCLUDE
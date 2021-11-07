#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Player.h"
#include "Flag.h"
#include "Barrier.h"
#include "DynamicObject.h"

class LevelCtrl
{
public:
	void init(Player *p1, Player *p2, vector<pair<string, DynamicObject*>> &d_objects, int lvl, bool godMode);
	void update(int deltaTime);
	void toggleGodMode();

private:
	void destroyBarriers();

	bool godmode;
	int currentLevel;
	Player *player1, *player2;
	DynamicObject *flag1, *flag2, *lever;
	vector<DynamicObject*> barriers, boxes;
	TileMap *map;
};

#endif // _LEVEL_INCLUDE
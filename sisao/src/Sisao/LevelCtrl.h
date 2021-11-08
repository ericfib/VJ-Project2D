#ifndef _LEVEL_INCLUDE
#define _LEVEL_INCLUDE

#include "Player.h"
#include "Flag.h"
#include "Barrier.h"
#include "DynamicObject.h"

class LevelCtrl
{
public:
	void init(Player *p1, Player *p2, vector<pair<string, DynamicObject*>> &d_objects, int lvl, int numLives, bool godMode);
	void update(int deltaTime);
	void toggleGodMode();
	string getCurrentState();

private:
	void destroyBarriers();

	enum State { PLAYING, WIN, DIE_1, DIE_2, DIE_BOTH };
	State currentState;
	bool godmode;
	int currentLevel, winTime, lives;
	Player *player1, *player2;
	DynamicObject *flag1, *flag2, *lever;
	vector<DynamicObject*> barriers, boxes;
	TileMap *map;
};

#endif // _LEVEL_INCLUDE
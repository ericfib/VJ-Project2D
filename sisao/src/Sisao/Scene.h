#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "Flag.h"
#include "Lever.h"
#include "Barrier.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Menu.h"
#include "LevelCtrl.h"
#include "Box.h"



// Scene contains all the entities of our game.
// It is responsible for updating and render them.


class Scene
{

public:
	Scene();
	~Scene();

	void init();
	void update(int deltaTime);
	void render();
	void changeState(int state);
	void loadlevel(int level);
	void updateCameraPosition(int deltaTime);
	float get_mid_point(float p1, float p2);
	void initProj();

private:
	void initShaders();
	void initDynamicObjects();
	enum State { LOADING, TITLE, LEVEL, CREDITS, INSTRUCTIONS };
	

private:
	TileMap *map;
	Player *player, *player2;
	Menu *menu, *instr;
	vector <pair<string, DynamicObject*>> d_objects;
	LevelCtrl *levelCtrl;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	State currentState, previousState;
	int currentLevel, timerState;
	float valor_cam, mid_point_aux, left, top, bottom, right;
};


#endif // _SCENE_INCLUDE
#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "Flag.h"
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Menu.h"
#include "LevelCtrl.h"



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
	void updateCameraPosition();

private:
	void initShaders();
	void initDynamicObjects();
	enum State { LOADING, TITLE, LEVEL, CREDITS, INSTRUCTIONS };
	

private:
	TileMap *map;
	Player *player;
	Player *player2;
	Menu *menu;
	vector <pair<string, DynamicObject*>> d_objects;
	LevelCtrl *levelCtrl;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	State currentState;
	int currentLevel;
	float maxX, maxY, minX, minY, cameraX, cameraY, cameraVx;
};


#endif // _SCENE_INCLUDE
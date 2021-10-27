#ifndef _SCENE_INCLUDE
#define _SCENE_INCLUDE


#include <glm/glm.hpp>
#include "ShaderProgram.h"
#include "TileMap.h"
#include "Player.h"
#include "Menu.h"


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

private:
	void initShaders();
	enum State { LOADING, TITLE, LEVEL, CREDITS, INSTRUCTIONS };

private:
	TileMap *map;
	Player *player;
	Player *player2;
	Menu *menu;
	ShaderProgram texProgram;
	float currentTime;
	glm::mat4 projection;
	State currentState;
	int currentLevel;
};


#endif // _SCENE_INCLUDE
#include <iostream>
#include <cmath>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Scene.h"
#include "Game.h"


#define SCREEN_X 32
#define SCREEN_Y 16

#define INIT_PLAYER_X_TILES 4
#define INIT_PLAYER_Y_TILES 25


Scene::Scene()
{
	map = NULL;
	player = NULL;
	player2 = NULL;
}

Scene::~Scene()
{
	if (map != NULL)
		delete map;
	if (player != NULL)
		delete player;
	if (player2 != NULL)
		delete player2;
}


void Scene::init()
{
	initShaders();
	map = TileMap::createTileMap("levels/levelTest.txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	player = new Player();
	player2 = new Player();
	menu = new Menu();
	currentState = TITLE;
	menu->initTitle(texProgram);
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1);
	player2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1);
	player->setPosition(glm::vec2(16 * map->getTileSize(), 11 * map->getTileSize()));
	player2->setPosition(glm::vec2(16 * map->getTileSize(), 13 * map->getTileSize()));
	player->setTileMap(map);
	player2->setTileMap(map);
	projection = glm::ortho(0.f, float(SCREEN_WIDTH - 1), float(SCREEN_HEIGHT - 1), 0.f);
	currentTime = 0.0f;
}

void Scene::update(int deltaTime)
{
	currentTime += deltaTime;
	switch (currentState) {
	case LOADING:
		break;
	case TITLE:
		menu->updateTitle(deltaTime);
		break;
	case LEVEL:
		player->update(deltaTime);
		player2->update(deltaTime);
		break;
	case CREDITS:
		break;
	case INSTRUCTIONS:
		break;
	}
}

void Scene::render()
{
	glm::mat4 modelview;

	texProgram.use();
	texProgram.setUniformMatrix4f("projection", projection);
	texProgram.setUniform4f("color", 1.0f, 1.0f, 1.0f, 1.0f);
	modelview = glm::mat4(1.0f);
	texProgram.setUniformMatrix4f("modelview", modelview);
	texProgram.setUniform2f("texCoordDispl", 0.f, 0.f);

	switch (currentState) {

	case LOADING:
		break;
	case TITLE:
		menu->renderTitle();
		break;
	case LEVEL:
		map->render();
		player->render();
		player2->render();
		break;
	case CREDITS:
		break;
	case INSTRUCTIONS:
		menu->renderInstructions();
		break;
	}

}

void Scene::initShaders()
{
	Shader vShader, fShader;

	vShader.initFromFile(VERTEX_SHADER, "shaders/texture.vert");
	if (!vShader.isCompiled())
	{
		cout << "Vertex Shader Error" << endl;
		cout << "" << vShader.log() << endl << endl;
	}
	fShader.initFromFile(FRAGMENT_SHADER, "shaders/texture.frag");
	if (!fShader.isCompiled())
	{
		cout << "Fragment Shader Error" << endl;
		cout << "" << fShader.log() << endl << endl;
	}
	texProgram.init();
	texProgram.addShader(vShader);
	texProgram.addShader(fShader);
	texProgram.link();
	if (!texProgram.isLinked())
	{
		cout << "Shader Linking Error" << endl;
		cout << "" << texProgram.log() << endl << endl;
	}
	texProgram.bindFragmentOutput("outColor");
	vShader.free();
	fShader.free();
}


void Scene::changeState(int state) {
	switch (state) {
	case 1:
		currentState = TITLE;
		break;

	case 2:
		currentState = LEVEL;
		break;

	case 3:
		currentState = CREDITS;
		break;

	case 4:
		currentState = CREDITS;
		break;
	}
	render();
}








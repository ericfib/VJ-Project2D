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

	currentState = TITLE;
	currentLevel = 2;
	loadlevel(currentLevel);

	menu = new Menu();
	menu->initTitle(texProgram);
	
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

		for (int i = 0; i < d_objects.size(); i++) {
			d_objects[i]->update(deltaTime);
		}
		break;
	case CREDITS:
		break;
	case INSTRUCTIONS:
		break;
	}

	if (Game::instance().getSpecialKey(GLUT_KEY_F1)) {
		currentLevel = 1;
		loadlevel(currentLevel);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_F2)) {
		currentLevel = 2;
		loadlevel(currentLevel);
	}
	else if (Game::instance().getSpecialKey(GLUT_KEY_F3)) {
		currentLevel = 3;
		loadlevel(currentLevel);
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
		menu->render_bg();
		
		map->render();

		player->render();
		player2->render();

		for (int i = 0; i < d_objects.size(); i++) {
			d_objects[i]->render();
		}

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

void Scene::loadlevel(int level) {
	//pop de d_objects[]

	string lvl = std::to_string(level);
	pair<int, int> posplayer1, posplayer2;
	int tileSize;

	map = TileMap::createTileMap("levels/level" + lvl + ".txt", glm::vec2(SCREEN_X, SCREEN_Y), texProgram);
	posplayer1 = map->getPosPlayer(1);
	posplayer2 = map->getPosPlayer(2);
	tileSize = map->getTileSize();

	initDynamicObjects();

	player = new Player();
	player2 = new Player();
	player->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, 1, currentLevel);
	player2->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, -1, currentLevel);

	player->setPosition(glm::vec2(posplayer1.first * tileSize, (posplayer1.second * tileSize) - 32));
	player2->setPosition(glm::vec2(posplayer2.first * tileSize, posplayer2.second * tileSize));
	player->setTileMap(map);
	player2->setTileMap(map);
}


void Scene::initDynamicObjects() {
	vector<pair<string, pair<int, int>>> aux;
	aux = map->getDynamicObjects();
	int tileSize = map->getTileSize();

	for (int i = 0; i < aux.size(); i++) {
		if (aux[i].first == "f1") {
			Flag* f1 = new Flag();
			f1->init(glm::ivec2(SCREEN_X, SCREEN_Y), texProgram, currentLevel);
			f1->setPosition(glm::vec2(aux[i].second.first * tileSize, (aux[i].second.second * tileSize) - 16));

			d_objects.push_back(f1);
		}
		else if (aux[i].first == "ct") {
		}
		else if (aux[i].first == "ba") {
		}
		else if (aux[i].first == "it") {
		}
		else if (aux[i].first == "cp") {
		}
	}
}




#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include <Windows.h>
#include <MMSystem.h>
#include "LevelCtrl.h"
#include "Game.h"

void LevelCtrl::init(Player *p1, Player *p2, vector<pair<string, DynamicObject*>> &d_objects, int lvl, bool godMode) {
	currentLevel = lvl;
	player1 = p1;
	player2 = p2;
	godmode = godMode;

	for (int i = 0; i < d_objects.size(); i++) {
		if (d_objects[i].first == "f1") {
			flag1 = d_objects[i].second;
		}
		else if (d_objects[i].first == "f2") {
			flag2 = d_objects[i].second;
		}
		else if (d_objects[i].first == "le") {
			lever = d_objects[i].second;
		}
		else if (d_objects[i].first == "ba") {
			barriers.push_back(d_objects[i].second);
		}
		else if (d_objects[i].first == "bx") {
			boxes.push_back(d_objects[i].second);
		}
	}
}

void LevelCtrl::update(int deltatime) {
	glm::ivec2 posP1 = player1->getPosition();
	glm::ivec2 posP2 = player2->getPosition();

	glm::ivec2 posF1 = flag1->getPosition();
	glm::ivec2 posF2 = flag2->getPosition();

	//control de muertes
	if (player1->isDead()) player2->iniDeath();
	else if (player2->isDead()) player1->iniDeath();


	//banderas
	if (posP1.x > posF1.x - 20 && posP1.x < posF1.x + 5 && posP1.y + 32 == posF1.y + 46) {
		flag1->setActive(true);
	}
	else flag1->setActive(false);

	if (posP2.x > posF2.x - 20 && posP2.x < posF2.x + 5 && posP2.y == posF2.y) {
		flag2->setActive(true);
	}
	else flag2->setActive(false);

	if (flag2->isActive() && flag1->isActive()) {
		Game::instance().changeLevel(currentLevel + 1);
	}

	//barreras
	for (int i = 0; i < barriers.size(); i++) {
		if (barriers[i]->collisionLeft(posP1, glm::ivec2(32, 32)) && godmode == false) player1->setPosition(glm::ivec2(posP1.x - 2, posP1.y));
		if (barriers[i]->collisionRight(posP1, glm::ivec2(32, 32)) && godmode == false) player1->setPosition(glm::ivec2(posP1.x + 2, posP1.y));

		if (barriers[i]->collisionLeft(posP2, glm::ivec2(32, 32))) player2->setPosition(glm::ivec2(posP2.x - 2, posP2.y));
		if (barriers[i]->collisionRight(posP2, glm::ivec2(32, 32))) player2->setPosition(glm::ivec2(posP2.x + 2, posP2.y));

	}

	//levers
	if (lever != NULL) {
		glm::ivec2 posLever = lever->getPosition();
		if (lever->getInverted() == 1) {
			if (posP1.x > posLever.x - 20 && posP1.x < posLever.x + 5 && posP1.y + 32 == posLever.y + 30) {
				PlaySound(TEXT("audio/lever.wav"), NULL, SND_FILENAME | SND_ASYNC);
				lever->setActive(true);
				destroyBarriers();
				lever = NULL;
			}
		}
		else {
			if (posP2.x > posLever.x - 20 && posP2.x < posLever.x + 5 && posP2.y == posLever.y) {
				PlaySound(TEXT("audio/lever.wav"), NULL, SND_FILENAME | SND_ASYNC);
				lever->setActive(true);
				destroyBarriers();
				lever = NULL;
			}
		}
	}

	//cajas
	player1->setColBox(false);
	player2->setColBox(false);
	for (int i = 0; i < boxes.size(); i++) {
		//player1
		boxes[i]->setPushLeft(false);
		boxes[i]->setPushRight(false);

		if (boxes[i]->collisionLeft(posP1, glm::ivec2(32, 32))) {
			player1->setPosition(glm::ivec2(posP1.x - 2, posP1.y));
			boxes[i]->setPushLeft(true);
		}
		if (boxes[i]->collisionRight(posP1, glm::ivec2(32, 32))) {
			player1->setPosition(glm::ivec2(posP1.x + 2, posP1.y));
			boxes[i]->setPushRight(true);
		}
		if (boxes[i]->collisionUp(posP1, glm::ivec2(32, 32))) {
			player1->setPosition(glm::ivec2(posP1.x, boxes[i]->getPosition().y - 34));
			player1->setColBox(true);
		}

		//player2
		if (boxes[i]->collisionLeft(posP2, glm::ivec2(32, 32))) {
			player2->setPosition(glm::ivec2(posP2.x - 2, posP2.y));
			boxes[i]->setPushLeft(true);
		}
		if (boxes[i]->collisionRight(posP2, glm::ivec2(32, 32))) {
			player2->setPosition(glm::ivec2(posP2.x + 2, posP2.y));
			boxes[i]->setPushRight(true);
		}
		if (boxes[i]->collisionDown(posP2, glm::ivec2(32, 32))) {
			player2->setPosition(glm::ivec2(posP2.x, boxes[i]->getPosition().y + 35));
			player2->setColBox(true);
		}
	}
}


void LevelCtrl::destroyBarriers()
{
	for (int i = 0; i < barriers.size(); i++) {
		barriers[i]->setDestroyed(true);
	}
	//barriers.clear();
}

void LevelCtrl::toggleGodMode() {
	godmode = !godmode;
	player1->setGodMode(godmode);
	player2->setGodMode(godmode);
}

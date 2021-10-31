#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "LevelCtrl.h"
#include "Game.h"

void LevelCtrl::init(Player *p1, Player *p2, vector<pair<string, DynamicObject*>> &d_objects, int lvl) {
	currentLevel = lvl;
	player1 = p1;
	player2 = p2;

	for (int i = 0; i < d_objects.size(); i++) {
		if (d_objects[i].first == "f1") {
			flag1 = d_objects[i].second;
		}
		else if (d_objects[i].first == "f2") {
			flag2 = d_objects[i].second;
		}
	}
}

void LevelCtrl::update(int deltatime) {
	glm::ivec2 posP1 = player1->getPosition();
	glm::ivec2 posP2 = player2->getPosition();
	
	glm::ivec2 posF1 = flag1->getPosition();
	glm::ivec2 posF2 = flag2->getPosition();
	if (posP1.x > posF1.x - 20 && posP1.x < posF1.x + 5 && posP1.y == posF1.y + 12) {
		flag1->setActive(true);
	}
	else flag1->setActive(false);

	if (posP2.x > posF2.x - 20  && posP2.x < posF2.x + 5 && posP2.y == posF2.y) {
		flag2->setActive(true);
	}
	else flag2->setActive(false);

}


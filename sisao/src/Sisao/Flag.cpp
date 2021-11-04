#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flag.h"


enum FlagAnims
{
	IDLE, GOING_DOWN, IDLE_DOWN
};

void Flag::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl, int invert) {
	tileMapDispl = tileMapPos;
	currentLevel = lvl;
	active = false;
	float x = 0.2;
	float y = 0.5;
	if (invert == 1) spritesheet.loadFromFile("images/flag_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else spritesheet.loadFromFile("images/flag_sprite2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(30, 46), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(3);
		
		sprite->setAnimationSpeed(IDLE, 4);
		sprite->addKeyframe(IDLE, glm::vec2(0, 0));
		sprite->addKeyframe(IDLE, glm::vec2(x, 0));
		sprite->addKeyframe(IDLE, glm::vec2(2 * x, 0));
		sprite->addKeyframe(IDLE, glm::vec2(3 * x, 0));
		sprite->addKeyframe(IDLE, glm::vec2(4 * x, 0));

		sprite->setAnimationSpeed(GOING_DOWN, 10);
		sprite->addKeyframe(GOING_DOWN, glm::vec2(0, y));
		sprite->addKeyframe(GOING_DOWN, glm::vec2(x, y));
		sprite->addKeyframe(GOING_DOWN, glm::vec2(2 * x, y));
		sprite->addKeyframe(GOING_DOWN, glm::vec2(3 * x, y));
		sprite->addKeyframe(GOING_DOWN, glm::vec2(4 * x, y));

		sprite->setAnimationSpeed(IDLE_DOWN, 1);
		sprite->addKeyframe(IDLE_DOWN, glm::vec2(4 * x, y));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Flag::update(int deltatime) {
	sprite->update(deltatime);
	if (active) {
		if (sprite->animation() != GOING_DOWN && sprite->animation() != IDLE_DOWN) {
			activedTime = 0;
			sprite->changeAnimation(GOING_DOWN);
		}
		else if (sprite->animation() != IDLE_DOWN) {
			activedTime += deltatime;
			if (activedTime >= 1000 / 10 * 5) {
				sprite->changeAnimation(IDLE_DOWN);
			}
		}
	}
	else if (sprite->animation() != IDLE) sprite->changeAnimation(IDLE);
}

void Flag::render() {
	sprite->render();
}

void Flag::setTileMap(TileMap *tilemap) {
	map = tilemap;
}

void Flag::setPosition(const glm::vec2 &pos) {
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Flag::setActive(bool actived) {
	active = actived;
}

glm::ivec2 Flag::getPosition() {
	return posObject;
}
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Flag.h"


enum FlagAnims
{
	IDLE, GOING_DOWN
};

void Flag::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl) {
	tileMapDispl = tileMapPos;
	currentLevel = lvl;
	float x = 0.2;
	float y = 0.47;
	spritesheet.loadFromFile("images/flag_sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(25, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);
		
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

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Flag::update(int deltatime) {
	sprite->update(deltatime);
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

bool Flag::collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	return true;
}

bool Flag::collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	return true;
}

bool Flag::collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const {
	return true;
}
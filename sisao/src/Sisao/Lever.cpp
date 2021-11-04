#include "Lever.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


enum LeverAnims
{
	IDLE_ACTIVE, IDLE_INACTIVE
};

void Lever::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl, int invert) {
	tileMapDispl = tileMapPos;
	currentLevel = lvl;
	active = false;
	inverted = invert;
	float x = 0.5;
	float y = 1;
	if (invert == 1) spritesheet.loadFromFile("images/lever.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else spritesheet.loadFromFile("images/lever2.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(26,30), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(2);

	sprite->setAnimationSpeed(IDLE_INACTIVE, 10);
	sprite->addKeyframe(IDLE_INACTIVE, glm::vec2(x, 0));

	sprite->setAnimationSpeed(IDLE_ACTIVE, 4);
	sprite->addKeyframe(IDLE_ACTIVE, glm::vec2(0, 0));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Lever::update(int deltatime) {
	sprite->update(deltatime);
	if (active && sprite->animation() != IDLE_ACTIVE) sprite->changeAnimation(IDLE_ACTIVE);

	else if (!active && sprite->animation() != IDLE_INACTIVE) sprite->changeAnimation(IDLE_INACTIVE);
}

void Lever::render() {
	sprite->render();
}

void Lever::setTileMap(TileMap *tilemap) {
	map = tilemap;
}

void Lever::setPosition(const glm::vec2 &pos) {
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Lever::setActive(bool actived) {
	active = actived;
}

glm::ivec2 Lever::getPosition() {
	return posObject;
}

int Lever::getInverted() {
	return inverted;
}
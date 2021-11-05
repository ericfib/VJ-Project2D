#include "Barrier.h"

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


enum BarrierAnims
{
	IDLE
};

void Barrier::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl) {
	tileMapDispl = tileMapPos;
	currentLevel = lvl;
	float x = 1;
	float y = 1;
	sizex = 15;
	sizey = 64;
	spritesheet.loadFromFile("images/barrier.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(sizex, sizey), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(IDLE, 1);
	sprite->addKeyframe(IDLE, glm::vec2(0, 0));

	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Barrier::update(int deltatime) {
	sprite->update(deltatime);
}

void Barrier::render() {
	if (!destroyed) sprite->render();
}

void Barrier::setTileMap(TileMap *tilemap) {
	map = tilemap;
}

void Barrier::setPosition(const glm::vec2 &pos) {
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Barrier::setDestroyed(bool destroy)
{
	destroyed = destroy;
}

bool Barrier::collisionLeft(glm::ivec2 &pos, glm::ivec2 &size)
{

	if ((pos.x + size.x) > posObject.x - 1 && (pos.x + size.x) <= posObject.x + 1) {
		int i2 = pos.y + size.y;
		for (int i = pos.y; i < i2; i++) {
			if (i > posObject.y && i < posObject.y + sizey) return true;
		}
	}
	return false;
}

bool Barrier::collisionRight(glm::ivec2 &pos, glm::ivec2 &size)
{

	if (pos.x > posObject.x + sizex - 1 && pos.x <= posObject.x + sizex + 1) {
		int i2 = pos.y + size.y;
		for (int i = pos.y; i < i2; i++) {
			if (i > posObject.y && i < posObject.y + sizey) return true;
		}
	}
	return false;
}

glm::ivec2 Barrier::getPosition() {
	return posObject;
}
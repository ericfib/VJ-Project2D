#include "Box.h"
#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>


enum BoxAnims
{
	IDLE
};

void Box::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int lvl, int invert) {
	inverted = invert;
	tileMapDispl = tileMapPos;
	currentLevel = lvl;
	float x = 1;
	float y = 1;
	sizex = 32;
	sizey = 32;
	spritesheet.loadFromFile("images/box.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(sizex, sizey), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(1);

	sprite->setAnimationSpeed(IDLE, 1);
	sprite->addKeyframe(IDLE, glm::vec2(0, 0));


	sprite->changeAnimation(0);
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Box::update(int deltatime) {
	sprite->update(deltatime);
	if (pushLeft && !(map->collisionMoveRight(posObject, glm::ivec2(32, 32)).first)) {
		posObject.x += 2;
	}
	else if (pushRight && !(map->collisionMoveLeft(posObject, glm::ivec2(32, 32)).first)) {
		posObject.x -= 2;
	}
	int tilesize = map->getTileSize();
	int mid = (inverted == 1) ? 12 : 14;
	if ((posObject.y / tilesize) != mid) {
		posObject.y += 4 * inverted;
		if (inverted == 1) map->collisionMoveDown(posObject, glm::ivec2(32, 32), &posObject.y);
		else map->collisionMoveUp(posObject, glm::ivec2(32, 32), &posObject.y);
	}

	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Box::render() {
	sprite->render();
}

void Box::setTileMap(TileMap *tilemap) {
	map = tilemap;
}

void Box::setPosition(const glm::vec2 &pos) {
	posObject = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posObject.x), float(tileMapDispl.y + posObject.y)));
}

void Box::setPushLeft(bool push)
{
	pushLeft = push;
}

void Box::setPushRight(bool push)
{
	pushRight = push;
}


glm::ivec2 Box::getPosition() {
	return posObject;
}

bool Box::collisionLeft(glm::ivec2 &pos, glm::ivec2 &size)
{

	if ((pos.x + size.x) > posObject.x - 1 && (pos.x + size.x) <= posObject.x + 1) {
		int i2 = pos.y + size.y;
		for (int i = pos.y; i < i2; i++) {
			if (i > posObject.y && i < posObject.y + sizey) return true;
		}
	}
	return false;
}

bool Box::collisionRight(glm::ivec2 &pos, glm::ivec2 &size)
{

	if (pos.x > posObject.x + sizex - 1 && pos.x <= posObject.x + sizex + 1) {
		int i2 = pos.y + size.y;
		for (int i = pos.y; i < i2; i++) {
			if (i > posObject.y && i < posObject.y + sizey) return true;
		}
	}
	return false;
}

bool Box::collisionUp(glm::ivec2 & pos, glm::ivec2 & size)
{
	if (pos.y + size.y > posObject.y - 2 && pos.y + size.y <= posObject.y + 2) {
		int i2 = pos.x + size.x;
		for (int i = pos.x; i < i2; i++) {
			if (i >= posObject.x && i <= posObject.x + sizex) {
				return true;
			}
		}
	}
	return false;
}

bool Box::collisionDown(glm::ivec2 & pos, glm::ivec2 & size)
{
	if (pos.y > posObject.y + sizey - 4 && pos.y <= posObject.y + sizey + 4) {
		int i2 = pos.x + size.x;
		for (int i = pos.x; i < i2; i++) {
			if (i >= posObject.x && i <= posObject.x + sizex) {
				return true;
			}
		}
	}
	return false;
}

#include <cmath>
#include <iostream>
#include <GL/glew.h>
#include <GL/glut.h>
#include "Player.h"
#include "Game.h"


#define JUMP_ANGLE_STEP 4
#define JUMP_HEIGHT 96
#define FALL_STEP 4


enum PlayerAnims
{
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT, DEATH
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int invert, int lvl)
{	
	currentLevel = lvl;
	inverted = invert;
	bJumping = false;
	death = false;
	float x = 0.19;
	float y = 0.118;
	float baseY = 0.03;
	float baseX = 0.063;
	if (invert == 1) spritesheet.loadFromFile("images/player1-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	else spritesheet.loadFromFile("images/player2-sprite.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(7);
	
		sprite->setAnimationSpeed(STAND_LEFT, 4);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(baseX, baseY + 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(x + 2*baseX, baseY + 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 4);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(baseX, y * 3 + baseY*4));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(x + 2 * baseX, y * 3 + baseY * 4));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 10);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(baseX, 0.f + baseY));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(x + 2 * baseX, 0.f + baseY));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(2*x + 3 * baseX, 0.f + baseY));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(3*x + 4 * baseX, 0.f + baseY));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 10);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(baseX, y * 3 + baseY*4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(x + 2 * baseX, y * 3 + baseY*4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(2 * x + 3 * baseX, y * 3 + baseY*4));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(3 * x + 4 * baseX, y * 3 + baseY*4));

		sprite->setAnimationSpeed(JUMP_LEFT, 7);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(baseX, y + baseY*2));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(x + 2 * baseX, y + baseY*2));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(2 * x + 3 * baseX, y + baseY*2));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(3 * x + 4 * baseX, y + baseY*2));

		sprite->setAnimationSpeed(JUMP_RIGHT, 7);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(baseX, 4*y + baseY * 5));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(x + 2 * baseX, 4*y + baseY * 5));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(2 * x + 3 * baseX, 4*y + baseY * 5));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(3 * x + 4 * baseX, 4*y + baseY * 5));

		sprite->setAnimationSpeed(DEATH, 15);
		sprite->addKeyframe(DEATH, glm::vec2(baseX, 5 * y + baseY * 6));
		sprite->addKeyframe(DEATH, glm::vec2(x + 2 * baseX, 5 * y + baseY * 6));
		sprite->addKeyframe(DEATH, glm::vec2(2 * x + 3 * baseX, 5 * y + baseY * 6));
		sprite->addKeyframe(DEATH, glm::vec2(3 * x + 4 * baseX, 5 * y + baseY * 6));
		sprite->addKeyframe(DEATH, glm::vec2(baseX, 6 * y + baseY * 7));
		sprite->addKeyframe(DEATH, glm::vec2(x + 2 * baseX, 6 * y + baseY * 7));
		sprite->addKeyframe(DEATH, glm::vec2(2 * x + 3 * baseX, 6 * y + baseY * 7));
		sprite->addKeyframe(DEATH, glm::vec2(3 * x + 4 * baseX, 6 * y + baseY * 7));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	int tilesize = map->getTileSize();
	float posaux = posPlayer.y;
	if (!inverted) {
		posaux += 32;
	}

	//death by fall
	if (!death && (posaux / tilesize) == 14) {
		death = true;
		deathTime = 0;
		sprite->changeAnimation(DEATH);
	}

	if (death) {
		deathTime += deltaTime;
		if (deathTime > 1200) Game::instance().changeLevel(currentLevel);
	}

	else {


		if (Game::instance().getSpecialKey(GLUT_KEY_LEFT))
		{
			if (bJumping && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);
			else if (!bJumping && sprite->animation() != MOVE_LEFT)
				sprite->changeAnimation(MOVE_LEFT);
			posPlayer.x -= 2;
			if (map->collisionCactusLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}
			if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x += 2;
				sprite->changeAnimation(STAND_LEFT);
			}

		}
		else if (Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
		{
			if (bJumping && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
			else if (!bJumping && sprite->animation() != MOVE_RIGHT)
				sprite->changeAnimation(MOVE_RIGHT);
			posPlayer.x += 2;
			if (map->collisionCactusRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}
			if (map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
			{
				posPlayer.x -= 2;
				sprite->changeAnimation(STAND_RIGHT);
			}
		}
		else if (!bJumping)
		{
			if (sprite->animation() == MOVE_LEFT)
				sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == MOVE_RIGHT)
				sprite->changeAnimation(STAND_RIGHT);
		}

		if (bJumping)
		{
			jumpAngle += JUMP_ANGLE_STEP;

			if (map->collisionCactusUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
				posPlayer.y += 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}

			if (map->collisionCactusDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, inverted)) {
				posPlayer.y -= 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}

			if (jumpAngle == 180)
			{
				bJumping = false;
				posPlayer.y = startY;
			}
			else
			{
				posPlayer.y = int(startY - (96 * sin(3.14159f * jumpAngle / 180.f)*inverted));
				if (inverted == 1) {
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
					if (jumpAngle < 90) {
						bJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
					}
				}
				else {
					if (jumpAngle > 90)
						bJumping = !map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
					if (jumpAngle < 90) {
						bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
					}
				}
			}
		}
		else
		{
			posPlayer.y += FALL_STEP * inverted;
			if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
			else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);

			if (map->collisionCactusDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y, inverted)) {
				posPlayer.y -= 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}

			if (map->collisionCactusUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
				posPlayer.y += 2;
				death = true;
				deathTime = 0;
				sprite->changeAnimation(DEATH);
			}

			if (map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
			{
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(JUMP_LEFT);
					else sprite->changeAnimation(JUMP_RIGHT);
				}
			}
			if (map->collisionMoveUp(posPlayer, glm::ivec2(32, 32), &posPlayer.y)) {
				if (Game::instance().getSpecialKey(GLUT_KEY_UP))
				{
					bJumping = true;
					jumpAngle = 0;
					startY = posPlayer.y;
					if (sprite->animation() == MOVE_LEFT || sprite->animation() == STAND_LEFT)
						sprite->changeAnimation(JUMP_LEFT);
					else sprite->changeAnimation(JUMP_RIGHT);
				}
			}
		}
	}
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	if (!death || deathTime <= 535) sprite->render();
}

void Player::setTileMap(TileMap *tileMap)
{
	map = tileMap;
}

void Player::setPosition(const glm::vec2 &pos)
{
	posPlayer = pos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

glm::ivec2 Player::getPosition() {
	return posPlayer;
}






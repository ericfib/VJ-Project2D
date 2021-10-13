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
	STAND_LEFT, STAND_RIGHT, MOVE_LEFT, MOVE_RIGHT, JUMP_LEFT, JUMP_RIGHT
};


void Player::init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram)
{
	bJumping = false;
	float x = 0.21;
	float y = 0.084;
	spritesheet.loadFromFile("images/prueba.png", TEXTURE_PIXEL_FORMAT_RGBA);
	sprite = Sprite::createSprite(glm::ivec2(32, 32), glm::vec2(x, y), &spritesheet, &shaderProgram);
	sprite->setNumberAnimations(6);
	
		sprite->setAnimationSpeed(STAND_LEFT, 4);
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(STAND_LEFT, glm::vec2(0.25f, 0.f));
		
		sprite->setAnimationSpeed(STAND_RIGHT, 4);
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.f, y*3));
		sprite->addKeyframe(STAND_RIGHT, glm::vec2(0.25f, y*3));
		
		sprite->setAnimationSpeed(MOVE_LEFT, 10);
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.25f, 0.f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.5f, 0.0f));
		sprite->addKeyframe(MOVE_LEFT, glm::vec2(0.75f, 0.0f));
		
		sprite->setAnimationSpeed(MOVE_RIGHT, 10);
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.f, y * 3));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.25f, y * 3));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.5f, y * 3));
		sprite->addKeyframe(MOVE_RIGHT, glm::vec2(0.75f, y * 3));

		sprite->setAnimationSpeed(JUMP_LEFT, 7);
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.f, y));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.25f, y));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.5f, y));
		sprite->addKeyframe(JUMP_LEFT, glm::vec2(0.75f, y));

		sprite->setAnimationSpeed(JUMP_RIGHT, 7);
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.f, 4*y));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.25f, 4*y));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.5f, 4*y));
		sprite->addKeyframe(JUMP_RIGHT, glm::vec2(0.75f, 4*y));
		
	sprite->changeAnimation(0);
	tileMapDispl = tileMapPos;
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
	
}

void Player::update(int deltaTime)
{
	sprite->update(deltaTime);
	if(Game::instance().getSpecialKey(GLUT_KEY_LEFT))
	{
		if (bJumping && sprite->animation() != JUMP_LEFT) sprite->changeAnimation(JUMP_LEFT);
		else if (!bJumping && sprite->animation() != MOVE_LEFT)
			sprite->changeAnimation(MOVE_LEFT);
		posPlayer.x -= 2;
		if (map->collisionMoveLeft(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x += 2;
			sprite->changeAnimation(STAND_LEFT);
		}
	}
	else if(Game::instance().getSpecialKey(GLUT_KEY_RIGHT))
	{
		if (bJumping && sprite->animation() != JUMP_RIGHT) sprite->changeAnimation(JUMP_RIGHT);
		else if(!bJumping && sprite->animation() != MOVE_RIGHT)
			sprite->changeAnimation(MOVE_RIGHT);
		posPlayer.x += 2;
		if(map->collisionMoveRight(posPlayer, glm::ivec2(32, 32)))
		{
			posPlayer.x -= 2;
			sprite->changeAnimation(STAND_RIGHT);
		}
	}
	else if (!bJumping)
	{
		if(sprite->animation() == MOVE_LEFT)
			sprite->changeAnimation(STAND_LEFT);
		else if(sprite->animation() == MOVE_RIGHT)
			sprite->changeAnimation(STAND_RIGHT);
	}
	
	if(bJumping)
	{
		jumpAngle += JUMP_ANGLE_STEP;
		if(jumpAngle == 180)
		{
			bJumping = false;
			posPlayer.y = startY;
		}
		else
		{
			posPlayer.y = int(startY - 96 * sin(3.14159f * jumpAngle / 180.f));
			if(jumpAngle > 90)
				bJumping = !map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y);
		}
	}
	else
	{
		posPlayer.y += FALL_STEP;
		if (sprite->animation() == JUMP_LEFT) sprite->changeAnimation(STAND_LEFT);
		else if (sprite->animation() == JUMP_RIGHT) sprite->changeAnimation(STAND_RIGHT);
		if(map->collisionMoveDown(posPlayer, glm::ivec2(32, 32), &posPlayer.y))
		{
			if(Game::instance().getSpecialKey(GLUT_KEY_UP))
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
	
	sprite->setPosition(glm::vec2(float(tileMapDispl.x + posPlayer.x), float(tileMapDispl.y + posPlayer.y)));
}

void Player::render()
{
	sprite->render();
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





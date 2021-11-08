#ifndef _BARRIER_INCLUDE
#define _BARRIER_INCLUDE

#include "DynamicObject.h"

class Barrier : public DynamicObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int currentLevel, int invert);
	void update(int deltatime);
	void render();

	void setTileMap(TileMap *tilemap);
	void setPosition(const glm::vec2 &pos);
	void setDestroyed(bool destroy);
	bool collisionLeft(glm::ivec2 & pos, glm::ivec2 &size);
	bool collisionRight(glm::ivec2 & pos, glm::ivec2 &size);

	glm::ivec2 getPosition();


private:
	int currentLevel, inverted;
	bool destroyed;
};

#endif


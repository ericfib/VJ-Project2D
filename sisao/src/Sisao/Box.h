#ifndef _BOX_INCLUDE
#define _BOX_INCLUDE

#include "DynamicObject.h"

class Box : public DynamicObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int currentLevel, int invert);
	void update(int deltatime);
	void render();

	void setTileMap(TileMap *tilemap);
	void setPosition(const glm::vec2 &pos);
	void setPushLeft(bool push);
	void setPushRight(bool push);

	bool collisionLeft(glm::ivec2 & pos, glm::ivec2 &size);
	bool collisionRight(glm::ivec2 & pos, glm::ivec2 &size);
	bool collisionUp(glm::ivec2 & pos, glm::ivec2 &size);
	bool collisionDown(glm::ivec2 & pos, glm::ivec2 &size);

	glm::ivec2 getPosition();


private:
	int currentLevel, inverted;
	bool pushLeft, pushRight;
};

#endif


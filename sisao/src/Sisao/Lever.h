#ifndef _LEVER_INCLUDE
#define _LEVER_INCLUDE

#include "DynamicObject.h"

class Lever : public DynamicObject
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int currentLevel, int invert);
	void update(int deltatime);
	void render();

	void setTileMap(TileMap *tilemap);
	void setPosition(const glm::vec2 &pos);
	void setActive(bool actived);

	glm::ivec2 getPosition();
	int getInverted();


private:
	int currentLevel, activedTime, inverted;
	bool active;
};

#endif


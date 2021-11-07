#ifndef _FLAG_INCLUDE
#define _FLAG_INCLUDE

#include "DynamicObject.h"

class Flag : public DynamicObject 
{
public:
	void init(const glm::ivec2 &tileMapPos, ShaderProgram &shaderProgram, int currentLevel, int invert);
	void update(int deltatime);
	void render();

	void setTileMap(TileMap *tilemap);
	void setPosition(const glm::vec2 &pos);
	void setActive(bool actived);
	bool isActive() { return active; };

	glm::ivec2 getPosition();

private:
	int currentLevel, activedTime;
	bool active;
};

#endif

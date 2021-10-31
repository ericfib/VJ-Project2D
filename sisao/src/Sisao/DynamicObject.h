#ifndef _DYNAMIC_OBJECT_INCLUDE
#define _DYNAMIC_OBJECT_INCLUDE

#include "Sprite.h"
#include "TileMap.h"

class DynamicObject
{
public:


	virtual void init() {};
	virtual void update(int deltatime) {};
	virtual void render() {};

	virtual void setTileMap(TileMap *tileMap) {};
	virtual void setPosition(const glm::vec2 &pos) {};

protected:

	glm::ivec2 tileMapDispl, posObject;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif
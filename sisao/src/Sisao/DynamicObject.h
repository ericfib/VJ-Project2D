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
	virtual void setActive(bool actived) {};
	virtual void setDestroyed(bool actived) {};
	virtual void setPushLeft(bool push) {};
	virtual void setPushRight(bool push) {};

	virtual glm::ivec2 getPosition() { return posObject; };
	virtual pair<int, int> getSize() { return make_pair(sizex, sizey); };
	virtual int getInverted() { return 0; };
	virtual bool isActive() { return 0; };

	virtual bool collisionLeft(glm::ivec2 &pos, glm::ivec2 &size) { return false; };
	virtual bool collisionRight(glm::ivec2 &pos, glm::ivec2 &size) { return false; };
	virtual bool collisionUp(glm::ivec2 &pos, glm::ivec2 &size) { return false; };
	virtual bool collisionDown(glm::ivec2 &pos, glm::ivec2 &size) { return false; };

protected:

	glm::ivec2 tileMapDispl, posObject;
	int sizex, sizey;
	Texture spritesheet;
	Sprite *sprite;
	TileMap *map;
};

#endif
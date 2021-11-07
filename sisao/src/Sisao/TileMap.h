#ifndef _TILE_MAP_INCLUDE
#define _TILE_MAP_INCLUDE


#include <glm/glm.hpp>
#include <vector>
#include "Texture.h"
#include "ShaderProgram.h"


// Class Tilemap is capable of loading a tile map from a text file in a very
// simple format (see level01.txt for an example). With this information
// it builds a single VBO that contains all tiles. As a result the render
// method draws the whole map independently of what is visible.


class TileMap
{

public:
	// Tile maps can only be created inside an OpenGL context
	static TileMap *createTileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);

	TileMap(const string &levelFile, const glm::vec2 &minCoords, ShaderProgram &program);
	~TileMap();

	void render() const;
	void free();
	
	int getTileSize() const { return tileSize; }

	pair<int, int> getPosPlayer(int p) { return (p == 1) ? players[0].second : players[1].second;}
	vector<pair<string, pair<int, int>>> getDynamicObjects() { return dynamic_objects; }

	pair<bool,bool> collisionMoveLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	pair<bool,bool> collisionMoveRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	pair<bool,bool> collisionMoveDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	pair<bool,bool> collisionMoveUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;

	bool collisionCactusLeft(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionCactusRight(const glm::ivec2 &pos, const glm::ivec2 &size) const;
	bool collisionCactusUp(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY) const;
	bool collisionCactusDown(const glm::ivec2 &pos, const glm::ivec2 &size, int *posY, int inverted) const;
	

	
private:
	bool loadLevel(const string &levelFile);
	void prepareArrays(const glm::vec2 &minCoords, ShaderProgram &program);

private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	glm::ivec2 position, mapSize, tilesheetSize;
	int tileSize, blockSize;
	vector <pair<string, pair<int,int>>> dynamic_objects, players;
	Texture tilesheet;
	glm::vec2 tileTexSize;
	int *map;

};


#endif // _TILE_MAP_INCLUDE



#pragma once
#include <vector>
#include <string>

#include "Tile.h"
#include "Player.h"

class Enemy;
class Tile;
enum class TYPE;

class Level
{
public:
	Level(std::vector<std::string> data, Player *p, std::vector<Enemy *> &e);

	std::vector< std::vector<Tile *> > getLevelData();
	void setTileSprite(int x, int y, char c, TYPE t);
	bool isComplete();

	~Level();

private:
	std::vector< std::vector<Tile *> > _levelData;
	bool _isComplete;
};


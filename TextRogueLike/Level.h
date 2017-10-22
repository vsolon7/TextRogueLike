#pragma once
#include <vector>
#include <string>

#include "Tile.h"
#include "Player.h"
#include "LinkedList.h"

class Enemy;
class Tile;
enum class TYPE;

template <typename T>
class LinkedList;

class Level
{
public:
	Level(std::vector<std::string> data, Player *p, LinkedList<Enemy *> &e);

	std::vector< std::vector<Tile *> > getLevelData();
	void setTileSprite(int x, int y, char c, TYPE t);
	bool isComplete();

	~Level();

private:
	std::vector< std::vector<Tile *> > _levelData;
	bool _isComplete;
};


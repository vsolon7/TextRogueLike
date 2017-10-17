#pragma once
#include <vector>
#include <string>

#include "Tile.h"
#include "Player.h"

class Level
{
public:
	Level(std::vector<std::string> data, Player *p);

	~Level();

private:
	std::vector< std::vector<Tile *> > _levelData;
};


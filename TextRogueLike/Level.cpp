#include <iostream>

#include "Level.h"

Level::Level(std::vector<std::string> data, Player *p)
{
	std::vector<Tile *> buffer;

	//loads the level into _levelData based on the data in the file
	for (int y = 0; y < data.size(); y++)
	{
		for (int x = 0; x < data[y].size(); x++)
		{
			switch (data[y][x])
			{
			case '.':
				buffer.push_back(new Tile(EMPTY_TILE, nullptr, x, y));
				break;
			case '@':
				buffer.push_back(new Tile(p->getSprite(), nullptr, x, y));
				p->setCurrPos(x, y);
				break;
			case '#':
				buffer.push_back(new Tile(WALL_TILE, nullptr, x, y));
			}
		}
		_levelData.push_back(buffer);
		buffer.clear();
	}

	_isComplete = false;
}

std::vector< std::vector<Tile *> > Level::getLevelData()
{
	return _levelData;
}

void Level::setTileSprite(int x, int y, char c)
{
	_levelData[y][x]->setSprite(c);
}

bool Level::isComplete()
{
	return _isComplete;
}

Level::~Level()
{
}

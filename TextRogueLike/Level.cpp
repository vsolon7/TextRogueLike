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
				buffer.push_back(new Tile( (char) TYPE::EMPTY, nullptr, x, y, TYPE::EMPTY));
				break;
			case '@':
				buffer.push_back(new Tile(p->getSprite(), nullptr, x, y, TYPE::PLAYER));
				p->setCurrPos(x, y);
				break;
			case '#':
				buffer.push_back(new Tile( (char) TYPE::WALL, nullptr, x, y, TYPE::WALL));
				break;
			case '%':
				buffer.push_back(new Tile( (char) TYPE::LOCKED_DOOR, nullptr, x, y, TYPE::LOCKED_DOOR));
				break;
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

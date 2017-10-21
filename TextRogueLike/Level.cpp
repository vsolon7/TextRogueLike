#include <iostream>

#include "Level.h"
#include "Snake.h"

Level::Level(std::vector<std::string> data, Player *p, std::vector<Enemy *> &e)
{
	std::vector<Tile *> buffer;

	//loads the level into _levelData based on the data in the file
	for (unsigned int y = 0; y < data.size(); y++)
	{
		for (unsigned int x = 0; x < data[y].size(); x++)
		{
			switch (data[y][x])
			{
			case '.':
				buffer.push_back(new Tile( (char) TILE::EMPTY, nullptr, x, y, TYPE::EMPTY));
				break;
			case '@':
				buffer.push_back(new Tile(p->getSprite(), nullptr, x, y, TYPE::PLAYER));
				p->setCurrPos(x, y);
				break;
			case '#':
				buffer.push_back(new Tile( (char) TILE::WALL, nullptr, x, y, TYPE::WALL));
				break;
			case '%':
				buffer.push_back(new Tile( (char) TILE::LOCKED_DOOR, nullptr, x, y, TYPE::LOCKED_DOOR));
				break;
			case 'S':
				buffer.push_back(new Tile((char)TILE::SNAKE, nullptr, x, y, TYPE::ENEMY));
				e.push_back(new Snake(x, y));
				break;
			case 'E':
				buffer.push_back(new Tile((char) TILE::ENEMY, nullptr, x, y, TYPE::ENEMY));
				e.push_back(new Enemy(x, y));
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

void Level::setTileSprite(int x, int y, char c, TYPE t)
{
	_levelData[y][x]->setSprite(c, t);
}

bool Level::isComplete()
{
	return _isComplete;
}

Level::~Level()
{
}

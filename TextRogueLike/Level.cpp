#include "Level.h"

Level::Level(std::vector<std::string> data, Player *p)
{
	std::vector<Tile *> buffer;

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
}

Level::~Level()
{
}

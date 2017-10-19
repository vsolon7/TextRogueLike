#include <random>
#include <time.h>

#include "Snake.h"

Snake::Snake(int x, int y)
{
	_maxHP = SNAKE_DEFAULT_HP;
	_currHP = SNAKE_DEFAULT_HP;
	_damage = SNAKE_DEFAULT_DAMAGE;
	_armor = SNAKE_DEFAULT_ARMOR;
	_viewDistance = SNAKE_DEFAULT_VIEW;
	_currX = x;
	_currY = y;
}

void Snake::move(Level *l, int x, int y)
{
	std::vector< std::vector<Tile *> > tempLvl = l->getLevelData();

	if (tempLvl[_currY + y][_currX + x]->isEmpty())
	{
		l->setTileSprite(_currX, _currY, (char)TYPE::EMPTY);
		_currX += x;
		_currY += y;
		l->setTileSprite(_currX, _currY, (char)TYPE::SNAKE);
		tempLvl[_currY][_currX]->setEnemyOnTile(this);
	}
	else
	{
		return;
	}
}

Snake::~Snake()
{
}

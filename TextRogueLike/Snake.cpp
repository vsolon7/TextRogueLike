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

Snake::Snake(int x, int y, int hp, int d, int a, int view)
{
	_maxHP = hp;
	_currHP = hp;
	_damage = d;
	_armor = a;
	_viewDistance = view;
	_currX = x;
	_currY = y;
}

void Snake::move(Level *l, Player *p, int x, int y, std::vector<StatusInfo *> &s)
{
	std::vector< std::vector<Tile *> > tempLvl = l->getLevelData();

	if (tempLvl[_currY + y][_currX + x]->isEmpty())
	{
		l->setTileSprite(_currX, _currY, (char)TILE::EMPTY, TYPE::EMPTY);
		_currX += x;
		_currY += y;
		l->setTileSprite(_currX, _currY, (char)TILE::SNAKE, TYPE::ENEMY);
		tempLvl[_currY][_currX]->setEnemyOnTile(this);
	}
	//if they're close enough to attack, aka 1 square away, not including diagonals
	if (_distFromPlayer < SQRT_2)
	{
		double tentDamage = _damage * (1 - p->getDamageReduc());

		int intDamage = (int) std::round(tentDamage);

		s.push_back(new StatusInfo(STATUSTYPE::BATTLE, "The snake attacks you for " + std::to_string(intDamage) + " damage!", s.size()));

		p->increaseCurrHP(-intDamage);
	}
	else
	{
		return;
	}
}

Snake::~Snake()
{
}

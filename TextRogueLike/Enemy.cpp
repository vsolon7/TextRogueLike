#include <math.h>
#include <time.h>

#include "Enemy.h"
#include "Utility.h"

Enemy::Enemy()
{

}

Enemy::Enemy(int x, int y)
{
	_maxHP = 1;
	_currHP = 1;
	_damage = 0;
	_armor = 0;
	_viewDistance = 3;
	_currX = x;
	_currY = y;
}
//GETTERS AND SETTERS
int Enemy::getMaxHP()
{
	return _maxHP;
}
int Enemy::getCurrHP()
{
	return _currHP;
}
int Enemy::getDamage()
{
	return _damage;
}
int Enemy::getArmor()
{
	return _armor;
}
int Enemy::getCurrX()
{
	return _currX;
}
int Enemy::getCurrY()
{
	return _currY;
}
int Enemy::getViewDistance()
{
	return _viewDistance;
}
void Enemy::setMaxHP(int hp)
{
	_maxHP = hp;
}
void Enemy::setCurrHP(int hp)
{
	_currHP = hp;
}
void Enemy::setDamage(int d) 
{
	_damage = d;
}
void Enemy::setArmor(int a)
{
	_armor = a;
}
void Enemy::setCurrPos(int x, int y) 
{
	_currX = x;
	_currY = y;
}
void Enemy::setViewDistance(int v)
{
	_viewDistance = v;
}
//GETTERS AND SETTERS

double Enemy::getDistance(int x1, int y1, int x2, int y2)
{
	//the the QUAKEIII fast inv square root is faster than the compiler optimized one. for some reason.
	double distance = 1 / Utility::fastInvSqrt(((x2 - x1) * (x2 - x1)) + ((y2 - y1) * (y2 - y1)));

	return distance;
}

void Enemy::idleMove(Level *l, Player *p)
{
	int playerX = p->getCurrX();
	int playerY = p->getCurrY();

	double dist = getDistance(_currX, _currY, playerX, playerY);

	if ((int)dist <= _viewDistance)
	{
		attack(l, p);
	}
	else
	{
		std::uniform_int_distribution<int> rand(-1, 1);
		int xDir = rand(Utility::randEngine);
		int yDir = rand(Utility::randEngine);
		move(l, xDir, yDir);
	}
}

void Enemy::move(Level *l, int x, int y) 
{
	std::vector< std::vector<Tile *> > tempLvl = l->getLevelData();

	if (tempLvl[_currY + y][_currX + x]->isEmpty())
	{
		l->setTileSprite(_currX, _currY, (char)TYPE::EMPTY);
		_currX += x;
		_currY += y;
		l->setTileSprite(_currX, _currY, 'X');
		tempLvl[_currY][_currX]->setEnemyOnTile(this);
	}
	else
	{
		return;
	}
}
void Enemy::attack(Level *l, Player *p)
{
	int playerX = p->getCurrX();
	int playerY = p->getCurrY();
	int xDist = abs(playerX - _currX);
	int yDist = abs(playerY - _currY);

	bool movingHoriz = (xDist > yDist) ? true : false;
	bool movingPositive = false;

	//find which axis is the farthest and move along that one
	switch (movingHoriz)
	{
	case true:
		movingPositive = (_currX < playerX) ? true : false;

		switch (movingPositive)
		{
		case true:
			move(l, 1, 0);
			break;
		case false:
			move(l, -1, 0);
			break;
		}

		break;
	case false:
		movingPositive = (_currY < playerY) ? true : false;

		switch (movingPositive)
		{
		case true:
			move(l, 0, 1);
			break;
		case false:
			move(l, 0, -1);
			break;
		}

		break;
	}
}

Enemy::~Enemy()
{
}

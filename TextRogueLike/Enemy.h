#pragma once
#include <random>

#include "Level.h"

class Level;
struct Player;

class Enemy
{
public:
	Enemy();
	Enemy(int x, int y);
	~Enemy();

	//BEGIN GETTERS & SETTERS
	int getMaxHP();
	int getCurrHP();
	int getDamage();
	int getArmor();
	int getCurrX();
	int getCurrY();
	int getViewDistance();

	void setMaxHP(int hp);
	void setCurrHP(int hp);
	void setDamage(int d);
	void setArmor(int a);
	void setCurrPos(int x, int y);
	void setViewDistance(int v);
	//END GETTERS AND SETTERS

	virtual void idleMove(Level *l, Player *p);
	virtual void move(Level *l, int x, int y);
	virtual void attack(Level *l, Player *p);

	double getDistance(int x1, int y1, int x2, int y2);
protected:
	int _maxHP, _currHP, _damage, _armor, _currX, _currY, _viewDistance;
};


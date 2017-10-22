#pragma once
#include <random>

#include "StatusInfo.h"
#include "Level.h"

#define SQRT_2 1.414213

class Level;
class Player;

//generic enemy class, other enemies inhereit from this

class Enemy
{
public:
	Enemy();
	Enemy(int x, int y);
	Enemy(int x, int y, int hp, int d, int a, int view);
	~Enemy();

	//BEGIN GETTERS & SETTERS
	int getMaxHP();
	int getCurrHP();
	int getDamage();
	int getArmor();
	double getDamageReduc();
	int getCurrX();
	int getCurrY();
	int getViewDistance();

	void setMaxHP(int hp);
	void setCurrHP(int hp);
	void increaseCurrHP(int hp);
	void setDamage(int d);
	void setArmor(int a);
	void setCurrPos(int x, int y);
	void setViewDistance(int v);
	//END GETTERS AND SETTERS

	virtual void idleMove(Level *l, Player *p, std::vector<StatusInfo *> &s);
	virtual void move(Level *l, Player *p, int x, int y, std::vector<StatusInfo *> &s);
	virtual void attack(Level *l, Player *p, std::vector<StatusInfo *> &s);

	double getDistance(int x1, int y1, int x2, int y2);
protected:
	int _maxHP, _currHP, _damage, _armor, _currX, _currY, _viewDistance;
	double _distFromPlayer;
};


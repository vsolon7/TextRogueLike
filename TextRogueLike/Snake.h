#pragma once

#include "Enemy.h"

#define SNAKE_DEFAULT_HP 10
#define SNAKE_DEFAULT_DAMAGE 2
#define SNAKE_DEFAULT_ARMOR 1
#define SNAKE_DEFAULT_VIEW 3

class Level;

class Snake : public Enemy
{
public:
	Snake(int x, int y);
	Snake(int x, int y, int hp, int d, int a, int view);

	void move(Level *l, Player *p, int x, int y, std::vector<StatusInfo *> &s);

	~Snake();
};


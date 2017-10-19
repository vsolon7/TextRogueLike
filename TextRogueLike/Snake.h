#pragma once

#include "Enemy.h"

#define SNAKE_DEFAULT_HP 10
#define SNAKE_DEFAULT_DAMAGE 2
#define SNAKE_DEFAULT_ARMOR 1
#define SNAKE_DEFAULT_VIEW 2

class Level;

class Snake : public Enemy
{
public:
	Snake(int x, int y);

	void move(Level *l, int x, int y);

	~Snake();
};


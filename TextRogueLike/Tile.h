#pragma once

#include "Enemy.h"

class Enemy;

enum class TILE
{
	WALL = 254,
	EMPTY = ' ',
	PLAYER,
	ENEMY = '?',
	ORC = 'O', ZOMBIE = 'Z', SNAKE = 'S',
	TRAP,
	LOCKED_DOOR = '%'
};

enum class TYPE
{
	WALL,
	EMPTY,
	PLAYER,
	ENEMY,
	TRAP,
	LOCKED_DOOR
};

class Tile
{
public:

	Tile(char s, Enemy *e, int x, int y, TYPE t);
	~Tile();

	//returns the enemy occupying the tile, if any
	Enemy * getEnemyOnTile();

	//returns true if the tile is empty
	bool isEmpty();

	//set whether the tile is empty
	void setEmpty(bool e);

	char getSprite();

	void setSprite(char c, TYPE t);

	void setEnemyOnTile(Enemy *e);

	TYPE getType();

private:
	Enemy *_enemyOnTile;
	bool _empty;
	int _xPos, _yPos;
	char _sprite;
	TYPE _type;
};
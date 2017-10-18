#pragma once
#include "Enemy.h"

#define WALL_TILE '#'
#define EMPTY_TILE ' '
#define PLAYER_TILE '@'
#define	ZOMBIE_TILE 'Z'
#define	ORC_TILE 'O'

struct Tile
{

	Tile::Tile(char s, Enemy *e, int x, int y)
	{
		_xPos = x;
		_yPos = y;
		_sprite = s;
		_enemyOnTile = e;

		if (s == EMPTY_TILE)
			_empty = true;
		else
			_empty = false;
	}

	//returns the enemy occupying the tile, if any
	Enemy * Tile::getEnemyOnTile()
	{
		return _enemyOnTile;
	}

	bool Tile::isEmpty()
	{
		return _empty;
	}

	void Tile::setEmpty(bool e)
	{
		_empty = e;
	}

	char getSprite()
	{
		return _sprite;
	}

	void setSprite(char c)
	{
		_sprite = c;
	}

private:
	Enemy *_enemyOnTile;
	bool _empty;
	int _xPos, _yPos;
	char _sprite;
};
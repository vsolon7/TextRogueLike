#pragma once

#include "Enemy.h"

class Enemy;

enum class TYPE
{
	WALL = 254,
	EMPTY = ' ',
	PLAYER,
	ENEMY,
	ORC = 'O', ZOMBIE = 'Z', SNAKE = 'S',
	TRAP,
	LOCKED_DOOR = '%'
};

struct Tile
{
	Tile::Tile(char s, Enemy *e, int x, int y, TYPE t)
	{
		_xPos = x;
		_yPos = y;
		_sprite = s;
		_enemyOnTile = e;
		type = t;

		if (t == TYPE::EMPTY)
			_empty = true;
		else
			_empty = false;
	}

	//returns the enemy occupying the tile, if any
	Enemy * Tile::getEnemyOnTile()
	{
		return _enemyOnTile;
	}

	//returns true if the tile is empty
	bool Tile::isEmpty()
	{
		return _empty;
	}

	//set whether the tile is empty
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
		//sets the tiles sprite to the parameter
		//if it is being set to EMPTY_TILE, set the tile as empty
		_sprite = c;
		if (c == (char)TYPE::EMPTY)
		{
			_enemyOnTile = nullptr;
			_empty = true;
		}
		else
			_empty = false;
	}
	void setEnemyOnTile(Enemy *e)
	{
		_enemyOnTile = e;
	}

private:
	Enemy *_enemyOnTile;
	bool _empty;
	int _xPos, _yPos;
	char _sprite;
	TYPE type;
};
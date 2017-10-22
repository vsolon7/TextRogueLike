#include "Tile.h"

Tile::Tile(char s, Enemy *e, int x, int y, TYPE t)
{
	_xPos = x;
	_yPos = y;
	_sprite = s;
	_enemyOnTile = e;
	_type = t;

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

char Tile::getSprite()
{
	return _sprite;
}

void Tile::setSprite(char c, TYPE t)
{
	//sets the tiles sprite to the parameter
	//if it is being set to EMPTY_TILE, set the tile as empty
	_sprite = c;
	if (t == TYPE::EMPTY)
	{
		_enemyOnTile = nullptr;
		_empty = true;
	}
	else
		_empty = false;
	_type = t;
}
void Tile::setEnemyOnTile(Enemy *e)
{
	_enemyOnTile = e;
}
TYPE Tile::getType()
{
	return _type;
}

Tile::~Tile()
{

}
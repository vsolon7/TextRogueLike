#include "Player.h"

Player::Player(int x, int y)
{
	_maxHP = PLAYER_DEFAULT_HP;
	_currHP = _maxHP;
	_damage = PLAYER_DEFAULT_DAMAGE;
	_armor = PLAYER_DEFAULT_ARMOR;
	_currX = x;
	_currY = y;
	_sprite = PLAYER_DEFAULT_SPRITE;
}

int Player::getMaxHP()
{
	return _maxHP;
}

double Player::getDamageReduc()
{
	return (double)(_armor) / (10 + _armor);
}

void Player::increaseMaxHP(int hp)
{
	_maxHP += hp;
}

void Player::increaseCurrHP(int hp)
{
	if (hp > _maxHP)
		_currHP = _maxHP;
	else
		_currHP += hp;
}

int Player::getCurrHP()
{
	return _currHP;
}

void Player::increaseDamage(int d)
{
	_damage += d;
}

int Player::getDamage()
{
	return _damage;
}

void Player::increaseArmor(int a)
{
	_armor += a;
}

int Player::getArmor()
{
	return _armor;
}

void Player::setCurrPos(int x, int y)
{
	_currX = x;
	_currY = y;
}

int Player::getCurrX()
{
	return _currX;
}

int Player::getCurrY()
{
	return _currY;
}

char Player::getSprite()
{
	return _sprite;
}

Player::~Player()
{

}
#pragma once

#define PLAYER_DEFAULT_DAMAGE 5
#define PLAYER_DEFAULT_HP 40
#define PLAYER_DEFAULT_ARMOR 1
#define PLAYER_DEFAULT_SPRITE (char) 233

//basically just a huge struct of a player. should probably be a class tbh. will change in the future
struct Player
{
public:
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

private:
	int _currHP;
	int _maxHP;
	int _damage;
	int _armor;
	int _currX;
	int _currY;
	char _sprite;
};
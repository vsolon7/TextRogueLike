#include "Player.h"

//REMEMBER TO DELETE PLAYER ITEMS
//REMEMBER TO DELETE PLAYER ITEMS
//REMEMBER TO DELETE PLAYER ITEMS
//REMEMBER TO DELETE PLAYER ITEMS
//REMEMBER TO DELETE PLAYER ITEMS
//REMEMBER TO DELETE PLAYER ITEMS

Player::Player(int x, int y)
{
	_maxHP = PLAYER_DEFAULT_HP;
	_currHP = _maxHP;
	_damage = PLAYER_DEFAULT_DAMAGE;
	_armor = PLAYER_DEFAULT_ARMOR;
	_currX = x;
	_currY = y;
	_sprite = PLAYER_DEFAULT_SPRITE;

	for (int i = 0; i < 4; i++)
	{
		inventory.push_back({ nullptr,nullptr,nullptr,nullptr });
	}

	//for testing
	addItemToInv(new Item('A', 12, 400, -5, "The letter", ITEMTYPE::WEAPON));
	addItemToInv(new Item('C', 0, 0, 0, "The other letter", ITEMTYPE::WEAPON));
	//for testing

	for (int i = 0; i < 6; i++)
	{
		equipped.push_back(new Item('O', 0, 0, 0, "None", ITEMTYPE::WEAPON));
		equipped.push_back(new Item('O', 0, 0, 0, "None", ITEMTYPE::ARMOR));
	}
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

void Player::setSprite(char c)
{
	_sprite = c;
}

char Player::getSprite()
{
	return _sprite;
}

int Player::addItemToInv(Item *itm)
{
	for (int y = 0; y < inventory.size(); y++)
	{
		for (int x = 0; x < inventory[y].size(); x++)
		{
			if (inventory[y][x] == nullptr)
			{
				inventory[y][x] = itm;
				return 0;
			}
		}
	}
	return 1;
}

Player::~Player()
{

}
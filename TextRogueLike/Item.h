#pragma once
#include <string>

enum class ITEMTYPE
{
	WEAPON, ARMOR
};

struct Item
{
	Item(char s, int d, int a, int hp, std::string n, ITEMTYPE t);
	~Item();

	int damageIncrease, armorIncrease, hpIncrease;
	char sprite;
	std::string name;
	ITEMTYPE type;
};


#include "Item.h"



Item::Item(char s, int d, int a, int hp, std::string n, ITEMTYPE t) : 
	sprite(s), 
	damageIncrease(d), 
	armorIncrease(a), 
	hpIncrease(hp),
	name(n),
	type(t)
{

}


Item::~Item()
{
}

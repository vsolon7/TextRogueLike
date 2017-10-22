#pragma once

#define PLAYER_DEFAULT_DAMAGE 5
#define PLAYER_DEFAULT_HP 40
#define PLAYER_DEFAULT_ARMOR 1
#define PLAYER_DEFAULT_SPRITE (char) 233

//armor formula ( x / (10 + x) )

//basically just a huge struct of a player. should probably be a class tbh. will change in the future
class Player
{
public:
	Player(int x, int y);
	~Player();

	//GETTERS AND SETTERS
	int getMaxHP();
	double getDamageReduc();
	void increaseMaxHP(int hp);
	void increaseCurrHP(int hp);
	int getCurrHP();
	void increaseDamage(int d);
	int getDamage();
	void increaseArmor(int a);
	int getArmor();
	void setCurrPos(int x, int y);
	int getCurrX();
	int getCurrY();
	void setSprite(char c);
	char getSprite();
	//END GETTERS AND SETTERS

private:
	int _currHP;
	int _maxHP;
	int _damage;
	int _armor;
	int _currX;
	int _currY;
	char _sprite;
};
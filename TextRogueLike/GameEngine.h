#pragma once
#include <vector>
#include <string>

#include "Level.h"
#include "Player.h"

class GameEngine
{
public:
	GameEngine();

	void gameLoop();
	void run();
	void loadLevel(std::string &filePath, Player *p);
	void deleteCurrLevel();
	Player * getPlayer();

	~GameEngine();
private:
	Level *_currLevel;
	Player *_player;
};


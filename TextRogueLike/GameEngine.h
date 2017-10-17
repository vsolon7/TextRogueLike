#pragma once
#include <vector>
#include <string>

#include "Level.h"

class GameEngine
{
public:
	GameEngine();

	void gameLoop();
	void run();
	void loadLevel(std::string &filePath);
	void deleteCurrLevel();

	~GameEngine();
private:
	Level *_currLevel;

};


#include <Windows.h>
#include <iostream>
#include <string>

#include "GameEngine.h"
#include "IOManager.h"

int main()
{
	GameEngine game;

	std::string fileName = "LevelOne.txt";

	game.loadLevel(fileName);

	system("pause");
	return 0;
}
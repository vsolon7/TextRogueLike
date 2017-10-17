#include "GameEngine.h"
#include "IOManager.h"


GameEngine::GameEngine()
{
}

void GameEngine::gameLoop()
{

}

void GameEngine::run()
{
	std::string filePath = "LevelOne.txt";

	loadLevel(filePath);
}

void GameEngine::loadLevel(std::string &filePath)
{
	_currLevel = new Level(IOManager::readFile(filePath));
}

void GameEngine::deleteCurrLevel()
{
	delete _currLevel;
}

GameEngine::~GameEngine()
{
}

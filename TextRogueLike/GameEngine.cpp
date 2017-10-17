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
	_player = new Player(0,0);
	_player->setCurrPos(0, 0);

	loadLevel(filePath, _player);
}

void GameEngine::loadLevel(std::string &filePath, Player *p)
{
	_currLevel = new Level(IOManager::readFile(filePath), p);
}

void GameEngine::deleteCurrLevel()
{
	delete _currLevel;
}

Player * GameEngine::getPlayer()
{
	return _player;
}

GameEngine::~GameEngine()
{
}

#include <conio.h>
#include <Windows.h>

#include "GameEngine.h"
#include "Utility.h"

#define MOVE_UP 0
#define MOVE_DOWN 1
#define MOVE_LEFT 2
#define MOVE_RIGHT 3

GameEngine::GameEngine()
{
}

void GameEngine::_gameLoop()
{
	_frame = 0;
	while (_gamestate != GAMESTATE::EXIT)
	{
		while (!_currLevel->isComplete())
		{
			_currLevel->printLevelData();
			_processInput();
			_updateStatuses();


			Utility::setCursor(0, 0);
			_frame++;
		}
	}
}

void GameEngine::run()
{
	_gamestate = GAMESTATE::NORMAL;
	std::string filePath = "LevelOne.txt";
	_player = new Player(0, 0);
	_player->setCurrPos(0, 0);

	_loadLevel(filePath, _player);
	_gameLoop();
}

void GameEngine::_loadLevel(std::string &filePath, Player *p)
{
	_currLevel = new Level(Utility::readFile(filePath), p);
}

void GameEngine::_deleteCurrLevel()
{
	delete _currLevel;
}

Player * GameEngine::getPlayer()
{
	return _player;
}

void GameEngine::_processInput()
{
	char c = _getch();
	switch (c)
	{
	case 'w':
		_movePlayer(DIR::UP);
		break;
	case 'a':
		_movePlayer(DIR::LEFT);
		break;
	case 's':
		_movePlayer(DIR::DOWN);
		break;
	case 'd':
		_movePlayer(DIR::RIGHT);
		break;
	
	}
}

void GameEngine::_movePlayer(DIR dir)
{
	switch (dir)
	{
	case DIR::UP:
		if (_currLevel->getLevelData()[_player->getCurrY() - 1][_player->getCurrX()]->isEmpty())
		{
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(true);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX(), _player->getCurrY() - 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(false);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::DOWN:
		if (_currLevel->getLevelData()[_player->getCurrY() + 1][_player->getCurrX()]->isEmpty())
		{
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(true);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX(), _player->getCurrY() + 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(false);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::LEFT:
		if (_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX() - 1]->isEmpty())
		{
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(true);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX() - 1, _player->getCurrY());
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(false);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::RIGHT:
		if (_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX() + 1]->isEmpty())
		{
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(true);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX() + 1, _player->getCurrY());
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
			_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX()]->setEmpty(false);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	}
}

void GameEngine::_updateStatuses()
{
	if (_statuses.size() == 0)
		return;

	for (int i = 0; i < _statuses.size(); i++)
	{
		if (_frame - _statuses[i]->frameCreated > _statuses[i]->frameTime)
		{
			Utility::setCursor(0, _statuses[i]->position + _currLevel->getLevelData().size() + 1);
			std::cout << "                                    ";
			delete _statuses[i];
			_statuses.erase(_statuses.begin() + i);
		}
		else if(!_statuses[i]->printed)
		{
			Utility::setCursor(0, _statuses[i]->position + _currLevel->getLevelData().size() + 1);
			std::cout << _statuses[i]->message;
			_statuses[i]->printed = true;
		}
	}
}

GameEngine::~GameEngine()
{
	delete _player;
}

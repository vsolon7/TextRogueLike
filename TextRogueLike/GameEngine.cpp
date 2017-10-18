#include <conio.h>
#include <Windows.h>

#include "GameEngine.h"
#include "Utility.h"

GameEngine::GameEngine()
{
}

void GameEngine::_printLevel()
{
	std::vector< std::vector<Tile *> > tempLvl = _currLevel->getLevelData();

	for (int y = 0; y != tempLvl.size(); y++)
	{
		for (int x = 0; x != tempLvl[y].size(); x++)
		{
			std::cout << tempLvl[y][x]->getSprite();
		}
		std::cout << std::endl;
	}

	//this is for the box that holds the statuses
	std::string line(tempLvl[tempLvl.size() - 1].size(), '=');
	std::string endlines(8, '\n');
	std::cout << line << endlines << line << std::endl;
}

void GameEngine::_gameLoop()
{
	_frame = 0;
	//loop until the game has been exited
	while (_gamestate != GAMESTATE::EXIT)
	{
		//loop until the current level has been completed
		while (!_currLevel->isComplete())
		{
			_printLevel();
			_processInput();
			_updateStatuses();


			Utility::setCursor(0, 0);
			_frame++;
		}
	}
}

void GameEngine::run()
{
	//set the gamestate to normal
	_gamestate = GAMESTATE::NORMAL;
	std::string filePath = "LevelOne.txt";

	//create a new player, load the first level, and go into gameloop!
	_player = new Player(0, 0);
	_loadLevel(filePath, _player);
	_gameLoop();
}

void GameEngine::_loadLevel(std::string &filePath, Player *p)
{
	_currLevel = new Level(Utility::readFile(filePath), p);
}

void GameEngine::_deleteCurrLevel()
{
	std::vector< std::vector<Tile *> > tempLvl = _currLevel->getLevelData();

	//delete all the tiles allocated on the heap
	for (int y = 0; y < tempLvl.size(); y++)
	{
		for (int x = 0; x < tempLvl.size(); x++)
		{
			delete tempLvl[y][x];
		}
	}
	//delete the level
	delete _currLevel;
}

Player * GameEngine::getPlayer()
{
	return _player;
}

void GameEngine::_processInput()
{
	//not much to say here. finds out what key you pressed and then does something based on which button was pressed.
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
	//moves the player by:
	//
	//find out if the tile they want to move to is empty
	//set the tile they are in to EMPTY_TILE
	//set their position to the new tile they want to move to
	//set the tile they are now in to PLAYER_TILE
	//
	//if the tile is NOT empty, display a status saying they can't move there.
	switch (dir)
	{
	case DIR::UP:
		if (_currLevel->getLevelData()[_player->getCurrY() - 1][_player->getCurrX()]->isEmpty())
		{
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX(), _player->getCurrY() - 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::DOWN:
		if (_currLevel->getLevelData()[_player->getCurrY() + 1][_player->getCurrX()]->isEmpty())
		{
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX(), _player->getCurrY() + 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::LEFT:
		if (_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX() - 1]->isEmpty())
		{
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX() - 1, _player->getCurrY());
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
		}
		else
		{
			_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
		}
		break;
	case DIR::RIGHT:
		if (_currLevel->getLevelData()[_player->getCurrY()][_player->getCurrX() + 1]->isEmpty())
		{
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), EMPTY_TILE);
			_player->setCurrPos(_player->getCurrX() + 1, _player->getCurrY());
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), PLAYER_TILE);
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
	//if there are no statuses, do nothing
	if (_statuses.size() == 0)
		return;

	//loop through all the statuses
	for (int i = 0; i < _statuses.size(); i++)
	{
		//if the status has existed for its specified length
		if (_frame - _statuses[i]->frameCreated > _statuses[i]->frameTime)
		{
			//set the cursor to the beginning of the status
			Utility::setCursor(0, _statuses[i]->position + _currLevel->getLevelData().size() + 1);

			//print out a bunch of spaces to "clear" the message
			std::string spaces(_statuses[i]->message.size(), ' ');
			std::cout << spaces;
			
			//delete it (it was allocated on the heap)
			delete _statuses[i];

			//erase it from the vector
			_statuses.erase(_statuses.begin() + i);
		}
		else if(!_statuses[i]->printed)
		{
			//if the status was created but hasn't been printed to the screen yet
			//set the cursor below the screen based on the position of the status
			Utility::setCursor(0, _statuses[i]->position + _currLevel->getLevelData().size() + 1);

			//print the message and set the status to has been printed
			std::cout << _statuses[i]->message;
			_statuses[i]->printed = true;
		}
	}
}

GameEngine::~GameEngine()
{
	delete _player;
}

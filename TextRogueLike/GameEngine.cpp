#include <conio.h>
#include <Windows.h>

#include "GameEngine.h"
#include "Utility.h"

GameEngine::GameEngine()
{
}

void GameEngine::_drawBox()
{
	std::string line(BOX_WIDTH, Utility::straightHor);

	std::cout << Utility::topLeftCorn << line << Utility::topRightCorn << std::endl;

	for (int x = 0; x != BOX_HEIGHT; x++)
	{
		Utility::setCursor(0, x + 1);
		std::cout << Utility::straightVert;
		Utility::setCursor(BOX_WIDTH + 1, x + 1);
		std::cout << Utility::straightVert;
	}
	Utility::setCursor(0, BOX_HEIGHT + 1);
	std::cout << Utility::lineOutRight << line << Utility::lineOutLeft << std::endl;

	for (int x = 0; x != STATUS_HEIGHT; x++)
	{
		Utility::setCursor(0, x + BOX_HEIGHT + 2);
		std::cout << Utility::straightVert;
		Utility::setCursor(BOX_WIDTH + 1, x + BOX_HEIGHT + 2);
		std::cout << Utility::straightVert;
	}
	Utility::setCursor(0, BOX_HEIGHT + STATUS_HEIGHT + 2);
	std::cout << Utility::botLeftCorn << line << Utility::botRightCorn << std::endl;
}

void GameEngine::_printLevel()
{
	Utility::hideCursor();

	_drawBox();

	std::vector< std::vector<Tile *> > view = _camera.getCameraView(_currLevel);

	int vertOffSet = (BOX_HEIGHT - _camera.getViewHeight()) / 2;
	int horOffSet = (BOX_WIDTH - _camera.getViewWidth()) / 2;

	std::string line(_camera.getViewWidth(), Utility::straightHor);

	Utility::setCursor(horOffSet, vertOffSet);
	std::cout << Utility::topLeftCorn << line << Utility::topRightCorn;

	for (unsigned int y = 0; y != view.size(); y++)
	{
		Utility::setCursor(horOffSet, y + vertOffSet + 1);

		std::cout << Utility::straightVert;
		for (unsigned int x = 0; x != view[y].size(); x++)
		{
			std::cout << view[y][x]->getSprite() << ' ';
		}
		std::cout << Utility::straightVert;
		
		std::cout << std::endl;
	}

	Utility::setCursor(horOffSet, vertOffSet + _camera.getViewHeight() + 1);
	std::cout << Utility::botLeftCorn << line << Utility::botRightCorn;
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
			_updateStatuses();
			_processInput();

			Utility::setCursor(0, 0);
			//Utility::clearScreen();
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
	_camera.init(_player);
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
	for (unsigned int y = 0; y < tempLvl.size(); y++)
	{
		for (unsigned int x = 0; x < tempLvl.size(); x++)
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

	std::vector< std::vector<Tile *> > tempLvl = _currLevel->getLevelData();
	int playerX = _player->getCurrX();
	int playerY = _player->getCurrY();

	switch (dir)
	{
	case DIR::UP:
		if (tempLvl[playerY - 1][playerX]->isEmpty())
		{
			_currLevel->setTileSprite(playerX, playerY, (char)TYPE::EMPTY);
			_player->setCurrPos(playerX, playerY - 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite());
		}
		else
		{
			Tile *t = tempLvl[playerY - 1][playerX];
			switch (t->getSprite())
			{
			case (char) TYPE::LOCKED_DOOR:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You don't have the key", _statuses.size()));
				break;
			default:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
				break;
			}
		}
		break;
	case DIR::DOWN:
		if (tempLvl[playerY + 1][playerX]->isEmpty())
		{
			_currLevel->setTileSprite(playerX, playerY, (char) TYPE::EMPTY);
			_player->setCurrPos(playerX, playerY + 1);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite());
		}
		else
		{
			Tile *t = tempLvl[playerY + 1][playerX];
			switch (t->getSprite())
			{
			case (char) TYPE::LOCKED_DOOR:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You don't have the key", _statuses.size()));
				break;
			default:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
				break;
			}
		}
		break;
	case DIR::LEFT:
		if (tempLvl[playerY][playerX - 1]->isEmpty())
		{
			_currLevel->setTileSprite(playerX, playerY, (char)TYPE::EMPTY);
			_player->setCurrPos(playerX - 1, playerY);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite());
		}
		else
		{
			Tile *t = tempLvl[playerY][playerX - 1];
			switch (t->getSprite())
			{
			case (char)TYPE::LOCKED_DOOR:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You don't have the key", _statuses.size()));
				break;
			default:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
				break;
			}
		}
		break;
	case DIR::RIGHT:
		if (tempLvl[playerY][playerX + 1]->isEmpty())
		{
			_currLevel->setTileSprite(playerX, playerY, (char)TYPE::EMPTY);
			_player->setCurrPos(playerX + 1, playerY);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite());
		}
		else
		{
			Tile *t = tempLvl[playerY][playerX + 1];
			switch (t->getSprite())
			{
			case (char)TYPE::LOCKED_DOOR:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You don't have the key", _statuses.size()));
				break;
			default:
				_statuses.push_back(new StatusInfo(STATUSTYPE::INFO, _frame, "You can't move there!", _statuses.size()));
				break;
			}
		}
		break;
	}
}

void GameEngine::_updateStatuses()
{
	//if there are no statuses, do nothing
	if (_statuses.size() == 0)
		return;

	//if the status has existed for its specified length
	if (_statuses.size() > 7)
	{
		//set the cursor to the beginning of the status
		Utility::setCursor(1, _statuses[0]->position + BOX_HEIGHT + 2);

		//print out a bunch of spaces to "clear" the message
		std::string spaces(BOX_WIDTH, ' ');
		std::cout << spaces;

		//delete it (it was allocated on the heap)
		delete _statuses[0];

		//erase it from the vector
		_statuses.erase(_statuses.begin());


		for (int i = 0; i < _statuses.size(); i++)
			_statuses[i]->position--;
	}

	//loop through all the statuses
	for (unsigned int i = 0; i < _statuses.size(); i++)
	{
		//if the status was created but hasn't been printed to the screen yet
		//set the cursor to the side of the screen based on the position of the status
		Utility::setCursor(1, _statuses[i]->position + BOX_HEIGHT + 2);

		std::string extraBuffer(BOX_WIDTH - _statuses[i]->message.size(), ' ');

		//print the message and set the status to has been printed
		std::cout << _statuses[i]->message << extraBuffer;
		_statuses[i]->printed = true;
	}
}

GameEngine::~GameEngine()
{
	delete _player;
}

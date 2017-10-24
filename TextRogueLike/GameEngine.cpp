#include <conio.h>
#include <Windows.h>
#include <time.h>
#include <iomanip>

#include "GameEngine.h"
#include "Utility.h"

GameEngine::GameEngine()
{
}

//these two functions print the level to the screen
void GameEngine::_drawBox()
{
	//create some lines of standard sizes
	std::string line(BOX_WIDTH, Utility::straightHor);
	std::string hpLine(HP_WIDTH, Utility::straightHor);

	//print top of the box
	std::cout << Utility::topLeftCorn << line << Utility::lineOutBot << hpLine << Utility::topRightCorn << std::endl;

	for (int x = 0; x != BOX_HEIGHT; x++)
	{

		//draw HP BOX

		if (x == 6)
		{
			std::cout << "      INVENTORY";
		}

		if (x % 4 == 0 && x > 7)
		{
			std::cout << "  +   +   +   +   +  ";
		}

		if (x == BOX_HEIGHT - 3)
		{
			std::cout << hpLine;
		}

		if (x == BOX_HEIGHT - 2)
		{
			std::cout << "      EQUIPPED";
		}

		Utility::setCursor(BOX_WIDTH + HP_WIDTH + 2, x + 1);
		std::cout << Utility::straightVert;

		if (x == HP_HEIGHT + 1)
		{
			Utility::setCursor(BOX_WIDTH + 1, x);
			std::cout << Utility::lineOutRight << hpLine << Utility::lineOutLeft;
		}

		//draw the regular box
		Utility::setCursor(0, x + 1);
		std::cout << Utility::straightVert;
		Utility::setCursor(BOX_WIDTH + 1, x + 1);
		std::cout << Utility::straightVert;
	}
	Utility::setCursor(0, BOX_HEIGHT + 1);
	std::cout << Utility::lineOutRight << line << Utility::lineOutAll << hpLine << Utility::botRightCorn << std::endl;

	//draw the status box
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
	//don't show the cursor
	Utility::hideCursor();

	_drawBox();

	//get the cameras view to draw
	std::vector< std::vector<Tile *> > view = _camera.getCameraView(_currLevel, _currCameraEffects);

	//offsets to center it
	int vertOffSet = (BOX_HEIGHT - _camera.getViewHeight()) / 2;
	int horOffSet = (BOX_WIDTH - _camera.getViewWidth()) / 2;

	//a line the width of the camera, its standard this way and based off your vision radius
	std::string line(_camera.getViewWidth(), Utility::straightHor);

	Utility::setCursor(horOffSet, vertOffSet);
	std::cout << Utility::topLeftCorn << line << Utility::topRightCorn;

	//draw Level
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

	//print out some players stats
	Utility::setCursor(BOX_WIDTH + 2, 1);
	std::cout << " HP: " << _player->getCurrHP() << " / " << _player->getMaxHP() << "    ";
	Utility::setCursor(BOX_WIDTH + 2, 2);
	std::cout << " DAMAGE: " << _player->getDamage();
	Utility::setCursor(BOX_WIDTH + 2, 3);
	std::cout << " ARMOR: " << _player->getArmor();
	Utility::setCursor(BOX_WIDTH + 2, 4);
	std::cout << " DMG REDUC: " << std::setprecision(3) << 100 * _player->getDamageReduc() << "%";

	Utility::setCursor(horOffSet, vertOffSet + _camera.getViewHeight() + 1);
	std::cout << Utility::botLeftCorn << line << Utility::botRightCorn;

	//print player inventory
	std::vector<std::vector<Item *>> tempInv = _player->inventory;

	for (int y = 0; y < tempInv.size(); y++)
	{
		for (int x = 0; x < tempInv[y].size(); x++)
		{
			Utility::setCursor(BOX_WIDTH + 6 + (x * 4), y * 4 + 10);

			if(tempInv[y][x] != nullptr)
				std::cout << tempInv[y][x]->sprite;
		}
	}
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
			_updateEnemies();
			_processInput();

			Utility::setCursor(0, 0);
			_frame++;
		}
	}
}

void GameEngine::run()
{
	Utility::randEngine.seed((unsigned int) time(nullptr));

	//set the gamestate to normal
	_gamestate = GAMESTATE::NORMAL;
	std::string filePath = "LevelOne.txt";

	//create a new player, load the first level, and go into gameloop!
	_player = new Player(0, 0);

	//intro is here to properly set the players sprite
	//_intro();

	_loadLevel(filePath, _enemies);

	//_loadLevel(filePath, _enemies);
	_currCameraEffects = EFFECTS::NONE;
	_camera.init(_player);

	_gameLoop();
}

void GameEngine::_loadLevel(std::string &filePath, LinkedList<Enemy *> &e)
{
	_currLevel = new Level(Utility::readFile(filePath), _player, e);
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

void GameEngine::_deleteEnemies()
{
	//delete all the enemies in a level to avoid memory leaks, this will happen when loading a new level
	for (LLNode<Enemy *> *it = _enemies.getBeg(); it->nextNode != nullptr; it = it->nextNode)
	{
		delete it->data;
		delete it;
	}
}

void GameEngine::_updateEnemies()
{
	int pos = 0;

	LLNode<Enemy *> *it = _enemies.getBeg();

	//loop thru all the enemies, check if it is dead, if it is delete it to prevent memory leak
	//if not, then move it!
	while (it->nextNode != nullptr)
	{
		if (it->data->getCurrHP() < 0)
		{
			_currLevel->setTileSprite(it->data->getCurrX(), it->data->getCurrY(), (char)TILE::EMPTY, TYPE::EMPTY);
			delete it->data;
			it = it->nextNode;
			_enemies.deleteNode(pos);
			pos++;
		}
		else
		{
			it->data->idleMove(_currLevel, _player, _statuses);
			it = it->nextNode;
		}
		pos++;
	}

	//don't forget the last node in the linked list!
	//basically, just do the same thing one more time 
	if (it->data->getCurrHP() < 0)
	{
		_currLevel->setTileSprite(it->data->getCurrX(), it->data->getCurrY(), (char)TILE::EMPTY, TYPE::EMPTY);
		delete it->data;
		it = it->nextNode;
		_enemies.deleteNode(pos);
	}
	else
	{
		it->data->idleMove(_currLevel, _player, _statuses);
	}
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
	case 'p':
		_pauseGame();
		break;
	case 'i':
		_inventorySelection();
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
	//if the tile is NOT empty, display a status based on what's there.

	std::vector< std::vector<Tile *> > tempLvl = _currLevel->getLevelData();
	int playerX = _player->getCurrX();
	int playerY = _player->getCurrY();
	int playerMoveX = 0;
	int playerMoveY = 0;

	switch (dir)
	{
	case DIR::UP:
		playerMoveX = 0;
		playerMoveY = -1;
		break;
	case DIR::DOWN:
		playerMoveX = 0;
		playerMoveY = 1;
		break;
	case DIR::LEFT:
		playerMoveX = -1;
		playerMoveY = 0;
		break;
	case DIR::RIGHT:
		playerMoveX = 1;
		playerMoveY = 0;
		break;
	}

	if (tempLvl[playerY + playerMoveY][playerX + playerMoveX]->isEmpty())
	{
		_currLevel->setTileSprite(playerX, playerY, (char)TILE::EMPTY, TYPE::EMPTY);
		_player->setCurrPos(playerX + playerMoveX, playerY + playerMoveY);
		_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite(), TYPE::PLAYER);
	}
	else
	{
		Tile *t = tempLvl[playerY + playerMoveY][playerX + playerMoveX];
		switch (t->getType())
		{
		case TYPE::LOCKED_DOOR:
			_statuses.pushBack(new StatusInfo(STATUSTYPE::INFO, "You don't have the key", _statuses.size()));
			break;
		case TYPE::DOOR:
			_statuses.pushBack(new StatusInfo(STATUSTYPE::INFO, "You open the door", _statuses.size()));

			_currLevel->setTileSprite(playerX, playerY, (char)TILE::EMPTY, TYPE::EMPTY);
			_player->setCurrPos(playerX + playerMoveX, playerY + playerMoveY);
			_currLevel->setTileSprite(_player->getCurrX(), _player->getCurrY(), _player->getSprite(), TYPE::PLAYER);

			break;
		case TYPE::ENEMY:
			Enemy *e = t->getEnemyOnTile();
			double tentDamage = _player->getDamage() * (1 - e->getDamageReduc());
			
			int intDamage = (int) std::round(tentDamage);

			e->increaseCurrHP(-intDamage);

			_statuses.pushBack(new StatusInfo(STATUSTYPE::INFO, "You attack for " + std::to_string(intDamage) + " damage", _statuses.size()));
			break;
		}
	}
}

void GameEngine::_updateStatuses()
{
	//once there are 8 statuses, we start deleting the oldest ones!

	//if there are no statuses, do nothing
	if (_statuses.size() == 0)
		return;

	LLNode<StatusInfo *> *it = _statuses.getBeg();
	
	if (_statuses.size() > 7)
	{
		//this is needed so if you get a huge flood of them, there will always only be 7.
		//O(n^2) tho :(, however the second for loop just shifts a position down by one, not that computationally taxing
		while (it->nextNode != nullptr)
		{
			if (_statuses.size() <= 7)
				break;

			//set the cursor to the beginning of the status
			Utility::setCursor(1, _statuses.getBeg()->data->position + BOX_HEIGHT + 2);

			//print out a bunch of spaces to "clear" the message
			std::string spaces(BOX_WIDTH, ' ');
			std::cout << spaces;

			//delete the statusinfo data (it was allocated on the heap)
			delete _statuses.getBeg()->data;

			//erase it from the LL
			_statuses.deleteNode(0);

			LLNode<StatusInfo *> *it2 = _statuses.getBeg();
			while (it2->nextNode != nullptr)
			{
				it2->data->position--;
				it2 = it2->nextNode;
			}
			it2->data->position--;
		}
	}

	it = _statuses.getBeg();

	//print the node
	while (it->nextNode != nullptr)
	{
		Utility::setCursor(1, it->data->position + BOX_HEIGHT + 2);
		std::string extraBuffer(BOX_WIDTH - it->data->message.size(), ' ');
		std::cout << it->data->message << extraBuffer;
		it = it->nextNode;
	}

	//don't forget the last node in the linked list!
	Utility::setCursor(1, it->data->position + BOX_HEIGHT + 2);
	std::string extraBuffer(BOX_WIDTH - it->data->message.size(), ' ');
	std::cout << it->data->message << extraBuffer;
}

void GameEngine::_pauseGame()
{
	_gamestate = GAMESTATE::PAUSE;

	Utility::clearScreen();
	std::cout << "Paused";

	char temp;

	do
	{
		temp = _getch();
	} while (temp != 'p');

	_gamestate = GAMESTATE::NORMAL;
}

void GameEngine::_inventorySelection()
{
	bool exit = false;

	int posX = 0;
	int posY = 0;
	int prevX = 0;
	int prevY = 0;

	Utility::setCursor(BOX_WIDTH + 6 + (posX * 4), posY * 4 + 12);
	std::cout << "^";

	while (!exit)
	{
		char c = _getch();

		switch (c)
		{
		case 'w':
			if (posY > 0)
			{
				prevY = posY;
				prevX = posX;
				posY--;
			}
			break;
		case 'a':
			if (posX > 0)
			{
				prevX = posX;
				prevY = posY;
				posX--;
			}
			break;
		case 's':
			if (posY < 3)
			{
				prevY = posY;
				prevX = posX;
				posY++;
			}
			break;
		case 'd':
			if (posX < 3)
			{
				prevX = posX;
				prevY = posY;
				posX++;
			}
			break;
		case '\\':
		{
			Utility::clearScreen();
			Item *tempItem = _player->inventory[posY][posX];

			std::cout << "\tItem Name:: \"" << tempItem->name << "\"\n\n";
			printf_s("\tDamage:: %d\n\tArmor::  %d\n\tHP::     %d\n", tempItem->damageIncrease, tempItem->armorIncrease, tempItem->hpIncrease);
			_getch();
		}
			break;
		case 'i':
			exit = true;
			break;
		}
		//clear the ^ from the last move
		Utility::setCursor(BOX_WIDTH + 6 + (prevX * 4), (prevY * 4) + 12);
		std::cout << " ";

		Utility::setCursor(BOX_WIDTH + 6 + (posX * 4), (posY * 4) + 12);
		std::cout << "^";
	}
}

void GameEngine::_intro()
{
	Utility::hideCursor();
	Utility::printDelayed("\tWelcome to my ASCII Roguelike game!\n\n");

	Utility::printDelayed("\n\n\n\tTo begin with, pick the sprite for your character!(enter the number, please)\n\n");
	std::cout << "\t1. " << (char)233 << "\n";
	std::cout << "\t2. " << "@" << "\n";
	std::cout << "\t3. " << "Enter custom sprite" << "\n\n";
	std::cout << "\t>> ";

	int choice;
	std::cin >> choice;

	switch (choice)
	{
	case 1:
		
		break;
	case 2:
		_player->setSprite('@');
		break;
	case 3:
		Utility::clearScreen();
		Utility::setTextColor(TEXTCOLOR::RED);
		std::cout << "\tKeep in mind you may have the same sprite as other things in-game, which may get confusing\n\n";
		Utility::setTextColor(TEXTCOLOR::WHITE);
		std::cout << "Enter a character for your sprite\n\n";
		std::cout << ">> ";

		char choice;
		std::cin >> choice;

		_player->setSprite(choice);
		break;
	}
	Utility::clearScreen();
}

GameEngine::~GameEngine()
{
	delete _player;
}
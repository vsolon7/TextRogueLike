#pragma once
#include <vector>
#include <string>

#include "Level.h"
#include "Player.h"
#include "StatusInfo.h"

enum class GAMESTATE
{
	EXIT, PAUSE, INVENTORY, NORMAL
};

enum class DIR
{
	UP, DOWN, LEFT, RIGHT
};

class GameEngine
{
public:
	GameEngine();

	//call this function to start the game!
	void run();

	//returns the player
	Player * getPlayer();


	~GameEngine();
private:
	//the level we are currently on
	Level *_currLevel;

	//the player
	Player *_player;

	//the current gamestate of the game
	GAMESTATE _gamestate;

	//statuses are little messages that pop up below the game that will say info.
	std::vector<StatusInfo *> _statuses;

	//the "frame" we are on. more like the turn. the length statuses exist is based off of this.
	int _frame;

	//the main gameloop!
	void _gameLoop();

	//load a level into the game, takes the filepath and the player
	void _loadLevel(std::string &filePath, Player *p);

	//deletes the level and all it's tiles allocated on the heap
	void _deleteCurrLevel();
	
	//processes the keyboard input
	void _processInput();

	//moves the player in a direction.
	void _movePlayer(DIR dir);

	//updates the "statuses" at the bottom of the screen
	void _updateStatuses();

	//prints the level to the screen!
	void _printLevel();
};


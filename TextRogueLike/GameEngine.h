#pragma once
#include <vector>
#include <string>

#include "Snake.h"
#include "Level.h"
#include "Snake.h"
#include "Player.h"
#include "StatusInfo.h"
#include "Camera.h"

#define BOX_WIDTH 60
#define BOX_HEIGHT 28
#define HP_WIDTH 21
#define HP_HEIGHT 4
#define STATUS_HEIGHT 7

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

	~GameEngine();
private:
	//the level we are currently on
	Level *_currLevel;

	//the player
	Player *_player;

	LinkedList<Enemy *> _enemies;

	//the current gamestate of the game
	GAMESTATE _gamestate;

	//the camera!
	Camera _camera;

	//statuses are little messages that pop up below the game that will say info.
	LinkedList<StatusInfo *> _statuses;

	//the "frame" we are on. more like the turn. the length statuses exist is based off of this.
	int _frame;

	EFFECTS _currCameraEffects;


	
	//draws a box for the game
	void _drawBox();

	//the main gameloop!
	void _gameLoop();

	//load a level into the game, takes the filepath and the player
	void _loadLevel(std::string &filePath, LinkedList<Enemy *> &e);

	//deletes the level and all it's tiles allocated on the heap
	void _deleteCurrLevel();

	void _deleteEnemies();

	//loops through the linked list of enemies and makes them move or attack
	void _updateEnemies();
	
	//processes the keyboard input
	void _processInput();

	//moves the player in a direction.
	void _movePlayer(DIR dir);

	//updates the "statuses" at the bottom of the screen
	void _updateStatuses();

	//prints the level to the screen!
	void _printLevel();

	//pauses the game. I dunno why you'd do this
	void _pauseGame();

	//lets you pick an item from your inventory
	void _inventorySelection();

	//do an introduction to the game!
	void _intro();
};


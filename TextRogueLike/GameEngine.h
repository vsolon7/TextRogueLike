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

	void run();
	Player * getPlayer();


	~GameEngine();
private:
	Level *_currLevel;
	Player *_player;
	GAMESTATE _gamestate;
	std::vector<StatusInfo *> _statuses;
	int _frame;

	void _gameLoop();
	void _loadLevel(std::string &filePath, Player *p);
	void _deleteCurrLevel();
	void _processInput();
	void _movePlayer(DIR dir);
	void _updateStatuses();
};


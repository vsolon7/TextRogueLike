#pragma once

#include <string>

enum class STATUSTYPE
{
	INFO, BATTLE, EVENT
};

struct StatusInfo
{
	StatusInfo::StatusInfo(STATUSTYPE t, int frame, std::string m, int pos)
	{
		//sets a bunch of variables
		frameCreated = frame;
		message = m;
		type = t;
		printed = false;
		position = pos;

		//the type of status determines how long it stays. needs more testing
		switch (type)
		{
		case STATUSTYPE::INFO:
			frameTime = 5;
			break;
		case STATUSTYPE::EVENT:
			frameTime = 5;
			break;
		case STATUSTYPE::BATTLE:
			frameTime = 3;
			break;
		default:
			frameTime = 5;
			break;
		}
	}

	std::string message;
	STATUSTYPE type;
	int frameCreated;
	int frameTime;
	int position;
	bool printed;
};
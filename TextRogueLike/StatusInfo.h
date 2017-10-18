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
		message = m;
		type = t;
		printed = false;
		position = pos;
	}

	std::string message;
	STATUSTYPE type;
	int position;
	bool printed;
};
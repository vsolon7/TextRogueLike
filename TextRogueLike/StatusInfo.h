#pragma once

#include <string>

enum class STATUSTYPE
{
	INFO, BATTLE, EVENT
};

struct StatusInfo
{
	StatusInfo::StatusInfo(STATUSTYPE t, std::string m, int pos)
	{
		//sets a bunch of variables
		message = m;
		type = t;
		position = pos;
	}

	std::string message;
	STATUSTYPE type;
	int position;
};
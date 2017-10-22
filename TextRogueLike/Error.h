#pragma once

#include <string>

//just creates an error message.
struct Error
{
	Error(std::string error)
	{
		_message = error;
	}
	std::string Error::what()
	{
		return _message;
	}
private:
	std::string _message;
};
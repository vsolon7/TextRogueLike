#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace Utility
{
	//reads a level and returns the vector of strings!
	static std::vector<std::string> readFile(std::string &fileName)
	{
		std::ifstream file(fileName);

		if (file.fail())
		{
			std::cout << "error opening file" << std::endl;
			exit(69);
		}

		std::string buffer;
		std::vector<std::string> fileData;

		while (getline(file, buffer))
		{
			fileData.push_back(buffer);
		}

		file.close();
		return fileData;
	}

	//sets the console cursor to any position on the screen
	static void setCursor(int x, int y)
	{
		HANDLE hOut;
		COORD Position;

		hOut = GetStdHandle(STD_OUTPUT_HANDLE);

		Position.X = x;
		Position.Y = y;
		SetConsoleCursorPosition(hOut, Position);
	}
}
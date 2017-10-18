#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <Windows.h>

/* Standard error macro for reporting API errors */
#define PERR(bSuccess, api){if(!(bSuccess)) printf("%s:Error %d from %s \ on line %d\n", __FILE__, GetLastError(), api, __LINE__);}

namespace Utility
{
	static const char straightHor = 205;
	static const char straightVert = 186;
	static const char topLeftCorn = 201;
	static const char topRightCorn = 187;
	static const char botLeftCorn = 200;
	static const char botRightCorn = 188;
	static const char lineOutLeft = 185;
	static const char lineOutRight = 204;

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

	static void hideCursor()
	{
		HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO info;
		info.dwSize = 100;
		info.bVisible = FALSE;
		SetConsoleCursorInfo(consoleHandle, &info);
	}

	static void printCodePage()
	{
		for (int i = 0; i < 256; i++)
		{
			std::cout << i << ": " << (char)i << "\n";
		}
	}
}
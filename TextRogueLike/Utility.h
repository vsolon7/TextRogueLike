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

	static void clearScreen()
	{
		HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
		COORD coordScreen = { 0, 0 };    /* here's where we'll home the
											cursor */
		BOOL bSuccess;
		DWORD cCharsWritten;
		CONSOLE_SCREEN_BUFFER_INFO csbi; /* to get buffer info */
		DWORD dwConSize;                 /* number of character cells in
											the current buffer */

											/* get the number of character cells in the current buffer */

		bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
		PERR(bSuccess, "GetConsoleScreenBufferInfo");
		dwConSize = csbi.dwSize.X * csbi.dwSize.Y;

		/* fill the entire screen with blanks */

		bSuccess = FillConsoleOutputCharacter(hConsole, (TCHAR) ' ',
			dwConSize, coordScreen, &cCharsWritten);
		PERR(bSuccess, "FillConsoleOutputCharacter");

		/* get the current text attribute */

		bSuccess = GetConsoleScreenBufferInfo(hConsole, &csbi);
		PERR(bSuccess, "ConsoleScreenBufferInfo");

		/* now set the buffer's attributes accordingly */

		bSuccess = FillConsoleOutputAttribute(hConsole, csbi.wAttributes,
			dwConSize, coordScreen, &cCharsWritten);
		PERR(bSuccess, "FillConsoleOutputAttribute");

		/* put the cursor at (0, 0) */

		bSuccess = SetConsoleCursorPosition(hConsole, coordScreen);
		PERR(bSuccess, "SetConsoleCursorPosition");
		return;
	}
}
#pragma once
#include <fstream>
#include <vector>
#include <string>
#include <iostream>

namespace IOManager
{
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
}
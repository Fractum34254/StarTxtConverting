#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include "Starclass.h"

void LoadFile(const std::string& name, std::vector<std::string>& vector)
{
	std::fstream file(name);

	for (std::string line; std::getline(file, line);)
	{
		if (!line.empty())
		{
			vector.push_back(line);
		}
	}
}


int main()
{
	std::vector<std::string> lines;

	LoadFile("sternenliste.txt", lines);

	std::cin.get();
	return 0;
}
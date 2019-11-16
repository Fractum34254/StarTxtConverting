#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Star.h"

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

void Replace(std::string& string, std::string old, std::string next)
{
	size_t pos = string.find_first_of(old);
	for (size_t pos = string.find_first_of(old); pos != std::string::npos; pos = string.find_first_of(old))
	{
		string.replace(pos, old.size(), next);
	}
}


int main()
{
	std::vector<std::string> lines;

	LoadFile("sternenliste.txt", lines);

	std::vector<Star> stars;

	for (size_t i = 0; i < lines.size(); )
	{
		const std::string firstLine = lines.at(i++);
		const std::string secondLine = lines.at(i++);

		stars.push_back(Star(firstLine, secondLine));
	}

	std::cout << "non-marked: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return !s.IsMarked(); }) << std::endl;
	std::cout << "non-star-like: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return !s.IsStar(); }) << std::endl;
	std::cout << "amount: " << stars.size() << std::endl;


	std::cin.get();
	return 0;
}
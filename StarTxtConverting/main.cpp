#include <vector>
#include <fstream>
#include <string>
#include <iostream>
#include <algorithm>
#include "Star.h"
#include "Layouter.h"

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

	std::cout << "correctly loaded: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return !s.IsMarked(); }) << " of " << stars.size() << std::endl;
	std::cout << "stars: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::Startype); }) << std::endl;
	std::cout << "brown dwarfes: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::BrownDwarf); }) << std::endl;
	std::cout << "red giants: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::RedGiant); }) << std::endl;
	std::cout << "white dwarfes: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::WhiteDwarf); }) << std::endl;
	std::cout << "planets: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::Planet); }) << std::endl;
	std::cout << "belts: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::Belt); }) << std::endl;
	std::cout << "unknowns: " << std::count_if(stars.begin(), stars.end(), [](const Star& s) {return (s.GetType() == Star::type::Undefined); }) << std::endl;

	std::vector<std::string> outputLines;
	for (size_t i = 0; i < stars.size(); i++)
	{
		outputLines.push_back(Layouter::Layout(stars.at(i)));
	}

	std::cin.get();
	return 0;
}
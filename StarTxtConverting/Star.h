#pragma once
#include <string>
#include <unordered_map>
#include "Starclass.h"
#include "StarCoordinates.h"

class Star
{
public:
	Star(std::string firstLine, std::string secondLine)
	{
		std::string information;
		int tabNum = 0;

		try
		{
			//first line
			for (int i = 0; i < firstLine.size(); i++)
			{
				if (firstLine.at(i) == '\t')
				{
					size_t space;
					std::string unknown = "";
					unknown.push_back(-105);
					switch (tabNum)
					{
					case 1:
						distance = std::stod(information);
						break;
					case 2:
						common_system = information;
						break;
					case 3:
						common_name = information;
						break;
					case 4:
						starclass = Starclass(information);
						break;
					case 5:
						if (information == unknown || information.empty())
						{
							radius = 0.0;
						}
						else
						{
							radius = std::stod(information);
						}
						break;
					case 6:
						if (information == unknown || information.empty())
						{
							mass = 0.0;
						}
						else
						{
							mass = std::stod(information);
						}
						break;
					case 7:
						if (information == unknown || information.empty())
						{
							appMag = -100.0;
						}
						else if (information.front() == '?')
						{
							appMag = std::stod(information.substr(1, information.size()-1));
							appMag *= -1.0;
						}
						else if (information.back() == 'J')
						{
							appMag = std::stod(information.substr(0, information.size() - 3));
							brownDwarf = true;
						}
						else
						{
							appMag = std::stod(information);
						}
						break;
					case 8:
						if (information == unknown || information.empty())
						{
							absMag = -1.0;
						}
						else
						{
							absMag = std::stod(information);
						}
						break;
					case 9:
						a = RightAscension(information);
						break;
					case 10:
						if (information == "?")
						{
							parallax = 0.0;
						}
						else
						{
							space = information.find_first_of(' ');
							parallax = std::stod(information.substr(0, space - 1));
						}
						break;
					default:
						break;
					}
					tabNum++;
					information = "";
				}
				else
				{
					information.push_back(firstLine.at(i));
				}
			}
			constellation = information;

			//reset
			information = "";
			tabNum = 0;

			//second line
			for (int i = 0; i < secondLine.size(); i++)
			{
				if (secondLine.at(i) == '\t')
				{
					switch (tabNum)
					{
					case 2:
						second_system = information;
						break;
					case 3:
						second_name = information;
						break;
					case 9:
						d = Declination(information);
						break;
					default:
						break;
					}
					tabNum++;
					information = "";
				}
				else
				{
					information.push_back(secondLine.at(i));
				}
			}
			if (constellation.back() == '-')
			{
				constellation.pop_back();
			}
			else
			{
				constellation += " ";
			}
			constellation += information;
		}
		catch (const std::exception& e)
		{
			marked = true;
			std::cout << e.what() << " at tab stop nr. " << tabNum << std::endl;
		}
	}
	bool IsMarked() const
	{
		return marked;
	}
	bool IsStar() const
	{
		return starclass.IsStar();
	}
private:
	bool marked = false;
	bool brownDwarf = false;
	double distance;			///lightyears
	std::string common_system;
	std::string second_system;
	std::string common_name;
	std::string second_name;
	Starclass starclass;		///only main and first-order subclasses
	double radius;				///multiple of sun radius
	double mass;				///multiple of sun mass
	double appMag;				///apparent magnitude
	double absMag;				///absolute magnitude
	RightAscension a;
	Declination d;
	double parallax;			///in arcsec
	std::string constellation;
};

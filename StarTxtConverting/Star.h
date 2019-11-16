#pragma once
#include <string>
#include <unordered_map>
#include "Starclass.h"
#include "StarCoordinates.h"

class Star
{
public:
	enum type
	{
		Startype,
		WhiteDwarf,
		BrownDwarf,
		RedGiant,
		Belt,
		Planet,
		Undefined
	};
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
							startype = type::BrownDwarf;
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
		
		DefineType();
	}
	bool IsMarked() const
	{
		return marked;
	}
	type GetType() const
	{
		return startype;
	}
	std::string GetSystem() const
	{
		if (second_system != "")
		{
			return (common_system + " " + second_system);
		}
		else
		{
			return common_system;
		}
	}
	std::string GetName() const
	{
		if (second_name != "")
		{
			return (common_name + " " + second_name);
		}
		else
		{
			return common_name;
		}
	}
	std::string GetDistance() const
	{
		const std::string d = std::to_string(distance);
		return d.substr(0, 6);
	}
	std::string GetMainStarClass() const
	{
		return starclass.GetMainClass();
	}
	std::string GetSubStarclass() const
	{
		const float s = starclass.GetSubClass();
		if (s == -1.0f)
		{
			return "";
		}
		else
		{
			return std::to_string(s).substr(0, 3);
		}
	}
	std::string GetRadius() const
	{
		if (radius == 0.0)
		{
			return "";
		}
		else
		{
			const std::string r = std::to_string(radius);
			return r.substr(0, 7);
		}
	}
	std::string GetMass() const
	{
		if (mass == 0.0)
		{
			return "";
		}
		else
		{
			const std::string m = std::to_string(mass);
			return m.substr(0, 7);
		}
	}
	std::string GetAppMag() const
	{
		if (appMag == -100.0)
		{
			return "";
		}
		else
		{
			const std::string am = std::to_string(appMag);
			return am.substr(0, 4);
		}
	}
	std::string GetAbsMag() const
	{
		if (absMag == -1.0)
		{
			return "";
		}
		else
		{
			const std::string am = std::to_string(absMag);
			return am.substr(0, 4);
		}
	}
	std::string GetRightAscension(const std::string& fill) const
	{
		return (std::to_string(a.GetHours()) + fill + std::to_string(a.GetMinutes()) + fill + std::to_string(a.GetSeconds()));
	}
	std::string GetDeclination(const std::string& fill) const
	{
		return ((d.GetNegative() ? "-" : "+") + fill + std::to_string(d.GetDegrees()) + fill + std::to_string(d.GetMinutes()) + fill + std::to_string(d.GetSeconds()));
	}
	std::string GetParallax() const
	{
		if (parallax == 0.0)
		{
			return "";
		}
		else
		{
			return std::to_string(parallax).substr(0, 6);
		}
	}
	std::string GetConstellation() const
	{
		return constellation;
	}
	std::string GetStarType() const
	{
		std::string t;
		switch (GetType())
		{
		case type::Belt:
			t = "Gürtel";
			break;
		case type::BrownDwarf:
			t = "Brauner Zwerg";
			break;
		case type::Planet:
			t = "Planet";
			break;
		case type::RedGiant:
			t = "Roter Riese";
			break;
		case type::Startype:
			t = "Stern";
			break;
		case type::WhiteDwarf:
			t = "Weißer Zwerg";
			break;
		case type::Undefined:
			t = "Unbekannt";
			break;
		}
		return t;
	}
private:
	void DefineType()
	{
		if (startype == type::Undefined)
		{
			const std::string classStars = "OBAFGKM";
			const std::string classBrownDwarfes = "LTY";
			const std::string classRedGiants = "RNS";
			const std::string classWhiteDwarfes = "D";

			const std::string main_class = starclass.GetMainClass();
			if (classStars.find(main_class) != std::string::npos)
			{
				startype = type::Startype;
			}
			else if (classBrownDwarfes.find(main_class) != std::string::npos)
			{
				startype = type::BrownDwarf;
			}
			else if (classRedGiants.find(main_class) != std::string::npos)
			{
				startype = type::RedGiant;
			}
			else if (classWhiteDwarfes.find(main_class.front()) != std::string::npos)
			{
				startype = type::WhiteDwarf;
			}
			else if (main_class == "Planet")
			{
				startype = type::Planet;
			}
			else if (main_class == "Belt")
			{
				startype = type::Belt;
			}
		}
	}
	bool marked = false;
	type startype = type::Undefined;
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

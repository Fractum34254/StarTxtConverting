#pragma once
#include "Util.h"
#include <string>
#include <iostream>
#include <vector>

class Starclass
{
public:
	Starclass()
		:
		main_class("Standard"),
		sub_class(-1.0f)
	{}
	Starclass(std::string starclass)
	{
		const int firstDigit = Util::PositionOfFirstDigit(starclass);
		const int lastDigit = Util::PositionOfLastDigit(starclass);


		//if there are digits
		if (firstDigit != starclass.size())
		{
			std::string sub_classification;

			for (int i = 0; i < firstDigit; i++)
			{
				main_class.push_back(starclass.at(i));
			}
			for (int i = firstDigit; i <= lastDigit; i++)
			{
				sub_classification.push_back(starclass.at(i));
			}
			sub_class = std::stof(sub_classification);
		}
		else //no digits
		{
			///Planet?
			if ((starclass.find("Planet") != std::string::npos) || (starclass.find("Gürtel") != std::string::npos))
			{
				main_class = "non-star";
				sub_class = -1.0f;
				isStar = false;
				return;
			}
			///Question mark?
			const size_t mark = starclass.find("?");
			if (mark != std::string::npos)
			{
				for (unsigned int i = 0; i < mark; i++)
				{
					main_class.push_back(starclass.at(i));
				}
				sub_class = 5.0f;
				return;
			}
			///Fail, unknown layout
			std::cout << "Unknown Starclass layout: " << starclass << std::endl;
		}
	}
	bool IsStar() const
	{
		return isStar;
	}
private:
	std::string main_class;
	float sub_class;
	bool isStar = true;
};
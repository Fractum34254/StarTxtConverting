#pragma once
#include <string>

class RightAscension
{
public:
	RightAscension() 
		:
		hours(-1),
		minutes(-1),
		seconds(-1)
	{}
	RightAscension(std::string input)
	{
		// layout description:
		///0|1:		digits (hour)
		///2:		h
		///3:		-96 (space)
		///4|5:		digits (minute)
		///6:		m
		///7:		-96 (space)
		///8|9:	digits (seconds)
		///10:		s

		hours = std::stoi(input.substr(0, 2));
		minutes = std::stoi(input.substr(4, 2));
		seconds = std::stoi(input.substr(8, 2));
	}
private:
	int hours;
	int minutes;
	int seconds;
};

class Declination
{
public:
	Declination()
		:
		negative(false),
		degrees(-1),
		minutes(-1),
		seconds(-1)
	{}
	Declination(std::string input)
	{
		// layout description:
		///0:		+/- (degrees)
		///1|2:		digits (degrees)
		///3:		°
		///4:		-96 (space)
		///5|6:		digits (minutes)
		///7:		'
		///8:		-96 (space)
		///9|10:	digits (seconds)
		///11:		"
		///12:		-96 (space)

		negative = (input.at(0) == '-');
		degrees = std::stoi(input.substr(1, 2));
		minutes = std::stoi(input.substr(5, 2));
		seconds = std::stoi(input.substr(9, 2));
	}
private:
	bool negative;
	int degrees;
	int minutes;
	int seconds;
};
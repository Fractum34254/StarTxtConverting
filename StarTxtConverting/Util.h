#pragma once
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>

struct Util
{
	static int PositionOfFirstDigit(std::string string)
	{
		for (unsigned int i = 0; i < string.size(); i++)
		{
			if (std::isdigit(static_cast<unsigned char>(string.at(i))))
			{
				return i;
			}
		}
		return string.size();
	}
	static int PositionOfLastDigit(std::string string)
	{
		for (int i = (int)string.size()-1; i >= 0; i--)
		{
			if (std::isdigit(static_cast<unsigned char>(string.at(i))))
			{
				return i;
			}
		}
		return string.size();
	}
};

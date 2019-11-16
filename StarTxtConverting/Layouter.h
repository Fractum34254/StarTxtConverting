#pragma once
#include <string>
#include "Star.h"

struct Layouter
{
	static std::string Layout(const Star& star)
	{
		const std::string fill = "#";
		const std::string end = "=";
		std::string starLine = "";
		
		starLine += star.GetName();
		starLine += fill;
		starLine += star.GetSystem();
		starLine += fill;
		starLine += star.GetStarType();
		starLine += fill;
		starLine += star.GetMainStarClass();
		starLine += fill;
		starLine += star.GetSubStarclass();
		starLine += fill;
		starLine += star.GetRightAscension(fill);
		starLine += fill;
		starLine += star.GetDeclination(fill);
		starLine += fill;
		starLine += star.GetConstellation();
		starLine += fill;
		starLine += star.GetDistance();
		starLine += fill;
		starLine += star.GetParallax();
		starLine += fill;
		starLine += star.GetAppMag();
		starLine += fill;
		starLine += star.GetAbsMag();
		starLine += fill;
		starLine += star.GetMass();
		starLine += fill;
		starLine += star.GetRadius();
		starLine += end;

		return starLine;
	}
};
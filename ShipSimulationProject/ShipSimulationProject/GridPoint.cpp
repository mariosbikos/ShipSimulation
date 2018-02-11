#include "GridPoint.h"
#include <string>

int GridPoint::NumOfPorts;
int GridPoint::NumOfTreasures;

GridPoint::GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort) :X(InX), Y(InY), WeatherConditionLevel(InWeatherConditionLevel), HasTreasure(InHasTreasure), IsPort(InIsPort)
{
	
	if (HasTreasure)
	{
		NumOfTreasures++;
	}

	if (IsPort)
	{
		NumOfPorts++;
	}
	
}

GridPoint::~GridPoint()
{
	if (HasTreasure)
	{
		NumOfTreasures--;
	}

	if (IsPort)
	{
		NumOfPorts--;
	}
	
}

std::string GridPoint::GetSymbol()
{
	if (HasTreasure)
	{
		return "$$$";
	}

	if (IsPort)
	{
		return "!!!";
	}

	return "   ";
}

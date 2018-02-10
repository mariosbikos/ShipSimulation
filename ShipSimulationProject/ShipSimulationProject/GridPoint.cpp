#include "GridPoint.h"
#include <string>

GridPoint::GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort) :X(InX), Y(InY), WeatherConditionLevel(InWeatherConditionLevel), HasTreasure(InHasTreasure), IsPort(InIsPort)
{
	std::cout << "GridPoint Construction: Row = " << X << ", Col= " << Y << " WeatherConditionLevel: " << WeatherConditionLevel << (HasTreasure ? "Treasure" : "") << (IsPort ? "Port" : "") << std::endl;
}

std::string GridPoint::GetSymbol()
{
	if (HasTreasure)
	{
		return "$$$";
	}

	if (IsPort)
	{
		return "PPP";
	}

	return "   ";
}

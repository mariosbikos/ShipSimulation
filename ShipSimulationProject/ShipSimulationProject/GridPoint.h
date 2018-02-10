#pragma once
#include <iostream>
#include <string>

class GridPoint
{
public:
	GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort);

	std::string GetSymbol();
	//private:

	int X;
	int Y;
	int WeatherConditionLevel; //between 1-10
	bool HasTreasure = false;
	bool IsPort = false;
	
};
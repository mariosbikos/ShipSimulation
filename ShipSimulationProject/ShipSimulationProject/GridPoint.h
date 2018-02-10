#pragma once
#include <iostream>

class GridPoint
{
public:
	GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort)
		:X(InX), Y(InY), WeatherConditionLevel(InWeatherConditionLevel), HasTreasure(InHasTreasure), IsPort(InIsPort) 
	{
		std::cout << "GridPoint Construction: Row = " << X << ", Col= " << Y << " WeatherConditionLevel: " << WeatherConditionLevel << (HasTreasure ? "Treasure" : "") << (IsPort ? "Port" : "") << std::endl;
	}

	
private:

	int X, Y;
	int WeatherConditionLevel; //between 1-10
	bool HasTreasure;
	bool IsPort;
	
};
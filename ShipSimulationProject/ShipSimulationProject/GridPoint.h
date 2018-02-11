#pragma once
#include <iostream>
#include <string>
class Ship;

class GridPoint
{
public:
	GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort);
	~GridPoint();

	//The symbol on the map
	std::string GetSymbol();

	static int NumOfTreasures;
	static int NumOfPorts;

	//points to a ship that may occupy this point
	Ship* ShipOnPoint = nullptr;

	bool IsPointEmpty();
private:
	int X;
	int Y;
	int WeatherConditionLevel; //between 1-10
	bool HasTreasure = false;
	bool IsPort = false;

	
	
};
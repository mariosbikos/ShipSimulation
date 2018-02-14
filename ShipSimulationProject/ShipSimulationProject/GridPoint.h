#pragma once
#include <iostream>
#include <string>
#include "Coordinates.h"

class Ship;

class GridPoint
{
public:
	GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort);
	~GridPoint();

	Ship* GetShipOnPoint();

	void SetShipOnPoint(Ship* InShip);
	std::string GetSymbol();

	static int NumOfTreasures;
	static int NumOfPorts;


	bool HasBadWeatherConditions() const;
	void ChangeWeatherConditionsRandomly();
	
	bool HasPort() const;
	bool IsEmpty() const;
	bool HasTreasure() const;
	bool HasShip() const;
	void MakeTreasure();

	void RemoveShipFromPoint();

	Position2D& GetCoordinates();
	void SetCoordinates(const Position2D& InCoords);
private:
	Position2D CoordinatesOnGrid;
	int WeatherConditionLevel; //between 1-10
	bool IsTreasure = false;
	bool IsPort = false;

	//points to a ship that may occupy this point
	Ship* ShipOnPoint = nullptr;
	
	
};
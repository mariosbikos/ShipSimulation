#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Coordinates.h"

using namespace std;

class Ship;
class OceanMap;

class GridPoint
{
public:
	GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort);
	~GridPoint();

	static int NumOfTreasures;
	static int NumOfPorts;

	Ship* GetShipOnPoint();
	void SetShipOnPoint(Ship* InShip);

	std::string GetSymbol();

	std::vector<GridPoint*> GetNeighborPoints();

	void SetOceanMap(OceanMap* InOceanMap);

	bool HasBadWeatherConditions() const;
	void ChangeWeatherConditionsRandomly();
	
	bool IsEmpty() const;
	bool HasPort() const;
	bool HasTreasure() const;
	bool HasShip() const;

	void ConvertToTreasure();

	void RemoveShipFromPoint();

	const Position2D& GetCoordinates() const;
	void SetCoordinates(const Position2D& InCoords);

	friend std::ostream& operator<<(std::ostream& out, const GridPoint& Point);

private:
	Position2D CoordinatesOnGrid;
	int WeatherConditionLevel; //between 1-10
	bool IsTreasure = false;
	bool IsPort = false;

	//points to a ship that may occupy this point
	Ship* ShipOnPoint = nullptr;
	OceanMap* PointOceanMap;
	
};

std::ostream& operator<<(std::ostream& out, const GridPoint& Point);
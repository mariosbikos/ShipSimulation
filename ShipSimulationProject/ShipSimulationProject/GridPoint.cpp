#include "GridPoint.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/SimulationStatics.h"
#include <string>
#include "Coordinates.h"

int GridPoint::NumOfPorts;


GridPoint::GridPoint(int InX, int InY, int InWeatherConditionLevel, bool InHasTreasure, bool InIsPort) :
	CoordinatesOnGrid(InX,InY), WeatherConditionLevel(InWeatherConditionLevel), IsTreasure(InHasTreasure), IsPort(InIsPort)
{

	if (IsTreasure)
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
	if (IsTreasure)
	{
		NumOfTreasures--;
	}

	if (IsPort)
	{
		NumOfPorts--;
	}

}

bool GridPoint::HasBadWeatherConditions() const
{
	return WeatherConditionLevel >= SimulationStatics::BadWeatherThreshold;
}

bool GridPoint::HasPort() const
{
	return IsPort;
}



bool GridPoint::HasTreasure() const
{
	return IsTreasure;
}

bool GridPoint::HasShip() const
{
	return (ShipOnPoint != nullptr);
}

const Position2D& GridPoint::GetCoordinates()
{
	return CoordinatesOnGrid;
}

int GridPoint::NumOfTreasures;



Ship* GridPoint::GetShipOnPoint()
{
	return ShipOnPoint;
}

void GridPoint::SetShipOnPoint(Ship* InShip)
{
	ShipOnPoint = InShip;
}

std::string GridPoint::GetSymbol()
{

	if (HasShip())
	{
		return ShipOnPoint->GetShipName();
	}

	if (HasTreasure())
	{
		return "$$$";
	}

	if (HasPort())
	{
		return "!!!";
	}

	

	return "   ";
}

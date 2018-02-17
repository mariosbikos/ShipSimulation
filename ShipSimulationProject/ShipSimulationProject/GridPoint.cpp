#include "GridPoint.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/SimulationStatics.h"
#include "HelperFunctions.h"
#include <string>
#include "Coordinates.h"

int GridPoint::NumOfPorts;
int GridPoint::NumOfTreasures;

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

void GridPoint::ChangeWeatherConditionsRandomly()
{
	int PreviousWeatherCondition = WeatherConditionLevel;
	int WeatherChangeValue = HelperFunctions::GetRandomIntWithinRange(-1, 1);
	WeatherConditionLevel = HelperFunctions::Clamp(WeatherConditionLevel +WeatherChangeValue,1,10);

	cout << "Weather Conditions changed from : "<< PreviousWeatherCondition<<" to: "<<WeatherConditionLevel<<" at Point: " << this->GetCoordinates() << endl;
}

bool GridPoint::HasPort() const
{
	return IsPort;
}

bool GridPoint::IsEmpty() const
{
	return (!IsPort && !IsTreasure && !ShipOnPoint);
}

bool GridPoint::HasTreasure() const
{
	return IsTreasure;
}

bool GridPoint::HasShip() const
{
	return (ShipOnPoint != nullptr);
}

void GridPoint::MakeTreasure()
{
	IsTreasure = true;
}

void GridPoint::RemoveShipFromPoint()
{
	SetShipOnPoint(nullptr);
}

const Position2D& GridPoint::GetCoordinates() const
{
	return CoordinatesOnGrid;
}

void GridPoint::SetCoordinates(const Position2D& InCoords)
{
	CoordinatesOnGrid = InCoords;
}


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

std::ostream& operator<<(std::ostream& out, const GridPoint& InPoint)
{
	out << "(" << InPoint.GetCoordinates().X << "," << InPoint.GetCoordinates().Y << ")";
	return out;
}

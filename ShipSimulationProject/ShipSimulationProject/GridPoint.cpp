#include "GridPoint.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/SimulationStatics.h"
#include "ShipSimulationProject/OceanMap.h"
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



std::vector<GridPoint*> GridPoint::GetNeighborPoints()
{
	vector<GridPoint*>& OceanGrid = PointOceanMap->Grid;
	std::vector<GridPoint*> NeighborPoints;

	if (CoordinatesOnGrid.Y < OceanMap::NumCols - 1)
	{
		//right(always, unless col=numCols-1)
		NeighborPoints.push_back(OceanGrid[HelperFunctions::Convert2DIndexTo1DIndex(CoordinatesOnGrid.X, CoordinatesOnGrid.Y + 1, OceanMap::NumCols)]);
	}

	if (CoordinatesOnGrid.Y > 0)
	{
		//left(always unless col=0)
		NeighborPoints.push_back(OceanGrid[HelperFunctions::Convert2DIndexTo1DIndex(CoordinatesOnGrid.X, CoordinatesOnGrid.Y - 1, OceanMap::NumCols)]);
	}

	if (CoordinatesOnGrid.X > 0)
	{
		//Up(always unless row=0)
		NeighborPoints.push_back(OceanGrid[HelperFunctions::Convert2DIndexTo1DIndex(CoordinatesOnGrid.X - 1, CoordinatesOnGrid.Y, OceanMap::NumCols)]);

	}

	if (CoordinatesOnGrid.X < OceanMap::NumRows - 1)
	{
		//down(always unless row = numRows-1)
		NeighborPoints.push_back(OceanGrid[HelperFunctions::Convert2DIndexTo1DIndex(CoordinatesOnGrid.X + 1, CoordinatesOnGrid.Y, OceanMap::NumCols)]);
	}

	return NeighborPoints;
}


void GridPoint::SetOceanMap(OceanMap* InOceanMap)
{
	PointOceanMap = InOceanMap;
}

#include <iostream>
#include <string>
#include "Ship.h"
#include "PirateShip.h"
#include "CargoShip.h"
#include "RepairShip.h"
#include "ExplorationShip.h"
#include "ShipTypes.h"
#include "ShipSimulationProject/SimulationStatics.h"
#include "ShipSimulationProject/HelperFunctions.h"
#include "ShipSimulationProject/Coordinates.h"
#include "ShipSimulationProject/GridPoint.h"
#include "ShipSimulationProject/OceanMap.h"
#include <algorithm>
#include <vector>
#include <limits>

int Ship::NumOfShips;



bool Ship::MoveToNewPosition(const Position2D& NewPosition)
{
	bool ShipCanMoveToNewPosition = false;

	if (NewPosition.AreCoordinatesValidOnMap())
	{
		int IndexToOldPosition = HelperFunctions::Convert2DIndexTo1DIndex(ShipGridPoint->GetCoordinates().X, ShipGridPoint->GetCoordinates().Y, OceanMap::NumCols);
		int IndexToNewPosition = HelperFunctions::Convert2DIndexTo1DIndex(NewPosition.X, NewPosition.Y, OceanMap::NumCols);
		if (!(CurrentOceanMap->Grid[IndexToNewPosition]->HasShip()) && !(CurrentOceanMap->Grid[IndexToNewPosition]->HasPort()))
		{
			CurrentOceanMap->Grid[IndexToOldPosition]->RemoveShipFromPoint();
			CurrentOceanMap->Grid[IndexToNewPosition]->SetShipOnPoint(this);
			this->SetShipGridPoint(CurrentOceanMap->Grid[IndexToNewPosition]); //We need to make the ship point to the new gridPosition since it moved
			std::cout << "Ship: " << *this << " moved from Position: " << *CurrentOceanMap->Grid[IndexToOldPosition] << " to position: " << NewPosition << std::endl;
			return true;
		}
	}

	return false;
}


void Ship::Move()
{
	const Position2D& ShipCurrentPointCoords = ShipGridPoint->GetCoordinates();
	MoveDirection RandomDirection = (MoveDirection)HelperFunctions::GetRandomIntWithinRange(0, NumOfDirections - 1);
	bool ShipCanMoveToNewPosition = false;
	int DirectionsCounter = 0;

	while(DirectionsCounter < NumOfDirections)
	{
		Position2D NewPosition = ShipCurrentPointCoords.GetPointAfterMovingToDirection(RandomDirection, Speed);

		if (MoveToNewPosition(NewPosition))
		{
			break;
		}

		RandomDirection = MoveDirection(((int)RandomDirection + 1) % NumOfDirections); // try the next direction
		DirectionsCounter++;
	}
}
	


Ship::Ship()
{
	NumOfShips++;

	MaxDurability = SimulationStatics::ShipMaxDurability;
	CurrentDurability = MaxDurability;
	Speed = HelperFunctions::GetRandomIntWithinRange(2, 3);

}

Ship::~Ship()
{
	NumOfShips--;
}



void Ship::SetupOceanMap(OceanMap* InOceanMap)
{
	CurrentOceanMap = InOceanMap;
}

void Ship::Action()
{
	this->DoAction();
}

Ship* Ship::CreateShip(ShipType ShipChoice)
{
	switch (ShipChoice)
	{
	case ShipType::PirateShipType:
		return new PirateShip;
		break;
	case ShipType::CargoShipType:
		return new CargoShip;
		break;
	case ShipType::RepairShipType:
		return new RepairShip;
		break;
	case ShipType::ExplorationShipType:
		return new ExplorationShip;
		break;
	default:
		break;
	}
	
	std::cout << "Problem creating ship!";
	return nullptr;
}

std::string Ship::GetShipName() const
{
	return Name;
}

void Ship::SetShipGridPoint(GridPoint* InGridPoint)
{
	ShipGridPoint = InGridPoint;
}


GridPoint* Ship::GetShipGridPoint() const
{
	return ShipGridPoint;
}

void Ship::ChangeDurability(const int DurabilityValue)
{
	CurrentDurability += DurabilityValue;
	HelperFunctions::Clamp(CurrentDurability, 0.0, MaxDurability);
}

void Ship::ChangeGold(const double GoldAmount)
{
	Gold += GoldAmount;
	HelperFunctions::Clamp(Gold, 0.0, std::numeric_limits<double>::max());
}

double Ship::GetCurrentGold() const
{
	return Gold;
}

bool Ship::IsDamaged() const
{
	return CurrentDurability < MaxDurability;
}

void Ship::RepairShipDurabilityFromPort()
{
	ChangeDurability(HelperFunctions::GetRandomFloatWithinRange(0, 1)*CurrentDurability);
}

double Ship::GetCurrentDurability() const
{
	return CurrentDurability;
}

double Ship::GetMaxDurability() const
{
	return MaxDurability;
}

ostream& operator<<(ostream& os, const Ship& dt)
{
	os << dt.Name.c_str();
	return os;
}


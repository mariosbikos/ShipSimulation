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

int Ship::NumOfShips;

void Ship::Move(vector<GridPoint*>& Grid, GridPoint* CurrentPoint)
{
	const Position2D& ShipCurrentPointCoords = CurrentPoint->GetCoordinates();
	int RandomDirection = HelperFunctions::GetRandomIntWithinRange(0, NumOfDirections - 1);
	bool ShipCanMoveToNewPosition = false;
	int DirectionsCounter = 0;

	while(!ShipCanMoveToNewPosition && DirectionsCounter < NumOfDirections)
	{
		Position2D NewPosition;
		int IndexToNewPosition = 0;

		switch (RandomDirection)
		{
		case MoveDirection::NORTH:
			NewPosition = ShipCurrentPointCoords + Position2D::UP()*Speed;
			if (!NewPosition.AreCoordinatesValidOnMap())
			{
				break;
			}
			IndexToNewPosition = HelperFunctions::Convert2DIndexTo1DIndex(NewPosition.X, NewPosition.Y, OceanMap::NumCols);
			if (NewPosition.X >= 0 && !(Grid[IndexToNewPosition]->HasShip()) && !(Grid[IndexToNewPosition]->HasPort()))
			{
				ShipCanMoveToNewPosition = true;
			}
			break;
		case MoveDirection::EAST:
			NewPosition = ShipCurrentPointCoords + Position2D::RIGHT()*Speed;
			if (!NewPosition.AreCoordinatesValidOnMap())
			{
				break;
			}
			IndexToNewPosition = HelperFunctions::Convert2DIndexTo1DIndex(NewPosition.X, NewPosition.Y, OceanMap::NumCols);
			if (NewPosition.Y < OceanMap::NumCols && !(Grid[IndexToNewPosition]->HasShip()) && !(Grid[IndexToNewPosition]->HasPort()))
			{
				ShipCanMoveToNewPosition = true;
			}
			break;
		case MoveDirection::WEST:
			NewPosition = ShipCurrentPointCoords + Position2D::LEFT()*Speed;
			if (!NewPosition.AreCoordinatesValidOnMap())
			{
				break;
			}
			IndexToNewPosition = HelperFunctions::Convert2DIndexTo1DIndex(NewPosition.X, NewPosition.Y, OceanMap::NumCols);
			if (NewPosition.Y >= 0 && !(Grid[IndexToNewPosition]->HasShip()) && !(Grid[IndexToNewPosition]->HasPort()))
			{
				ShipCanMoveToNewPosition = true;
			}
			break;
		case MoveDirection::SOUTH:
			NewPosition = ShipCurrentPointCoords + Position2D::LEFT()*Speed;
			if (!NewPosition.AreCoordinatesValidOnMap())
			{
				break;
			}
			IndexToNewPosition = HelperFunctions::Convert2DIndexTo1DIndex(NewPosition.X, NewPosition.Y, OceanMap::NumCols);
			if (NewPosition.X < OceanMap::NumRows && !(Grid[IndexToNewPosition]->HasShip()) && !(Grid[IndexToNewPosition]->HasPort()))
			{
				ShipCanMoveToNewPosition = true;
			}
			break;
		default:
			break;
		}

		if (ShipCanMoveToNewPosition)
		{
			Grid[IndexToNewPosition]->SetShipOnPoint(this);
			CurrentPoint->RemoveShipFromPoint();
			std::cout << "Ship: " << *this << " moved from Position: " << *CurrentPoint << " to position: " << NewPosition << std::endl;
			break;
		}

		RandomDirection = (RandomDirection + 1) % NumOfDirections; // try the next direction
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

void Ship::ApplyDamage(const int DamageValue)
{
	CurrentDurability--;
}

void Ship::IncreaseGold(const double GoldAmount)
{
	Gold += GoldAmount;
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
	CurrentDurability += HelperFunctions::GetRandomFloatWithinRange(0, 1)*CurrentDurability;
	if (CurrentDurability > MaxDurability)
	{
		CurrentDurability = MaxDurability;
	}
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


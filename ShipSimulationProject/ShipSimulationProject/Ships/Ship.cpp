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
#include <algorithm>
#include <vector>

int Ship::NumOfShips;



void Ship::Move(vector<GridPoint*>& Grid, GridPoint* CurrentPoint)
{
	switch (HelperFunctions::GetRandomIntWithinRange(0, NumOfDirections - 1))
	{
	case MoveDirection::NORTH:
		if((CurrentPoint->GetCoordinates()+Position2D::UP()*Speed).X>0)
		break;
	case MoveDirection::EAST:
		break;
	case MoveDirection::WEST:
		break;
	case MoveDirection::SOUTH:
		break;
	default:
		break;
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


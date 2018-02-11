#include <iostream>
#include "Ship.h"
#include "PirateShip.h"
#include "CargoShip.h"
#include "RepairShip.h"
#include "ExplorationShip.h"
#include "ShipTypes.h"
#include "ShipSimulationProject/SimulationStatics.h"

int Ship::NumOfShips;


void Ship::Move()
{
	//pre-move. Standard things all ships do before they move
	this->DoMove(); //each subclass can do different things
	//after-move. Standard things all ships do after they move
}

Ship::Ship()
{
	NumOfShips++;
	MaxDurability = SimulationStatics::ShipMaxDurability;
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

std::string Ship::GetShipName()
{
	return Name;
}

void Ship::ApplyDamage(const int DamageValue)
{
	CurrentDurability--;
}

void Ship::IncreaseGold(const double GoldAmount)
{
	Gold += GoldAmount
}


#include "RepairShip.h"
#include "ShipSimulationProject/Ships/Ship.h"

int RepairShip::RepairShipID;

RepairShip::RepairShip()
{
	RepairShipID++;
	this->Name = "R" + RepairShipID;
}

RepairShip::~RepairShip()
{
	RepairShipID--;
}

void RepairShip::DoAction()
{
	//if other ship in neighborhood->increase its durability+get back gold
}

void RepairShip::DoMove()
{

}


#include "RepairShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"

int RepairShip::RepairShipID;

RepairShip::RepairShip()
{
	RepairShipID++;
	this->Name = "R" + HelperFunctions::ShipIDToString(RepairShipID);
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


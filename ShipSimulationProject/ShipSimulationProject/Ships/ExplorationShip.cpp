#include "ExplorationShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"

int ExplorationShip::ExplorationShipID;

ExplorationShip::ExplorationShip()
{
	ExplorationShipID++;
	this->Name = "E" + HelperFunctions::ShipIDToString(ExplorationShipID);
}

ExplorationShip::~ExplorationShip()
{
	ExplorationShipID--;
}

void ExplorationShip::DoAction()
{
	//Check if pirate ship or bad weather conditions in neighborhood+move to opposite direction!
}


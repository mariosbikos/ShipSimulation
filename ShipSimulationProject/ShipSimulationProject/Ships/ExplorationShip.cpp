#include "ExplorationShip.h"
#include "ShipSimulationProject/Ships/Ship.h"

int ExplorationShip::ExplorationShipID;

ExplorationShip::ExplorationShip()
{
	ExplorationShipID++;
	this->Name = "E" + ExplorationShipID;
}

ExplorationShip::~ExplorationShip()
{
	ExplorationShipID--;
}

void ExplorationShip::DoAction()
{
	//Check if pirate ship or bad weather conditions in neighborhood+move to opposite direction!
}

void ExplorationShip::DoMove()
{

}


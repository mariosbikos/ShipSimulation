#include "PirateShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"

int PirateShip::PirateShipID;

PirateShip::PirateShip()
{
	PirateShipID++;
	this->Name = "P" + HelperFunctions::ShipIDToString(PirateShipID);
}

PirateShip::~PirateShip()
{
	PirateShipID--;
}

void PirateShip::DoMove()
{
	
}

void PirateShip::DoAction()
{
	//Attacks ship in neighborhood + steals gold from it
}

void PirateShip::AttackShip(Ship* otherShip)
{
	otherShip->ApplyDamage(this->AttackDamage);
}


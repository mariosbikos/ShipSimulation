#include "PirateShip.h"
#include "ShipSimulationProject/Ships/Ship.h"

int PirateShip::PirateShipID;

PirateShip::PirateShip()
{
	PirateShipID++;
	this->Name = "P" + PirateShipID;
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


#include "CargoShip.h"
#include "ShipSimulationProject/SimulationStatics.h"

int CargoShip::CargoShipID;

CargoShip::CargoShip()
{
	CargoShipID++;
	this->Name = "C" + CargoShipID;
}

CargoShip::~CargoShip()
{
	CargoShipID--;
}

void CargoShip::DoAction()
{
	//if port in neighborhood, increase this->gold by standard value
	GainGoldFromClosePort();
}

void CargoShip::DoMove()
{
	
}

void CargoShip::GainGoldFromClosePort()
{
	this->Gold += SimulationStatics::NearPortGoldIncreaseForCargoShip;
}


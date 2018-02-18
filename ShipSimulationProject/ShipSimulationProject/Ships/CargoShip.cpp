#include "CargoShip.h"
#include "ShipSimulationProject/SimulationStatics.h"
#include "ShipSimulationProject/HelperFunctions.h"
#include "ShipSimulationProject/GridPoint.h"
#include <string>


int CargoShip::CargoShipID;

CargoShip::CargoShip()
{
	CargoShipID++;
	this->Name = "C" + HelperFunctions::ShipIDToString(CargoShipID);
}

CargoShip::~CargoShip()
{
	CargoShipID--;
}

void CargoShip::DoAction()
{
	//if port in neighborhood, increase this->gold by standard value
	for (const GridPoint* NeighborPoint : ShipGridPoint->GetNeighborPoints())
	{
		if (NeighborPoint->HasPort())
		{
			int GoldEarnedFromPort = SimulationStatics::NearPortGoldIncreaseForCargoShip;
			this->Gold += GoldEarnedFromPort;
			cout << "Ship: " << *this << " earned:" << GoldEarnedFromPort << " Gold from neighbor Port at: " << *NeighborPoint << endl;
		}
	}
}



#include "RepairShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"
#include "ShipSimulationProject/GridPoint.h"
#include "ShipSimulationProject/SimulationStatics.h"

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
	for (GridPoint* NeighborPoint : ShipGridPoint->GetNeighborPoints())
	{
		if (NeighborPoint->HasShip() && NeighborPoint->GetShipOnPoint()->IsDamaged())
		{
			RepairNeighborShipForGold(NeighborPoint->GetShipOnPoint());
		}
	}
}

void RepairShip::RepairNeighborShipForGold(Ship* OtherShip)
{
	if (OtherShip->GetCurrentGold() >= SimulationStatics::RepairCostInGold)
	{
		OtherShip->ChangeGold(-SimulationStatics::RepairCostInGold);
		this->ChangeGold(SimulationStatics::RepairCostInGold);
		OtherShip->ChangeDurability(SimulationStatics::RepairShipDurabilityIncreaseAfterRepair);
		cout << "Ship: " << *this << " Repaired Ship: " << *OtherShip << " at Position: "<<*OtherShip->GetShipGridPoint()<< " by: "<< SimulationStatics::RepairShipDurabilityIncreaseAfterRepair <<" for: "<< SimulationStatics::RepairCostInGold<<" Gold" << endl;
	}
}



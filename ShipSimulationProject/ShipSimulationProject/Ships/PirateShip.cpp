#include "PirateShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"
#include "ShipSimulationProject/GridPoint.h"

int PirateShip::PirateShipID;

PirateShip::PirateShip()
{
	PirateShipID++;
	this->Name = "P" + HelperFunctions::ShipIDToString(PirateShipID);
	Speed = 1;
}

PirateShip::~PirateShip()
{
	PirateShipID--;
}



void PirateShip::DoAction()
{
	//Attacks ship in neighborhood + steals gold from it
	for (GridPoint* NeighborPoint : ShipGridPoint->GetNeighborPoints())
	{
		if (NeighborPoint->HasShip())
		{
			AttackShip(NeighborPoint->GetShipOnPoint());
		}
	}

}

void PirateShip::AttackShip(Ship* otherShip)
{
	otherShip->ApplyDamage(this->AttackDamage);
	int GoldToSteal = HelperFunctions::GetRandomFloatWithinRange(0, 1) * otherShip->GetCurrentGold();
	if (GoldToSteal > 0) //otherShip might not have any gold
	{
		otherShip->DecreaseGold(GoldToSteal);
		this->IncreaseGold(GoldToSteal);
	}
	cout << "Ship: " << *this << " attacked Ship:"<<*otherShip<<" and stole: "<< GoldToSteal<< endl;
}


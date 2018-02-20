#pragma once
#include "Ship.h"

class RepairShip : public Ship
{
public:
	RepairShip();
	virtual ~RepairShip();

	static int RepairShipID;

protected:
	virtual void DoAction();

private:
	void RepairNeighborShip(Ship* OtherShip);
};

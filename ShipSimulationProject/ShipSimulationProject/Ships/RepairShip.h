#pragma once
#include "Ship.h"

class RepairShip : public Ship
{
public:
	RepairShip();
	virtual ~RepairShip();
	static int RepairShipID;
private:
	virtual void DoAction();
	virtual void DoMove();
};
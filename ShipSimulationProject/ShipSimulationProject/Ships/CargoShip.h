#pragma once
#include "Ship.h"

class CargoShip : public Ship
{
public:
	CargoShip();
	virtual ~CargoShip();
	static int CargoShipID;
private:
	virtual void DoAction();

};
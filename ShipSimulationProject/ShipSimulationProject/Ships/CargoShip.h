#pragma once
#include "Ship.h"

class CargoShip : public Ship
{
private:
	virtual void DoAction();
	virtual void DoMove();
};
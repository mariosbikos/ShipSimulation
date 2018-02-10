#pragma once
#include "Ship.h"

class RepairShip : public Ship
{
private:
	virtual void DoAction();
	virtual void DoMove();
};
#pragma once
#include "Ship.h"

class ExplorationShip :public Ship
{
public:
	ExplorationShip();
	virtual ~ExplorationShip();
	static int ExplorationShipID;
private:
	virtual void DoAction();
	
};
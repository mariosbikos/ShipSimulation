#pragma once
#include "Ship.h"

class ExplorationShip :public Ship
{
private:
	virtual void DoAction();
	virtual void DoMove();
};
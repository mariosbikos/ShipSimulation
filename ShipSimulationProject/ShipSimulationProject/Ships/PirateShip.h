#pragma once
#include "Ship.h"

class PirateShip : public Ship
{

public:
	PirateShip();
	virtual ~PirateShip();
	static int PirateShipID;
	void AttackShip(Ship* otherShip);

protected:
	
	virtual void DoAction();
	int AttackDamage = 1;
	//always speed = 1;

private:
	
};
#pragma once
#include "Ship.h"

class PirateShip : public Ship
{
protected:
	virtual void DoMove();
	virtual void DoAction();
public:
	void AttackShip(Ship* otherShip);
	
private:
	int AttackDamage;
	//always speed = 1;
	
};
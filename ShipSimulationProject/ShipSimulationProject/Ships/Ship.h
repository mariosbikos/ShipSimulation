#pragma once 
#include <iostream>
enum ShipType : int;

class Ship
{

public:
	Ship();
	virtual ~Ship();

	void Action();
	void Move();

	static int NumOfShips;
	static Ship* CreateShip(ShipType ShipChoice); //Factory Method

	void ApplyDamage(const int DamageValue);
	void IncreaseGold(const double GoldAmount);

	std::string GetShipName();
protected: 
	int CurrentDurability;
	int MaxDurability;
	int Speed;
	double Gold;

	std::string Name;

	virtual void DoMove() = 0;
	virtual void DoAction() = 0;

};

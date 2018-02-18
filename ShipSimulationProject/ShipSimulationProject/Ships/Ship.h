#pragma once 
#include <iostream>
#include <string>
#include <vector>

enum ShipType : int;
class GridPoint;
class OceanMap;

using namespace std;

class Ship
{

public:
	Ship();
	virtual ~Ship();

	void Action();
	void Move(vector<GridPoint*>& Grid, GridPoint* CurrentPoint);

	static int NumOfShips; //Total Num of ships of all types
	static Ship* CreateShip(ShipType ShipChoice); //Factory Method

	void ApplyDamage(const int DamageValue);
	void IncreaseGold(const double GoldAmount); 
	double GetCurrentGold() const;
	bool IsDamaged() const;
	void RepairShipDurabilityFromPort();
	double GetCurrentDurability() const;
	double GetMaxDurability() const;
	std::string GetShipName() const;
	void SetShipGridPoint(GridPoint* InGridPoint);
	GridPoint* GetShipGridPoint() const;
	friend ostream& operator<<(ostream& os, const Ship& dt);
protected: 
	double CurrentDurability;
	double MaxDurability;
	int Speed;
	double Gold=0;
	std::string Name;

	GridPoint* ShipGridPoint = nullptr;

	virtual void DoAction() = 0;
};


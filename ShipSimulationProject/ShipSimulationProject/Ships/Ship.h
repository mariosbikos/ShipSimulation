#pragma once 
#include <iostream>
#include <string>
#include <vector>

enum ShipType : int;
enum MoveDirection : int;
class GridPoint;
class OceanMap;
class Position2D;

using namespace std;

class Ship
{

public:
	Ship();
	virtual ~Ship();

	void SetupOceanMap(OceanMap* InOceanMap);
	void Action();
	void Move();

	static int NumOfShips; //Total Num of ships of all types
	bool MoveToNewPosition(const Position2D& NewPosition);
	static Ship* CreateShip(ShipType ShipChoice); //Factory Method

	void ApplyDamage(const int DamageValue);
	void IncreaseGold(const double GoldAmount); 
	void DecreaseGold(const double GoldAmount);
	double GetCurrentGold() const;
	bool IsDamaged() const;
	void RepairShipDurabilityFromPort();
	
	double GetCurrentDurability() const;
	double GetMaxDurability() const;
	std::string GetShipName() const;
	void SetShipGridPoint(GridPoint* InGridPoint);
	GridPoint* GetShipGridPoint() const;
	void RepairShipDurability(const double DurabilityToAdd);

	friend ostream& operator<<(ostream& os, const Ship& dt);
protected: 
	double CurrentDurability;
	double MaxDurability;
	int Speed;
	double Gold=0;
	std::string Name;
	

	GridPoint* ShipGridPoint = nullptr;
	OceanMap* CurrentOceanMap = nullptr;
	virtual void DoAction() = 0;
private:
	
};


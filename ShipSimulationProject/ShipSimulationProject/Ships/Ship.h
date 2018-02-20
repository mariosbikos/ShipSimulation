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
	static Ship* CreateShip(ShipType ShipChoice); //Factory Method

	GridPoint* GetShipGridPoint() const;
	void SetShipGridPoint(GridPoint* InGridPoint);
	bool MoveToNewPosition(const Position2D& NewPosition);

	void ChangeGold(const double GoldAmount); 
	double GetCurrentGold() const;
	
	double GetCurrentDurability() const;
	double GetMaxDurability() const;
	bool IsDamaged() const;
	void ChangeDurability(const int DurabilityValue);
	void RepairShipDurabilityFromPort();

	std::string GetShipName() const;

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

};


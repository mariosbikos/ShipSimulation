#pragma once
#include <vector>

class GridPoint;
class Ship;
using namespace std;

class OceanMap
{
public:
	vector<GridPoint*> Grid;
	vector<Ship*> AllShips;

	void Init();
	void PlaceShipOnAvailableGridPosition(Ship* ShipToPlace);
	void PlaceShipOnGridPoint(Ship* ShipToPlace, GridPoint* Position);
	void Terminate();
	void PrintMap();
	bool ShowMenu();
	void StartTurn();
	vector<GridPoint*> GetNeighborsForPoint(GridPoint* position);

	static int NumRows;
	static int NumCols;

private:
	void CreateShips();
	void InitializeMap();
	void QueryUserForMapSize();

	void ApplyChangesToPortNeighbors(GridPoint* PortPoint);
};

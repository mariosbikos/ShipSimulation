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
	//Places given ship to a GridPoint as long as it's not a port and there isn't any ship there
	void PlaceShipOnAvailableGridPoint(Ship* ShipToPlace);
	void PlaceShipOnGridPoint(Ship* ShipToPlace, GridPoint* Position);
	void Terminate();
	void PrintMap();
	bool ShowMenu();
	bool CheckForEndConditions();
	void EndTurn();
	void DestroyShipAtPoint(GridPoint* Point);
	void StartTurn();
	vector<GridPoint*> GetNeighborsForPoint(GridPoint* position);

	static int NumRows;
	static int NumCols;

private:
	void CreateShips();
	void InitializeMapWithGridPoints();
	void QueryUserForMapSize();

	//If point has a pirate ship on it then damage is applied to it, otherwise the ship is repaired by a %.
	void ApplyChangesToPortNeighbors(GridPoint* PortPoint);
};

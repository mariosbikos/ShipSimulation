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
	void Terminate();
	void PrintMap();
	void ShowMenu();

	static int NumRows;
	static int NumCols;

private:
	void CreateShips();
	void InitializeMap();
	void QueryUserForMapSize();
};
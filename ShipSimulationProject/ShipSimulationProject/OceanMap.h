#pragma once
#include <vector>

class GridPoint;
using namespace std;

class OceanMap
{
public:
	vector<GridPoint*> Grid;

	void Init();
	void Terminate();

	void PrintMap();



	static int NumRows;
	static int NumCols;



private:
	void CreateShips();
	void InitializeMap();
	void QueryUserForMapSize();
};
#pragma once
#include <vector>
#include "GridPoint.h"

class OceanMap
{
public:
	std::vector<GridPoint*> Grid;

	void Init();
	void Terminate();
	static int NumRows;
	static int NumCols;

private:
	void CreateShips();
	void InitializeMap();
	void QueryUserForMapSize();
};
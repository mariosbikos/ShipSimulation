#include <iostream>
#include "HelperFunctions.h"
#include "OceanMap.h"
#include<stdlib.h>
#include <time.h>       /* time */
#include "SimulationStatics.h"

int OceanMap::NumRows;
int OceanMap::NumCols;

void OceanMap::Init()
{
	QueryUserForMapSize();
	InitializeMap();
	CreateShips();
}

void OceanMap::CreateShips()
{

}

void OceanMap::InitializeMap()
{
	srand(time(0));
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Col = 0; Col < NumCols; Col++)
		{
			int RandomNumberForType = rand() % 100;
			bool IsPort = false;
			bool HasTreasure = false;
			if (RandomNumberForType < SimulationStatics::ChanceForPortPercentage)
			{
				IsPort = true;
			}
			else if (RandomNumberForType < SimulationStatics::ChanceForPortPercentage + SimulationStatics::ChanceForTreasurePercentage)
			{
				HasTreasure = true;
			}

			int RandomWeatherConditionLevel = rand() % 10 + 1;
			GridPoint* point = new GridPoint(Row, Col, RandomWeatherConditionLevel, IsPort, HasTreasure);
			Grid.push_back(point);
		}
	}
}

void OceanMap::QueryUserForMapSize()
{
	std::cout << "Welcome to Ship Simulation. Please enter the the size of the Grid (e.g for 5x5 enter 5): ";
	std::cin >> NumRows;
	NumCols = NumRows;
	std::cout << "A Grid was created that is: " << NumRows << " X " << NumCols << std::endl;
}


void OceanMap::Terminate()
{
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Col = 0; Col < NumCols; Col++)
		{
			int Index = HelperFunctions::Convert2DIndexTo1DIndex(Row, Col, NumCols);
			delete Grid[Index];
		}
	}
}




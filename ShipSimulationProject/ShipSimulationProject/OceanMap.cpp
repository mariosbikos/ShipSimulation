#include <iostream>
#include<stdlib.h>
#include <time.h>       /* time */
#include "HelperFunctions.h"
#include "OceanMap.h"
#include "Ships/Ship.h"
#include "SimulationStatics.h"
#include "GridPoint.h"
#include "Ships/ShipTypes.h"

int OceanMap::NumRows;
int OceanMap::NumCols;

using namespace std;

enum MenuChoice
{
	Invalid=-1,
	EndSimulation,
	Stats
	
};

void OceanMap::Init()
{
	QueryUserForMapSize();
	InitializeMap();
	CreateShips();
}

void OceanMap::CreateShips()
{
	//Create random ships of each type but make sure they fit the map
	Ship* NewShip = Ship::CreateShip(ShipType::CargoShipType);


	//Assign to random GridPoint that is not a port and does not have treasure
	//Grid[].ShipOnPoint = NewShip;
}

void OceanMap::InitializeMap()
{
	srand(time(NULL));
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
	cout << "Welcome to Ship Simulation. Please enter the the size of the Grid (e.g for 5x5 enter 5): ";
	cin >> NumRows;
	NumCols = NumRows;
	cout << "A Grid was created that is: " << NumRows << " X " << NumCols << endl;
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

void OceanMap::PrintMap()
{
	for (int Col = 0; Col < NumCols; Col++)
	{
		cout << "\t[" << Col << "]";
	}
	cout << endl<< endl;

	for (int Row = 0; Row < NumRows; Row++)
	{
		cout << "["<<Row<<"]";
		for (int Col = 0; Col < NumCols; Col++)
		{
			cout << "\t";
			cout << Grid[HelperFunctions::Convert2DIndexTo1DIndex(Row, Col, NumCols)]->GetSymbol();
		}
		cout << endl<<endl;
		
	}
}

void OceanMap::ShowMenu()
{
	MenuChoice Choice = MenuChoice::Invalid;
	while (Choice == MenuChoice::Invalid)
	{
		int selection = 0;
		cout << "Menu" << endl;
		cout << "Please select one of the following commands" << endl;
		cout << "1. Get Stats" << endl;
		cout << "0. Stop Simulation" << endl;

		cin >> selection;
		Choice = (MenuChoice)selection;
	}

	switch ((MenuChoice)Choice)
	{
	case MenuChoice::EndSimulation:
		cout << "Terminating program" << endl;
		break;
	case MenuChoice::Stats:
		cout << "Stats" << endl;
		cout << "Num Of Ports: " <<GridPoint::NumOfPorts<< endl;
		cout << "Num Of Treasures: " << GridPoint::NumOfTreasures << endl;
		break;
	default:
		break;
	}
}


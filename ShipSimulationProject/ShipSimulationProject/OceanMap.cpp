#include <iostream>
#include<stdlib.h>
#include <time.h>       /* time */
#include "HelperFunctions.h"
#include "OceanMap.h"
#include "Ships/Ship.h"
#include "ShipSimulationProject/Ships/CargoShip.h"
#include "ShipSimulationProject/Ships/PirateShip.h"
#include "ShipSimulationProject/Ships/ExplorationShip.h"
#include "ShipSimulationProject/Ships/RepairShip.h"
#include "SimulationStatics.h"
#include "GridPoint.h"
#include "Ships/ShipTypes.h"
#include <math.h>

using namespace std;

int OceanMap::NumRows;
int OceanMap::NumCols;

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

void OceanMap::Terminate()
{
	for (GridPoint* Gridpoint : Grid)
	{
		delete Gridpoint;
	}

	for (Ship* ShipInGrid : AllShips)
	{
		delete ShipInGrid;
	}
}


void OceanMap::PlaceShipOnAvailableGridPosition(Ship* ShipToPlace)
{
	while (true)
	{
		int RandomIndexToPlaceShip = HelperFunctions::GetRandomIntWithinRange(0, (NumCols*NumRows) - 1);
		if (Grid[RandomIndexToPlaceShip]->IsPointEmpty())
		{
			Grid[RandomIndexToPlaceShip]->ShipOnPoint = ShipToPlace;
			break;
		}
	}
}

void OceanMap::CreateShips()
{
	int AvailableEmptySpacesForShips = (NumCols*NumRows) - (GridPoint::NumOfPorts + GridPoint::NumOfTreasures);
	//Create random ships of each type but make sure they fit the map
	int NumOfShipsToCreate = HelperFunctions::GetRandomIntWithinRange(1, round(SimulationStatics::PercentageOfMaxRandomNumberOfShips*AvailableEmptySpacesForShips));
	for (int i = 0; i < NumOfShipsToCreate; i++)
	{
		ShipType RandomType = (ShipType)HelperFunctions::GetRandomIntWithinRange(0, ShipType::NumOfDifferentShipTypes - 1);
		Ship* NewShip = Ship::CreateShip(RandomType);
		AllShips.push_back(NewShip);
		//Assign to random GridPoint that is not a port and does not have treasure
		PlaceShipOnAvailableGridPosition(NewShip);
	}
	
}

void OceanMap::InitializeMap()
{
	for (int Row = 0; Row < NumRows; Row++)
	{
		for (int Col = 0; Col < NumCols; Col++)
		{
			int RandomNumberForType = HelperFunctions::GetRandomIntWithinRange(0, 100);
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

			int RandomWeatherConditionLevel = HelperFunctions::GetRandomIntWithinRange(1, 10);
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
		cout << "Num Of Ships: " << AllShips.size() << endl;
		cout << "Num Of Pirate Ships: " << PirateShip::PirateShipID << endl;
		cout << "Num Of Cargo Ships: " << CargoShip::CargoShipID << endl;
		cout << "Num Of Repair Ships: " << RepairShip::RepairShipID << endl;
		cout << "Num Of Exploration Ships: " << ExplorationShip::ExplorationShipID << endl;
		break;
	default:
		break;
	}
}


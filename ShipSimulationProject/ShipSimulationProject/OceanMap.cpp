#include <iostream>
#include<stdlib.h>
#include <time.h>       /* time */
#include <algorithm>   
#include "HelperFunctions.h"
#include "OceanMap.h"
#include "Ships/Ship.h"
#include "ShipSimulationProject/Ships/CargoShip.h"
#include "ShipSimulationProject/Ships/PirateShip.h"
#include "ShipSimulationProject/Ships/ExplorationShip.h"
#include "ShipSimulationProject/Ships/RepairShip.h"
#include "SimulationStatics.h"
#include "ShipSimulationProject/GridPoint.h"
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
	InitializeMapWithGridPoints();
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

void OceanMap::PlaceShipOnAvailableGridPoint(Ship* ShipToPlace)
{
	while (true)
	{
		int RandomIndexToPlaceShip = HelperFunctions::GetRandomIntWithinRange(0, (NumCols*NumRows) - 1);
		GridPoint* GridPointToPlaceShip = Grid[RandomIndexToPlaceShip];
		if (!GridPointToPlaceShip->HasShip() && 
			!GridPointToPlaceShip->HasPort() && 
			!GridPointToPlaceShip->HasShip())
		{
			GridPointToPlaceShip->SetShipOnPoint(ShipToPlace);
			ShipToPlace->SetShipGridPoint(GridPointToPlaceShip);
			break;
		}
	}
}

void OceanMap::CreateShips()
{
	int AvailableEmptySpacesForShips = (NumCols*NumRows) - GridPoint::NumOfPorts;
	//Create random ships of each type but make sure they fit the map
	int NumOfShipsToCreate = (int)HelperFunctions::GetRandomFloatWithinRange(1, HelperFunctions::Clamp(round(SimulationStatics::PercentageOfMaxRandomNumberOfShips*static_cast<double>(AvailableEmptySpacesForShips)),1.0, (double)AvailableEmptySpacesForShips));
	for (int i = 0; i < NumOfShipsToCreate; i++)
	{
		ShipType RandomType = (ShipType)HelperFunctions::GetRandomIntWithinRange(0, ShipType::NumOfDifferentShipTypes - 1);
		Ship* NewShip = Ship::CreateShip(RandomType);
		NewShip->SetupOceanMap(this);
		AllShips.push_back(NewShip);

		PlaceShipOnAvailableGridPoint(NewShip);
	}
}

void OceanMap::InitializeMapWithGridPoints()
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
			point->SetOceanMap(this);
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

bool OceanMap::ShowMenu()
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
		return true;
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

	return false;
}

bool OceanMap::CheckForEndConditions()
{
	if (Ship::NumOfShips == 0)
	{
		cout << "Game Over: All Ships have been destroyed!" << endl;
		return true;
	}

	for (Ship* CurrentShip : AllShips)
	{
		if (CurrentShip->GetCurrentGold() >= SimulationStatics::TargetGold)
		{
			cout << "Game Over: Ship: "<< *CurrentShip << " has reached Target Gold" << endl;
			return true;
		}
	}
	return false;
}

void OceanMap::EndTurn()
{
	cout  << endl << endl<< "---END TURN---" << endl << endl;
	for (GridPoint* Point : Grid)
	{
		Point->ChangeWeatherConditionsRandomly();

		if (Point->IsEmpty())
		{
			continue;
		}

		Ship* CurrentShip = Point->GetShipOnPoint();
		if (CurrentShip && CurrentShip->GetCurrentDurability()<=0)
		{
			cout << *CurrentShip << " was destroyed and replaced with Treasure at: " << Point->GetCoordinates() << endl;
			Point->MakeTreasure();
			DestroyShipAtPoint(Point);
		}
	}
}

void OceanMap::DestroyShipAtPoint(GridPoint* Point)
{
	Ship* ShipToDestroy = Point->GetShipOnPoint();

	std::vector<Ship*>::iterator position = std::find(AllShips.begin(), AllShips.end(), ShipToDestroy);
	if (position != AllShips.end()) // == myVector.end() means the element was not found
	{
		AllShips.erase(position);
		delete ShipToDestroy;
	}
		

	Point->RemoveShipFromPoint();
}


void OceanMap::StartTurn()
{
	cout <<endl<<  endl <<"---START TURN---" << endl << endl;
	//Grid
	//	AllShips
	for (Ship* CurrentShip : AllShips)
	{
		GridPoint* ShipGridPoint = CurrentShip->GetShipGridPoint();

		if (ShipGridPoint->HasBadWeatherConditions())
		{
			CurrentShip->ApplyDamage(SimulationStatics::DamageCausedByBadWeather);
			cout << *CurrentShip << " got damage due to bad weather conditions at position: " << *ShipGridPoint << endl;
		}

		if (ShipGridPoint->HasTreasure())
		{
			CurrentShip->IncreaseGold(SimulationStatics::GoldRewardForTreasurePoint);
			cout << *CurrentShip << " earned: "<< SimulationStatics::GoldRewardForTreasurePoint <<" Gold since it is on top of a Treasure Point at: " << *ShipGridPoint << endl;
		}
	}

	for (GridPoint* Point : Grid)
	{
		if (Point->HasPort())
		{
			ApplyChangesToPortNeighbors(Point);
		}
	}

}

void OceanMap::ApplyChangesToPortNeighbors(GridPoint* PortPoint)
{
	//Need vector of GridPoints neighbors
	std::vector<GridPoint*>& Neighbors = PortPoint->GetNeighborPoints();
	for (GridPoint* NeighborPoint : Neighbors)
	{
		Ship* NeighborShip = NeighborPoint->GetShipOnPoint();
		if (NeighborShip)
		{
			PirateShip* PirateNeighbor = dynamic_cast<PirateShip*>(NeighborShip);
			if (PirateNeighbor)
			{
				NeighborShip->ApplyDamage(SimulationStatics::DamageCausedToPirateShipByPort);
				cout << *NeighborShip << " at Point: " << NeighborPoint->GetCoordinates() << " got Damage due to Port at : " << PortPoint->GetCoordinates() << endl;
			}
			else
			{
				//TODO: Move all couts inside the ship class+only print if durability<max
				NeighborShip->RepairShipDurabilityFromPort();
				cout << *NeighborShip << " at Point: " << NeighborPoint->GetCoordinates() << " was repaired from neighbor Port at: " << PortPoint->GetCoordinates() << endl;
			}
		}
	}

}

void OceanMap::ShipsMovePhase()
{
	cout <<endl<< endl << "--- MOVE PHASE---" << endl<< endl;
	for (Ship* CurrentShip : AllShips)
	{
		CurrentShip->Move();
	}
}

void OceanMap::ShipsActionPhase()
{
	cout << endl<< endl <<"---ACTION PHASE---" << endl<< endl;
	for (Ship* CurrentShip : AllShips)
	{
		CurrentShip->Action();
	}
}
	

std::vector<GridPoint*> OceanMap::GetNeighborsForPoint(GridPoint* position)
{
	std::vector<GridPoint*> NeighborPoints;
	Position2D CurrentPositionCoords = position->GetCoordinates();

	if (CurrentPositionCoords.Y < NumCols-1)
	{
		//right(always, unless col=numCols-1)
		NeighborPoints.push_back(Grid[HelperFunctions::Convert2DIndexTo1DIndex(CurrentPositionCoords.X, CurrentPositionCoords.Y + 1, NumCols)]);
	}
	
	if (CurrentPositionCoords.Y > 0)
	{
		//left(always unless col=0)
		NeighborPoints.push_back(Grid[HelperFunctions::Convert2DIndexTo1DIndex(CurrentPositionCoords.X, CurrentPositionCoords.Y - 1, NumCols)]);
	}
	
	if (CurrentPositionCoords.X > 0)
	{
		//Up(always unless row=0)
		NeighborPoints.push_back(Grid[HelperFunctions::Convert2DIndexTo1DIndex(CurrentPositionCoords.X - 1, CurrentPositionCoords.Y, NumCols)]);

	}

	if (CurrentPositionCoords.X < NumRows-1)
	{
		//down(always unless row = numRows-1)
		NeighborPoints.push_back(Grid[HelperFunctions::Convert2DIndexTo1DIndex(CurrentPositionCoords.X + 1, CurrentPositionCoords.Y, NumCols)]);
	}

	return NeighborPoints;
}


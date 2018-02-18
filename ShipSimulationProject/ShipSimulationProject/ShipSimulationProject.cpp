// ShipSimulationProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "OceanMap.h"
#include "GridPoint.h"
#include "ShipSimulationProject/Ships/Ship.h"

int main()
{
	OceanMap Map;
	Map.Init();
	Map.PrintMap();
	bool EndGame = false;
	while (true)
	{
		//Start Turn
		Map.StartTurn();

		//Move phase
		Map.ShipsMovePhase();

		//Action phase 
		Map.ShipsActionPhase();

		//End Turn Phase
		Map.EndTurn();

		Map.PrintMap();

		//EndSimulation?
		EndGame = Map.ShowMenu();
		EndGame = Map.CheckForEndConditions();

		if (EndGame)
		{
			break;
		}
	}


	Map.Terminate();


	system("pause");
    return 0;
}


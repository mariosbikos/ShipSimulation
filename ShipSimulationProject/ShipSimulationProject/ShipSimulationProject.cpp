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
	std::cout << GridPoint::NumOfPorts;
	bool EndGame = false;
	while (true)
	{
		Map.PrintMap();
		
		//Start Turn
		Map.StartTurn();


		//Move phase

		//Action phase 

		//End Turn Phase
		Map.EndTurn();


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


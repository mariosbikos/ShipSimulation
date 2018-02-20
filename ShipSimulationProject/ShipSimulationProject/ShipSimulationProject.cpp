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

	Map.PrintMap();
	bool EndGame = false;
	while (true)
	{
		Map.StartTurn();

		Map.ShipsMovePhase();

		Map.ShipsActionPhase();

		Map.EndTurn();

		Map.PrintMap();
		
		EndGame = Map.CheckForEndConditions();
		EndGame = Map.ShowMenu();
		if (EndGame)
		{
			break;
		}
	}

	system("pause");
    return 0;
}


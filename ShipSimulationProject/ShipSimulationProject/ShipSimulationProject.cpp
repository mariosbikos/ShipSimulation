// ShipSimulationProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "OceanMap.h"
#include "GridPoint.h"

int main()
{
	OceanMap Map;
	Map.Init();
	std::cout << GridPoint::NumOfPorts;
	while (true)
	{
		Map.PrintMap();
		Map.ShowMenu();
		//Start Turn

		//Move phase

		//Action phase 

		//End Turn Phase

		//EndSimulation?
		break;
		
	}


	Map.Terminate();


	system("pause");
    return 0;
}


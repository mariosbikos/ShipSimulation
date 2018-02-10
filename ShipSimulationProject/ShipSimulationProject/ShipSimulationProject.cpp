// ShipSimulationProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "OceanMap.h"

int main()
{
	OceanMap Map;
	Map.Init();

	while (true)
	{
		Map.PrintMap();
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


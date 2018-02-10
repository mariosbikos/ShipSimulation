// ShipSimulationProject.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include "OceanMap.h"

int main()
{
	OceanMap Map;
	Map.Init();

	
	Map.Terminate();
	system("pause");
    return 0;
}


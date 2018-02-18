#include "ExplorationShip.h"
#include "ShipSimulationProject/Ships/Ship.h"
#include "ShipSimulationProject/HelperFunctions.h"
#include "ShipSimulationProject/GridPoint.h"
#include "ShipSimulationProject/Coordinates.h"
#include "ShipSimulationProject/Ships/PirateShip.h"
#include <algorithm>

int ExplorationShip::ExplorationShipID;

ExplorationShip::ExplorationShip()
{
	ExplorationShipID++;
	this->Name = "E" + HelperFunctions::ShipIDToString(ExplorationShipID);
}

ExplorationShip::~ExplorationShip()
{
	ExplorationShipID--;
}

void ExplorationShip::DoAction()
{
	//Check if pirate ship or bad weather conditions in neighborhood+move to opposite direction!
	vector<MoveDirection> NeighborDirectionsToMoveAwayFrom;
	for (GridPoint* NeighborPoint : ShipGridPoint->GetNeighborPoints())
	{
		Ship* NeighborShip = NeighborPoint->GetShipOnPoint();
		if ( (NeighborShip && dynamic_cast<PirateShip*>(NeighborShip)) || NeighborPoint->HasBadWeatherConditions())
		{
			NeighborDirectionsToMoveAwayFrom.push_back(Position2D::GetMoveDirectionForPositionVector(NeighborPoint->GetCoordinates() - ShipGridPoint->GetCoordinates()));
		}
	}

	if (NeighborDirectionsToMoveAwayFrom.size() == 0 || NeighborDirectionsToMoveAwayFrom.size() == NumOfDirections)
	{
		//No need to move
		return;
	}


	MoveDirection DirectionToMove;
	switch (NeighborDirectionsToMoveAwayFrom.size())
	{
	case 1:
		DirectionToMove = Position2D::GetOppositeDirection(NeighborDirectionsToMoveAwayFrom[0]);
		break;
	case 2:
		DirectionToMove = Position2D::GetOppositeDirection(NeighborDirectionsToMoveAwayFrom[HelperFunctions::GetRandomIntWithinRange(0, 1)]);
		break;
	case 3:
		if (std::find(NeighborDirectionsToMoveAwayFrom.begin(), NeighborDirectionsToMoveAwayFrom.end(), MoveDirection::NORTH) == NeighborDirectionsToMoveAwayFrom.end())
		{
			DirectionToMove = MoveDirection::NORTH;
			break;
		}
		if (std::find(NeighborDirectionsToMoveAwayFrom.begin(), NeighborDirectionsToMoveAwayFrom.end(), MoveDirection::EAST) == NeighborDirectionsToMoveAwayFrom.end())
		{
			DirectionToMove = MoveDirection::EAST;
			break;
		}
		if (std::find(NeighborDirectionsToMoveAwayFrom.begin(), NeighborDirectionsToMoveAwayFrom.end(), MoveDirection::WEST) == NeighborDirectionsToMoveAwayFrom.end())
		{
			DirectionToMove = MoveDirection::WEST;
			break;
		}
		if (std::find(NeighborDirectionsToMoveAwayFrom.begin(), NeighborDirectionsToMoveAwayFrom.end(), MoveDirection::SOUTH) == NeighborDirectionsToMoveAwayFrom.end())
		{
			DirectionToMove = MoveDirection::SOUTH;
			break;
		}
		break;
	default:
		break;
	}

	
	MoveToAvoidEnemies(DirectionToMove);
	
}

void ExplorationShip::MoveToAvoidEnemies(MoveDirection Direction)
{
	Position2D NewPosition = ShipGridPoint->GetCoordinates().GetPointAfterMovingToDirection(Direction, Speed);
	cout << "Ship: " << *this << " will try to avoid enemies by moving" << endl;
	MoveToNewPosition(NewPosition);
}


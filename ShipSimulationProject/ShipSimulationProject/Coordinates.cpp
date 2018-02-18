#include "Coordinates.h"
#include "OceanMap.h"
#include <iostream>


ostream& operator<<(ostream &strm, const Position2D &a)
{
	return strm << "(" << a.X << "," << a.Y << ")";
}

const Position2D operator+(const Position2D& CurrentPosition, const Position2D& OtherPosition)
{
	return Position2D(CurrentPosition.X + OtherPosition.X, CurrentPosition.Y + OtherPosition.Y);
}


const Position2D operator-(const Position2D& CurrentPosition, const Position2D& OtherPosition)
{
	return Position2D(CurrentPosition.X - OtherPosition.X, CurrentPosition.Y - OtherPosition.Y);
}

Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition)
{
	return Position2D(CurrentPosition.X*ScalarValue, CurrentPosition.Y *ScalarValue);
}

Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue)
{
	return ScalarValue*CurrentPosition;
}


const bool operator==(const Position2D& CurrentPosition, const Position2D& OtherPosition)
{
	return (CurrentPosition.X == OtherPosition.X && CurrentPosition.Y == OtherPosition.Y);
}

MoveDirection Position2D::GetMoveDirectionForPositionVector(Position2D PositionVector)
{
	if (PositionVector.X > 0)
	{
		return MoveDirection::SOUTH;
	}
	if (PositionVector.X < 0)
	{
		return MoveDirection::NORTH;
	}
	if (PositionVector.Y > 0)
	{
		return MoveDirection::EAST;
	}
	if (PositionVector.Y < 0)
	{
		return MoveDirection::WEST;
	}
}

Position2D Position2D::UP()
{
	return Position2D(-1, 0);
}

Position2D Position2D::DOWN()
{
	return Position2D(1,0);
}

Position2D Position2D::LEFT()
{
	return Position2D(0, -1);
}

Position2D Position2D::RIGHT()
{
	return Position2D(0 , 1);
}

MoveDirection Position2D::GetOppositeDirection(const MoveDirection Direction)
{
	return MoveDirection((Direction + 2) % MoveDirection::NumOfDirections);
}

Position2D Position2D::GetPointAfterMovingToDirection( const MoveDirection Direction, const int Speed) const
{
	Position2D NewPosition;

	switch (Direction)
	{
	case MoveDirection::NORTH:
		NewPosition = *this + Position2D::UP()*Speed;
		break;
	case MoveDirection::EAST:
		NewPosition = *this + Position2D::RIGHT()*Speed;
		break;
	case MoveDirection::WEST:
		NewPosition = *this + Position2D::LEFT()*Speed;
		break;
	case MoveDirection::SOUTH:
		NewPosition = *this + Position2D::LEFT()*Speed;
		break;
	default:
		break;
	}

	return NewPosition;
}

bool Position2D::AreCoordinatesValidOnMap() const
{
	return X >= 0 && X < OceanMap::NumRows && Y >= 0 && Y < OceanMap::NumCols;
		
}


#pragma once
#include <iostream>
#include <string>

using namespace std;

enum MoveDirection
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	NumOfDirections
};

struct Position2D
{
	Position2D(int InX =0, int InY=0)
		:X(InX), Y(InY) {}


	int X;
	int Y;

	friend const Position2D operator+(const Position2D& CurrentPosition, const Position2D& OtherPosition);
	friend const Position2D operator-(const Position2D& CurrentPosition, const Position2D& OtherPosition);
	friend Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue);
	friend Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition);
	friend const bool operator==(const Position2D& CurrentPosition, const Position2D& OtherPosition);

	static MoveDirection GetMoveDirectionForPositionVector(Position2D PositionVector);
	static Position2D UP();
	static Position2D DOWN();
	static Position2D LEFT();
	static Position2D RIGHT();
	static MoveDirection GetOppositeDirection(const MoveDirection Direction);
	friend ostream& operator<<(ostream &strm, const Position2D &a);

	Position2D GetPointAfterMovingToDirection(const MoveDirection Direction, const int Speed) const;

	bool AreCoordinatesValidOnMap() const;
};

const Position2D operator+(const Position2D& CurrentPosition, const Position2D& OtherPosition);
const Position2D operator-(const Position2D& CurrentPosition, const Position2D& OtherPosition);
Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue);
Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition);
const bool operator==(const Position2D& CurrentPosition, const Position2D& OtherPosition);
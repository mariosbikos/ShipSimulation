#pragma once
#include <iostream>
#include <string>

using namespace std;

enum MoveDirection
{
	NORTH,
	EAST,
	WEST,
	SOUTH,
	NumOfDirections
};

struct Position2D
{
	Position2D(int InX, int InY)
		:X(InX), Y(InY) {}


	int X;
	int Y;

	friend Position2D operator+(Position2D& CurrentPosition, const Position2D& OtherPosition);
	friend Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue);
	friend Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition);

	static Position2D UP();
	static Position2D DOWN();
	static Position2D LEFT();
	static Position2D RIGHT();
	friend ostream& operator<<(ostream &strm, const Position2D &a);
};

Position2D operator+(Position2D& CurrentPosition, const Position2D& OtherPosition);
Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue);
Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition);
#pragma once
#include <iostream>
#include <string>

using namespace std;

struct Position2D
{
	Position2D(int InX, int InY)
		:X(InX), Y(InY) {}


	int X;
	int Y;

	friend ostream& operator<<(ostream &strm, const Position2D &a);
};


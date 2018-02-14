#include "Coordinates.h"
#include <iostream>


ostream& operator<<(ostream &strm, const Position2D &a)
{
	return strm << "(" << a.X << "," << a.Y << ")";
}

Position2D operator+(Position2D& CurrentPosition, const Position2D& OtherPosition)
{
	return Position2D(CurrentPosition.X + OtherPosition.X, CurrentPosition.Y + OtherPosition.Y);
}


Position2D operator*(const int& ScalarValue, Position2D& CurrentPosition)
{
	return Position2D(CurrentPosition.X*ScalarValue, CurrentPosition.Y *ScalarValue);
}

Position2D operator*(Position2D& CurrentPosition, const int& ScalarValue)
{
	return ScalarValue*CurrentPosition;
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


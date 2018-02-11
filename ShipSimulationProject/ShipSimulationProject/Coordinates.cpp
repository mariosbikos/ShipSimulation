#include "Coordinates.h"
#include <iostream>


ostream& operator<<(ostream &strm, const Position2D &a)
{
	return strm << "(" << a.X << "," << a.Y << ")";
}
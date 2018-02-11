#include "HelperFunctions.h"
#include <sstream>
#include <iomanip>
#include <random>

int HelperFunctions::Convert2DIndexTo1DIndex(const int Row, const int Col,const int NumCols)
{
	return Col + NumCols*Row;
}

void HelperFunctions::Convert1DIndexTo2DIndex(const int Index,const int NumCols, int& OutRow, int& OutCol)
{
	OutRow = Index / NumCols;
	OutCol = Index % NumCols;
}

int HelperFunctions::GetRandomIntWithinRange(const int Min, const int Max)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::uniform_int_distribution<> distr(Min, Max); // define the range

	return distr(eng);
}

std::string HelperFunctions::ShipIDToString(const int ID)
{
	std::stringstream ss;
	ss << std::setw(2) << std::setfill('0') << ID;
	return ss.str();
}


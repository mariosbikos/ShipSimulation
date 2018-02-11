#pragma once
#include <string>

class HelperFunctions
{
public:
	static int Convert2DIndexTo1DIndex(const int Row, const int Col,const int NumCols);
	static void Convert1DIndexTo2DIndex(const int Index, const int NumCols, int& OutRow, int& OutCol);

	static int GetRandomIntWithinRange(const int Min, const int Max);
	static float GetRandomFloatWithinRange(const float Min, const float Max);
	static std::string ShipIDToString(const int ID);
};
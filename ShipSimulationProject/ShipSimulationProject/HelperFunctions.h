#pragma once

class HelperFunctions
{
public:
	static int Convert2DIndexTo1DIndex(const int Row, const int Col,const int NumCols);
	static void Convert1DIndexTo2DIndex(const int Index, const int NumCols, int& OutRow, int& OutCol);
};
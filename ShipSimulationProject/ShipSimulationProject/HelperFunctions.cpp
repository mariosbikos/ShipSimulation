#include "HelperFunctions.h"

int HelperFunctions::Convert2DIndexTo1DIndex(const int Row, const int Col,const int NumCols)
{
	return Col + NumCols*Row;
}

void HelperFunctions::Convert1DIndexTo2DIndex(const int Index,const int NumCols, int& OutRow, int& OutCol)
{
	OutRow = Index / NumCols;
	OutCol = Index % NumCols;
}


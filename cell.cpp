#include "cell.h"


Cell::Cell(int x, int y)
{
	xy.xPos = x;
	xy.yPos = y;
}

struct coordinates Cell::getCoordinates()
{
	return this->xy;
}
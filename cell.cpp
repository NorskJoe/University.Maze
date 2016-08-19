#include "cell.h"


Cell::Cell(int x, int y)
{
	xy.xPos = x;
	xy.yPos = y;
}

struct coordinates Cell::getCell()
{
	return this->xy;
}

/*Cell * getOtherCell(Cell * cell)
{
	if(cell.)
}*/
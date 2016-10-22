
#include "cell.h"

Cell::Cell(int x, int y)
{
	xy.xPos = x;
	xy.yPos = y;
	visited = false;
}

struct coordinates Cell::getCoordinates()
{
	return this->xy;
}

void Cell::setNeighbourCell(Cell * cell)
{
	this->neighbourCells.push_back(cell);
}

const std::vector<Cell *>& Cell::getNeighbourCells()
{
	return neighbourCells;
}
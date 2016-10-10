
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

void Cell::setNeighbour(Edge neighbour)
{
	this->neighbours.push_back(neighbour);
}

void Cell::setNeighbourCell(Cell * cell)
{
	this->neighbourCells.push_back(cell);
}
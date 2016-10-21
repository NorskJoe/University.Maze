#ifndef CELL_H
#define CELL_H

#include <vector>
#include "edge.h"

/* Used to hold the position of a cell */
struct coordinates
{
	int xPos, yPos;
};


class Cell
{
private:
	struct coordinates xy;
	bool visited;
	std::vector<Cell *> neighbourCells;
public:
	/* Constructors */
	Cell() :
		xy()	
	{};
	Cell(int x, int y);
	
	/* Functions */
	struct coordinates getCoordinates();
	bool isVisited() { return visited; }

	void setNeighbourCell(Cell * cell);
	void setVisited() { this->visited = true; }
	void setNotVisited() { this->visited = false; }

	std::vector<Cell *> getNeighbourCells() { return neighbourCells; }
};

#endif // CELL_H
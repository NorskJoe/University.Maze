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
	std::vector<Edge> neighbours;
public:
	/* Constructors */
	Cell() :
		xy()	
	{};
	Cell(int x, int y);
	
	/* Functions */
	struct coordinates getCoordinates();
	bool isVisited() { return visited; }

	void setNeighbour(Edge neighbour);
	void setVisited() { this->visited = true; }
	void setNotVisited() { this->visited = false; }

	std::vector<Edge> getNeighbours() { return neighbours; }
	int getNeighbourCount() { return this->neighbours.size(); }
};

#endif // CELL_H
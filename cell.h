#ifndef CELL_H
#define CELL_H

#include <vector>

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
	std::vector<Cell*> neighbours;
public:
	/* Constructors */
	Cell() :
		xy()
	{};
	Cell(int x, int y);
	
	/* Functions */
	struct coordinates getCoordinates();
	bool isVisited() { return visited; }

	void setNeighbour(Cell * neighbour) { neighbours.push_back(neighbour); }
	void setVisited() { this->visited = true; }
	void setNotVisited() { this->visited = false; }

	std::vector<Cell*> getNeighbours() { return neighbours; }
};

#endif // CELL_H
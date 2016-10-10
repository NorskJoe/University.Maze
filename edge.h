#ifndef EDGE_H
#define EDGE_H

//#include "cell.h"

class Cell;

class Edge
{
private:
	Cell * cell1, * cell2;
	bool isPathway;
	bool isVisited;

public:
	/* Constructors */
	Edge(Cell * cell1, Cell * cell2): cell1(cell1), cell2(cell2), isPathway(false), isVisited(false) {};

	/* Functions */
	bool isSolved() { return isPathway; }
	void setSolvedPathway() { isPathway = true; }

	Cell * getCellOne() { return cell1; }
	Cell * getCellTwo() { return cell2; }
	Cell * getNeighbouringCell(Cell * cell);

	bool checkVisited() { return isVisited; }
	void setVisited() { isVisited = true; }
};

#endif
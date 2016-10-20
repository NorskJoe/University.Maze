#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "mazeSolver.h"

#define COST_OF_MOVING_CELL 1

class DijkstraSolver: public MazeSolver
{
public:
	/* Constructor */
	DijkstraSolver();

	/* Functions */
	void solveMaze(Maze&);
	/* virtual function, will be implemented differently depending on
	cost heuristic */
	virtual int heuristicEstimate(Maze& maze, Cell * cell) = 0;
};

#endif
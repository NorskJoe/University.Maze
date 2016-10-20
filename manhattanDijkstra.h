#ifndef MANHATTAN_DIJKSTRA_H
#define MANHATTAN_DIJKSTRA_H

#include "dijkstraSolver.h"

class DijkstraManhattan: public DijkstraSolver
{
public:
	/* Constructor */
	DijkstraManhattan();

	/* Functions */
	int heuristicEstimate(Maze& maze, Cell * cell);
};

#endif
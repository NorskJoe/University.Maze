#ifndef MANHATTAN_DIJKSTRA_H
#define MANHATTAN_DIJKSTRA_H

#include "mazeSolver.h"

#define COST_OF_MOVING_CELL 1

class DijkstraManhattanSolver: public MazeSolver
{
public:
	/* Constructor */
	DijkstraManhattanSolver();

	/* Functions */
	void solveMaze(Maze&);
	int heuristicEstimate(Maze& maze, Cell * cell);
};

#endif
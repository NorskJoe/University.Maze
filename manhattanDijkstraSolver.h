#ifndef MANHATTAN_DIJKSTRA_H
#define MANHATTAN_DIJKSTRA_H

#include "mazeSolver.h"

class DijkstraManhattanSolver: public MazeSolver
{
public:
	/* Constructor */
	DijkstraManhattanSolver();

	/* Functions */
	void solveMaze(Maze&, vector<Edge>&);
};

#endif
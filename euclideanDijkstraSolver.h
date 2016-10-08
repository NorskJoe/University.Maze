#ifndef EUCLIDEAN_DIJKSTRA_H
#define EUCLIDEAN_DIJKSTRA_H

#include "mazeSolver.h"

class DijkstraEuclideanSolver: public MazeSolver
{
public:
	/* Constructor */
	DijkstraEuclideanSolver();

	/* Functions */
	void solveMaze(Maze&, vector<Edge>&);
};

#endif
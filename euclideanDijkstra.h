#ifndef EUCLIDEAN_DIJKSTRA_H
#define EUCLIDEAN_DIJKSTRA_H

#include "dijkstraSolver.h"

class DijkstraEuclidean: public DijkstraSolver
{
public:
	/* Constructor */
	DijkstraEuclidean();

	/* Functions */
	int heuristicEstimate(Maze& maze, Cell * cell);
};

#endif
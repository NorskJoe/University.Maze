/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
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
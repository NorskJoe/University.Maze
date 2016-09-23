#ifndef BFS_H
#define BFS_H

#include "mazeSolver.h"

class DepthFirstSearchSolver: public MazeSolver
{
public:
	/* Constructor */
	DepthFirstSearchSolver();

	/* Functions */
	void solveMaze(Maze&, vector<edge>&);
};

#endif
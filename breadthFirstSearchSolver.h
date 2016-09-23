#ifndef DFS_H
#define DFS_H

#include "mazeSolver.h"

class BreadthFirstSearchSolver: public MazeSolver
{
public:
	/* Constructor */
	BreadthFirstSearchSolver();

	/* Functions */
	void solveMaze(Maze&, vector<edge>&);
};

#endif
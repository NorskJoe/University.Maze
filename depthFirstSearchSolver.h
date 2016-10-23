/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#ifndef BFS_H
#define BFS_H

#include "mazeSolver.h"

class DepthFirstSearchSolver: public MazeSolver
{
public:
	/* Constructor */
	DepthFirstSearchSolver();

	/* Functions */
	void solveMaze(Maze&);
};

#endif
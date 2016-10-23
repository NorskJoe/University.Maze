/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/

#ifndef DFS_H
#define DFS_H

#include "mazeSolver.h"

class BreadthFirstSearchSolver: public MazeSolver
{
public:
	/* Constructor */
	BreadthFirstSearchSolver();

	/* Functions */
	void solveMaze(Maze&);
};

#endif
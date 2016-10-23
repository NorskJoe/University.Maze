/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include "mazeSolver.h"
#include "breadthFirstSearchSolver.h"
#include "depthFirstSearchSolver.h"
#include "euclideanDijkstra.h"
#include "manhattanDijkstra.h"

/* Constructor */
MazeSolver::MazeSolver()
{
	
}

/***************************************************************************** 
	Function that implements the factory method.  Returns a maze solver
	object of the correct type

	mazeType - the type of maze solver requested by user via cmd line
	
******************************************************************************/
MazeSolver* MazeSolver::getSolver(int solverType)
{
	if(solverType == DFS)
	{
		return new DepthFirstSearchSolver;
	}
	else if(solverType == BFS)
	{
		return new BreadthFirstSearchSolver;
	}
	else if(solverType == DIJKSTRA_MANHATTAN)
	{
		return new DijkstraManhattan;
	}
	else /* DIJKSTRA_EUCLIDEAN */
	{
		return new DijkstraEuclidean;
	}
}

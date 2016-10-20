#include "mazeSolver.h"
#include "breadthFirstSearchSolver.h"
#include "depthFirstSearchSolver.h"
#include "euclideanDijkstra.h"
#include "manhattanDijkstra.h"

/* Constructor */
MazeSolver::MazeSolver()
{
	
}

/* Factory method will return the appropriate generator object for making a maze */
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

#include <vector>

#include "mazeSolver.h"
#include "breadthFirstSearchSolver.h"
#include "depthFirstSearchSolver.h"
#include "euclideanDijkstraSolver.h"
#include "manhattanDijkstraSolver.h"

using namespace std;

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
		return new DijkstraManhattanSolver;
	}
	else /* DIJKSTRA_EUCLIDEAN */
	{
		return new DijkstraEuclideanSolver;
	}
}

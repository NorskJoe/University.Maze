#include <vector>

#include "mazeGenerator.h"
#include "aldousBroderGenerator.h"
#include "ellersGenerator.h"
#include "depthFirstSearchSolver.h"
#include "breadthFirstSearchSolver.h"
#include "manhattanDijkstraSolver.h"
#include "euclideanDijkstraSolver.h"


/* Constructor */
MazeGenerator::MazeGenerator()
{
	
}

/* Factory method will return the appropriate generator object for making a maze */
MazeGenerator* MazeGenerator::getGenerator(int mazeType)
{
	if(mazeType == ALDOUS_BRODER)
	{
		return new AldousBroderGenerator;
	}
	else
	{
		return new EllersGenerator;
	}
}

void MazeGenerator::addNewEdge(vector<Edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(Edge(currentCell, nextCell));

	currentCell->setNeighbour(edges[edgeCount]);
	nextCell->setNeighbour(edges[edgeCount]);

	currentCell->setNeighbourCell(nextCell);
	nextCell->setNeighbourCell(currentCell);

	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}
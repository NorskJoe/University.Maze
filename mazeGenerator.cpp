#include <vector>

#include "mazeGenerator.h"
#include "aldousBroderGenerator.h"
#include "ellersGenerator.h"
#include "depthFirstSearchSolver.h"
#include "breadthFirstSearchSolver.h"
#include "manhattanDijkstraSolver.h"
#include "euclideanDijkstraSolver.h"

using namespace std;

/* Constructor */
MazeGenerator::MazeGenerator()
{
	
}

/* Factory method will return the appropriate generator object for making a maze */
MazeGenerator MazeGenerator::getGenerator(int mazeType)
{
	if(mazeType == ALDOUS_BRODER)
	{
		return AldousBroderGenerator();
	}
	else
	{
		return EllersGenerator();
	}
}

/* Method signature for derived generator classes */
void MazeGenerator::makeMaze(Maze& maze, vector<edge>& edges)
{

}

/* Adds the currentCell and nextCell to the edge structure */
void MazeGenerator::addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(edge());
	edges[edgeCount].cell1 = currentCell;
	edges[edgeCount].cell2 = nextCell;
	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}
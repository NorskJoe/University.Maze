#include <vector>

#include "mazeGenerator.h"

//#include "edge.h"

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


/* Adds the currentCell and nextCell to the edge structure and add the appropriate neighbours to each cell */
/*void MazeGenerator::addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(edge());
	edges[edgeCount].cell1 = currentCell;
	edges[edgeCount].cell2 = nextCell;
	currentCell->setNeighbour(nextCell);
	nextCell->setNeighbour(currentCell);
	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}*/

void MazeGenerator::addNewEdge(vector<Edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(Edge(currentCell, nextCell));
	//edges[edgeCount].cell1 = currentCell;
	//edges[edgeCount].cell2 = nextCell;
	//currentCell->setNeighbour(&edges[edges.size()-1]);
	//nextCell->setNeighbour(&edges[edges.size()-1]);
	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}
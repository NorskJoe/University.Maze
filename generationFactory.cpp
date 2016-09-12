#include <random>
#include <vector>

#include "generationFactory.h"
#include "aldousBroderGenerator.h"

using namespace std;

/* Constructor */
GenerationFactory::GenerationFactory(int w, int h, int s)
{
	width = w;
	height = h;
	seed = s;
}


void GenerationFactory::makeMaze(vector<edge>& edges, Maze& maze, int mazeType)
{
	if(mazeType == 1)
	{
		AldousBroderGenerator generator;
		generator.makeMaze(edges, maze);
	}
}

/* Adds the currentCell and nextCell to the edge structure */
void GenerationFactory::addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(edge());
	edges[edgeCount].cell1 = currentCell;
	edges[edgeCount].cell2 = nextCell;
	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}
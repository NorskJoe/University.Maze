#include <vector>

//remove later
#include <iostream>

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
	// /* DEBUGGING */
	// cout << "current edge: " << currentCell->getCoordinates().xPos << "," <<currentCell->getCoordinates().yPos << " - " << nextCell->getCoordinates().xPos << "," << nextCell->getCoordinates().yPos <<  endl;


	edges.push_back(Edge(currentCell, nextCell));

	currentCell->setNeighbour(edges[edgeCount]);
	nextCell->setNeighbour(edges[edgeCount]);

	currentCell->setNeighbourCell(nextCell);
	nextCell->setNeighbourCell(currentCell);

	nextCell->setVisited();
	remainingCells--;
	edgeCount++;

	/* DEBUGGING */
	// cout << "adding cell1 neighbour pathways: " << endl;
	// for(Edge neighbour : currentCell->getNeighbours())
	// {
	// 	Cell * cell1 = neighbour.getCellOne();
	// 	Cell * cell2 = neighbour.getCellTwo();

	// 	cout << cell1->getCoordinates().xPos << "," << cell1->getCoordinates().yPos << " - " << cell2->getCoordinates().xPos << "," << cell2->getCoordinates().yPos <<  endl;
	// }

	// cout << "adding cell2 neighbour pathways: " << endl;
	// for(Edge neighbour : nextCell->getNeighbours())
	// {
	// 	Cell * cell1 = neighbour.getCellOne();
	// 	Cell * cell2 = neighbour.getCellTwo();

	// 	cout << cell1->getCoordinates().xPos << "," << cell1->getCoordinates().yPos << " - " << cell2->getCoordinates().xPos << "," << cell2->getCoordinates().yPos <<  endl;
	// }
}
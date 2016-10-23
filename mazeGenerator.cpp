/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <vector>

#include "mazeGenerator.h"
#include "aldousBroderGenerator.h"
#include "ellersGenerator.h"

/* Constructor */
MazeGenerator::MazeGenerator()
{
	
}

/***************************************************************************** 
	Function that implements the factory method.  Returns a maze generator
	object of the correct type

	mazeType - the type of maze generator requested by user via cmd line
	
******************************************************************************/
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

void MazeGenerator::addNewEdge(vector<Edge>& edges, int& edgeCount, 
	Cell * currentCell, Cell * nextCell)
{
	edges.push_back(Edge(currentCell, nextCell));

	currentCell->setNeighbourCell(nextCell);
	nextCell->setNeighbourCell(currentCell);

	nextCell->setVisited();

	edgeCount++;
}
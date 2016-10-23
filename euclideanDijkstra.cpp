/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <cmath>

#include "euclideanDijkstra.h"

using namespace std;

/* Constructor */
DijkstraEuclidean::DijkstraEuclidean()
{

}

/***************************************************************************** 
	Function returns a heuristic estimate using Euclidean Cost

	maze - the maze object
	cell - the cell the estimate is based on
	
******************************************************************************/
int DijkstraEuclidean::heuristicEstimate(Maze& maze, Cell * cell)
{	
	int x = maze.getWidth() - cell->getCoordinates().xPos-1;
	int y = maze.getHeight() - cell->getCoordinates().yPos-1;
	return (int)sqrt((x*x) + (y*y));
}
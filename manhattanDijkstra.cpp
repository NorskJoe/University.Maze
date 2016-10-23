/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include "manhattanDijkstra.h"

/* Constructor */
DijkstraManhattan::DijkstraManhattan()
{

}

/***************************************************************************** 
	Function returns a heuristic estimate using Manhattan Cost

	maze - the maze object
	cell - the cell the estimate is based on
	
******************************************************************************/
int DijkstraManhattan::heuristicEstimate(Maze& maze, Cell * cell)
{
	return (maze.getWidth() - cell->getCoordinates().xPos-1)  + 
		(maze.getHeight() - cell->getCoordinates().yPos-1);
}
/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/

#include <random>
#include <iostream>

#include "aldousBroderGenerator.h"

using namespace std;

/* Constructor for making the generator object */
AldousBroderGenerator::AldousBroderGenerator()
{
	
}

/***************************************************************************** 
	Function that generates a new maze

	maze - the maze object
	gen - a seeded random number generator
	edges - a vector of edges that represents pathways in the maze
	
	Implemented using the Aldous-Broder algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2011/1/17/maze-
	generation-aldous-broder-algorithm

******************************************************************************/
void AldousBroderGenerator::makeMaze(Maze& maze, mt19937& gen, 
	vector<Edge>& edges)
{
	int totalCells, remainingCells, edgeCount=0, xPos, yPos;
	int width = maze.getWidth();
	int height = maze.getHeight();

	totalCells = width * height;
	Cell * currentCell, * nextCell;
	nextCell = nullptr;
	vector< vector<Cell *> > cells = maze.getMaze();

	/* Choose a random vertex to start generation */
	xPos = gen() % width-1;
	yPos = gen() % height-1;
	currentCell = maze.getCell(xPos,yPos);
	currentCell->setVisited();
	remainingCells = totalCells - 1;

	const int east_westMovement[] = { 0, 1, 0, -1 };
	const int north_southMovement[] = { 1, 0, -1, 0 };

	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		int nextX, nextY, random;

		/* Get a random adjacent cell.
			validMove used to keep nextCell within the maze bounds */
		xPos = currentCell->getCoordinates().xPos;
		yPos = currentCell->getCoordinates().yPos;

		/* Get the next random direction. 0-3 */
		random = gen() % DIRECTION_COUNT;

		nextX = xPos + east_westMovement[random];
		nextY = yPos + north_southMovement[random];
		/* Check next cell is within bounds */
		if(maze.existsInMaze(nextX, nextY))
		{
			nextCell = cells[nextX][nextY];
			/* Check next cell is unvisited */
			if(nextCell->isVisited() == false)
			{
				/* Add currentCell and nextCell to edge structure */
				addNewEdge(edges, edgeCount, currentCell, nextCell);
				remainingCells--;
			}
		}
		currentCell = nextCell;
	}

	maze.setEdgeCount(edgeCount);
	maze.setEdges(edges);
}
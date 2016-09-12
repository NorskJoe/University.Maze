#include <random>
#include <iostream>

#include "aldousBroderGenerator.h"

using namespace std;

/* Implemented using the Aldous-Broder algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm */
AldousBroderGenerator::AldousBroderGenerator(int w, int h)
{
	cout << "in aldousBroderGenerator constructor" << endl;
	width = w;
	height = h;
}

void AldousBroderGenerator::makeMaze(vector<edge>& edges, Maze& maze)
{

	int totalCells, remainingCells, edgeCount=0, xPos, yPos;
	int width = maze.getWidth();
	int height = maze.getHeight();
	int seed = maze.getSeed();

	totalCells = width * height;
	Cell * currentCell, * nextCell;
	vector< vector<Cell *> > cells = maze.getMaze();

	/* Get number generator */
	mt19937 mt(seed);
	/* Choose a random vertex to start generation */
	xPos = mt() % width;
	yPos = mt() % height;
	currentCell = maze.getCell(xPos,yPos);
	currentCell->setVisited();
	remainingCells = totalCells - 1;

	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		int nextX, nextY, random;

		/* Get a random adjacent cell.
			validMove used to keep nextCell within the maze bounds */
		bool validMove = false;
		while(validMove == false)
		{	
			xPos = currentCell->getCoordinates().xPos;
			yPos = currentCell->getCoordinates().yPos;

			/* Get the next random direction. 0-3 */
			random = mt() % NUMBER_OF_DIRECTIONS;

			if(random == NORTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_NORTH;
				/* Check next cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					validMove = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is unvisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						maze.addNewEdge(edges, edgeCount, remainingCells, currentCell, nextCell);
					}

				}
			}

			else if(random == EAST)
			{
				nextX = xPos + MOVE_EAST;
				nextY = yPos;
				/* Check cell is within bounds */
				if(nextX >= 0 && nextX < width)
				{
					validMove = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						maze.addNewEdge(edges, edgeCount, remainingCells, currentCell, nextCell);
					}
				}
			}

			else if(random == SOUTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_SOUTH;
				/* Check cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					validMove = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						maze.addNewEdge(edges, edgeCount, remainingCells, currentCell, nextCell);
					}
				}
			}

			else if(random == WEST)
			{
				nextX = xPos + MOVE_WEST;
				nextY = yPos;
				/* Check cell is within bounds */
				if(nextX >= 0 && nextX < width)
				{
					validMove = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						maze.addNewEdge(edges, edgeCount, remainingCells, currentCell, nextCell);
					}
				}
			}
		}
		currentCell = nextCell;
		validMove = false;
	}
	maze.setEdgeCount(edgeCount);
	maze.setEdges(edges);
}
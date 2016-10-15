#include <random>
#include <iostream>

#include "aldousBroderGenerator.h"

using namespace std;

/* Constructor for making the generator object */
AldousBroderGenerator::AldousBroderGenerator()
{
	
}

/* Implemented using the Aldous-Broder algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm */
void AldousBroderGenerator::makeMaze(Maze& maze, mt19937& gen, vector<Edge>& edges)
{
	int totalCells, remainingCells, edgeCount=0, xPos, yPos;
	int width = maze.getWidth();
	int height = maze.getHeight();

	totalCells = width * height;
	Cell * currentCell, * nextCell;
	vector< vector<Cell *> > cells = maze.getMaze();

	/* Choose a random vertex to start generation */
	xPos = gen() % width;
	yPos = gen() % height;
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
			random = gen() % NUMBER_OF_DIRECTIONS;

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
						addNewEdge(edges, edgeCount, currentCell, nextCell);
						remainingCells--;
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
						addNewEdge(edges, edgeCount, currentCell, nextCell);
						remainingCells--;
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
						addNewEdge(edges, edgeCount, currentCell, nextCell);
						remainingCells--;
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
						addNewEdge(edges, edgeCount, currentCell, nextCell);
						remainingCells--;
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
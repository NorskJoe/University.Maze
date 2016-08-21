#include <iostream>
#include <random>
#include <functional>
#include <chrono>
#include <cstdlib>

#include "mazeGenerator.h"

using namespace std;

/* Constructor */
mazeGenerator::mazeGenerator(int w, int h, int s)
{
	width = w;
	height = h;
	seed = s;
}

/* Implemented using the Aldous-Broder algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm */
Maze mazeGenerator::makeMaze(vector<edge>& edges)
{
	int totalCells, remainingCells, edgeCount, xPos, yPos;

	Maze maze(width, height);
	totalCells = width * height;
	Cell * currentCell, * nextCell;
	vector< vector<Cell *> > cells = maze.getAllCells();

	/* Get number generator */
	mt19937 mt(seed);
	/* Choose a random vertex to start generation */
	xPos = mt() % width;
	yPos = mt() % height;
	currentCell = maze.getCell(xPos,yPos);
	currentCell->setVisited();
	remainingCells = totalCells - 1;

	cout << "starting cell is: " << xPos << ", " << yPos << endl;

	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		int nextX, nextY, random;

		/* Get a random adjacent cell */
		while(nextCell == NULL)
		{	
			xPos = currentCell->getCell().xPos;
			yPos = currentCell->getCell().yPos;

			random = mt() % NUMBER_OF_DIRECTIONS;
			cout << "random is: " << random << endl;

			if(random == NORTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_NORTH;
				/* Check next cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					nextCell = cells[nextX][nextY];
					/* Check next cell is unvisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
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
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
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
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
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
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
					}
				}
			}
		}

		currentCell = nextCell;
		nextCell = NULL;
	}

	maze.setEdgeCount(edgeCount);
	maze.setEdges(edges);

/*	cout << "GENERATED: " << endl;
	for(vector<edge>::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		cout << it->cell1->getCell().xPos << ", ";
		cout << it->cell1->getCell().yPos << "-  ";
		cout << it->cell2->getCell().xPos << ", ";
		cout << it->cell2->getCell().yPos << endl;
	}*/

	return maze;
}


void mazeGenerator::setSeed(int s)
{
	this->seed = s;
}
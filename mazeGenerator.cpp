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
	int totalCells, remainingCells;

	Maze maze(width, height);
	totalCells = width * height;
	Cell * currentCell, * nextCell;
	vector< vector<Cell *> > cells = maze.getAllCells();

	/* Assuming position 0,0 is starting point */
	currentCell = maze.getCell(0,0);
	currentCell->setVisited();
	remainingCells = totalCells - 1;

	/* Setting up seed */
	mt19937::result_type seed = time(nullptr);


	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		int xPos, yPos, nextX, nextY, counter;

		/* Get a random, adjacent, unvisited cell */
		while(nextCell == NULL)
		{	
			xPos = currentCell->getCell().xPos;
			yPos = currentCell->getCell().yPos;
			/* Seeding based on time */
			auto random = bind(uniform_int_distribution<int>(1,4), mt19937(seed));

			cout << "in while(nextCell==NULL)" << endl;
			cout << "random number is: " << random() << endl;

			if(random() == NORTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_NORTH;
				/* Check next cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					/* Check next cell is unvisited */
					if(cells[nextX][nextY]->isVisited() == false)
					{
						//successful
						nextCell = cells[nextX][nextY];
					}

				}
			}

			else if(random() == EAST)
			{
				nextX = xPos + MOVE_EAST;
				nextY = yPos;
				if(nextX >= 0 && nextX < width)
				{
					if(cells[nextX][nextY]->isVisited() == false)
					{
						//succesful
						nextCell = cells[nextX][nextY];
					}
				}
			}

			else if(random() == SOUTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_SOUTH;
				if(nextY >= 0 && nextY < height)
				{
					if(cells[nextX][nextY]->isVisited() == false)
					{
						//succesful
						nextCell = cells[nextX][nextY];
					}
				}
			}

			else if(random() == WEST)
			{
				nextX = xPos + MOVE_WEST;
				nextY = yPos;
				if(nextX >= 0 && nextX < width)
				{
					if(cells[nextX][nextY]->isVisited() == false)
					{
						//succesful
						nextCell = cells[nextX][nextY];
					}
				}
			}
		}

		edges.push_back(edge());
		edges[counter].cell1 = currentCell;
		edges[counter].cell2 = nextCell;

		counter++;
		remainingCells--;
		nextCell->setVisited();
		currentCell = nextCell;
		nextCell = NULL;

		cout << "remainingCells: " << remainingCells <<endl;
	}

	return maze;
}

#include <iostream>
#include <random>
#include <functional>

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

	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		/* Seeding based on time */
		mt19937::result_type seed = time(0);
		auto random = bind(uniform_int_distribution<int>(1,4), mt19937(seed));
		int xPos, yPos, counter;
		xPos = currentCell->getCell().xPos;
		yPos = currentCell->getCell().yPos;

		/* Get a random, adjacent, unvisited cell */
		while(nextCell == NULL)
		{	
			cout << "in while(nextCell==NULL)" << endl;
			cout << "random number is: " << random() << endl;
			if(random() == NORTH)
			{
				if(cells[xPos][yPos + MOVE_NORTH] == NULL || cells[xPos][yPos + MOVE_NORTH]->isVisited() == true)
				{

				}
				else
				{
					nextCell = cells[xPos][yPos + MOVE_NORTH];
				}
			}

			else if(random() == EAST)
			{
				if(cells[xPos + MOVE_EAST][yPos] == NULL || cells[xPos + MOVE_EAST][yPos]->isVisited() == true)
				{

				}
				else
				{
					nextCell = cells[xPos + MOVE_EAST][yPos];
				}
			}

			else if(random() == SOUTH)
			{
				if(cells[xPos][yPos + MOVE_SOUTH] == NULL || cells[xPos][yPos + MOVE_SOUTH]->isVisited() == true)
				{

				}
				else
				{
					nextCell = cells[xPos][yPos + MOVE_SOUTH];
				}
			}

			else if(random() == WEST)
			{
				if(cells[xPos + MOVE_WEST][yPos] == NULL || cells[xPos + MOVE_WEST][yPos]->isVisited() == true)
				{

				}
				else
				{
					nextCell = cells[xPos + MOVE_WEST][yPos];
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

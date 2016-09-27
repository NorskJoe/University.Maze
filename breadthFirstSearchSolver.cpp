#include <queue>
#include <unordered_set>
#include <iostream>

#include "breadthFirstSearchSolver.h"

using namespace std;

/* Constructor */
BreadthFirstSearchSolver::BreadthFirstSearchSolver()
{

}

void BreadthFirstSearchSolver::solveMaze(Maze& maze, vector<edge>& edges)
{
	/* Setting up local variables */
	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(maze.getWidth()-1, maze.getHeight()-1);
	Cell * currentCell = nullptr;
	Cell * nextCell = nullptr;
	/* Setting up local data structures */
	queue<Cell *> cellQueue;
	unordered_set<Cell *> visistedCells;
	vector< vector<Cell *> > cells = maze.getMaze();

	/* Set all the cells as unvisited to begin the algorithm */
	for(int i = 0; i < maze.getWidth(); i ++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			Cell * cell = maze.getCell(i, j);
			cell->setNotVisited();
		}
	}

	/* MAIN BODY OF ALGORITHM */
	/* Start by pushing first cell to queue */
	cellQueue.push(startCell);

	while(cellQueue.empty() == false)
	{
		/* Get the next cell in the queue */
		currentCell = cellQueue.front();
		cellQueue.pop();

		if(currentCell == endCell)
		{
			/* Found a complete path to the end */
			cout << "compelted pathway" << endl;

		}
		/* ERROR HERE, NOT CHECKING IF NEXT CELL IS PART OF AN EDGE */

		else
		{
			int x, y;
			x = currentCell->getCoordinates().xPos;
			y = currentCell->getCoordinates().yPos;
			cout << "current cell: x, y: " << x << ", " << y << endl;

			/* Check north movement */
			if(x >= 0 && y+1 <= maze.getHeight())
			{
				cout << "north cell" << endl;
				nextCell = cells[x][y+1];
				/* Check nextCell has not been visited */
				if(!nextCell->isVisited())
				{
					cellQueue.push(nextCell);
					nextCell->setVisited();
				}
				else
				{
					nextCell = nullptr;
				}
			}
			/* Check east movement */
			if(x+1 <= maze.getWidth() && y >= 0)
			{
				cout << "east cell" << endl;
				nextCell = cells[x+1][y];
				/* Check nextCell has not been visited */
				if(!nextCell->isVisited())
				{
					cellQueue.push(nextCell);
					nextCell->setVisited();
				}
				else
				{
					nextCell = nullptr;
				}
			}
			/* Check south movement */
			if(x >= 0 && y-1 >= maze.getHeight())
			{
				cout << "south cell" << endl;
				nextCell = cells[x][y-1];
				/* Check nextCell has not been visited */
				if(!nextCell->isVisited())
				{
					cellQueue.push(nextCell);
					nextCell->setVisited();
				}
				else
				{
					nextCell = nullptr;
				}
			}
			/* Check west movement */
			if(x-1 >= maze.getWidth() && y >= 0)
			{
				cout << "west cell" << endl;
				nextCell = cells[x-1][y];
				/* Check nextCell has not been visited */
				if(!nextCell->isVisited())
				{
					cellQueue.push(nextCell);
					nextCell->setVisited();
				}
				else
				{
					nextCell = nullptr;
				}
			}
			nextCell = nullptr;

		}
	}
}
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <iostream>
#include <algorithm>

#include "breadthFirstSearchSolver.h"

using namespace std;

/* Constructor */
BreadthFirstSearchSolver::BreadthFirstSearchSolver()
{

}

void BreadthFirstSearchSolver::solveMaze(Maze& maze)
{
	/* Setting up local variables */
	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(maze.getWidth()-1, maze.getHeight()-1);
	Cell * currentCell = nullptr;
	/* Setting up local data structures */
	queue<Cell *> cellQueue;
	//unordered_set<Cell *> visistedCells;

	/* Set all cells in the maze as invisited */
	for(int i = 0; i < maze.getWidth(); i ++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			Cell * cell = maze.getCell(i,j);
			cell->setNotVisited();
		}
	}
	

	int x, y;

	/* MAIN BODY OF ALGORITHM */
	/* Start by pushing first cell to queue */
	cellQueue.push(startCell);
	startCell->setVisited();

	int count = 0;

	while(count < 10)
	{
		/* Get the next cell in the queue */
		currentCell = cellQueue.front();
		cellQueue.pop();
		x = currentCell->getCoordinates().xPos;
		y = currentCell->getCoordinates().yPos;
		cout << "current cell is: " << y << "," << x << endl;

		if(currentCell == endCell)
		{
			/* Found a complete path to the end */
			cout << "The maze has been solved!" << endl;
			break;
		}

		else
		{ 
			/* For each of the current cells neighbours, add it to the queue, 
			and mark it visited */
			for(Cell * neighbour : currentCell->getNeighbourCells())
			{
				if(!neighbour->isVisited())
				{
					cellQueue.push(neighbour);
					neighbour->setVisited();
					x = neighbour->getCoordinates().xPos;
					y = neighbour->getCoordinates().yPos;
					cout << "pushed: " << y << "," << x << endl;
				}
			}

			count++;

		}
	}

	cout << "cellQueue contains: " << endl;
	for(unsigned i = 0; i < cellQueue.size(); i++)
	{
		Cell * cell = cellQueue.front();
		cellQueue.pop();
		x = cell->getCoordinates().xPos;
		y = cell->getCoordinates().yPos;
		cout << y << "," << x << endl;
	}
		
}
#include <queue>
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
	int maxNumberOfPathways = maze.getWidth() * maze.getHeight();
	int checkedPathways = 0;
	/* Setting up local data structures */
	queue<Cell *> cellQueue;
	unordered_map<Cell *, Cell *> cellMap;
	cellMap.reserve(maxNumberOfPathways);

	/* Set all cells in the maze as unvisited */
	for(int i = 0; i < maze.getWidth(); i ++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			Cell * cell = maze.getCell(i,j);
			cell->setNotVisited();
		}
	}

	/* MAIN BODY OF ALGORITHM */
	/* Start by pushing first cell to queue and pathway stack */
	cellQueue.push(startCell);
	startCell->setVisited();

	while(currentCell != endCell)
	{
		/* Get the next cell in the queue */
		currentCell = cellQueue.front();
		cellQueue.pop();

		if(currentCell == endCell)
		{
			/* Found a complete path to the end */
			break;
		}

		if(checkedPathways > maxNumberOfPathways)
		{
			//error
			cout << "This maze cannot be solved." << endl;
			return;
		}

		else
		{ 
			/* For each of the current cells neighbours, add it to the queue, 
			 mark it visited, and add to cell map for solving */
			for(Cell * neighbour : currentCell->getNeighbourCells())
			{
				if(!neighbour->isVisited())
				{
					cellQueue.push(neighbour);
					cellMap[neighbour] = currentCell;
					neighbour->setVisited();
					checkedPathways++;
				}
			}
		}
	}


	/* Start at end of map, work backwards through key-values to 
	build solved pathway */
	currentCell = endCell;	
	unordered_map<Cell *, Cell *>::const_iterator nextCell;
	while(currentCell != startCell)
	{
		nextCell = cellMap.find(currentCell);
		maze.addPathway((Edge(currentCell, nextCell->second)));
		currentCell = nextCell->second;
		
	}
		
}
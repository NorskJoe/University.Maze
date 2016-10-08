#include <queue>
#include <unordered_set>
#include <iostream>
#include <algorithm>

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
	/* Setting up local data structures */
	queue<Cell *> cellQueue;
	unordered_set<Cell *> visistedCells;
	vector< vector<Cell *> > cells = maze.getMaze();

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
			cout << "size of pathway: " << visistedCells.size() << endl;
			break;
		}

		else
		{
			/* For each of the current cells neighbours, add it to the queue, and mark it visited */
			for(Cell* neighbour : currentCell->getNeighbours())
			{
				cout << "neighbour is: " <<  neighbour->getCoordinates().xPos << "," << neighbour->getCoordinates().yPos << endl;
				cellQueue.push(neighbour);
				visistedCells.insert(neighbour);
			}

		}
	}
}
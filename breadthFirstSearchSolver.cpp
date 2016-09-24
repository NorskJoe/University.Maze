#include <queue>
#include <unordered_set>

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

	/* Set all the cells as unvisited to begin the algorithm */
	for(int i = 0; i < maze.getWidth(); i ++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			Cell * cell = maze.getCell(i, j);
			cell->setVisited();
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

		}

		else
		{
			
		}
	}
}
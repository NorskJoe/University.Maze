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

void BreadthFirstSearchSolver::solveMaze(Maze& maze, vector<Edge>& edges)
{
	/* Setting up local variables */
	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(maze.getWidth()-1, maze.getHeight()-1);
	Cell * currentCell = nullptr;
	/* Setting up local data structures */
	queue<Cell *> cellQueue;
	unordered_set<Cell *> visistedCells;
	

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
			cout << "The maze has been solved!" << endl;
			break;
		}

		else
		{ 
			/* For each of the current cells neighbours, add it to the queue, and mark it visited */
			for(Cell* neighbour : currentCell->getNeighbours())
			{
				/* Checks to see if neighbour has already been visited */
				if(visistedCells.find(neighbour) == visistedCells.end())
				{
					cellQueue.push(neighbour);
					visistedCells.insert(neighbour);

					/* Find the associated edge in the maze, mark it as part of a pathway */
					/*for(unsigned i = 0; i < edges.size(); i++)
					{
						if(edges[i].cell1 == currentCell && edges[i].cell2 == neighbour)
						{
							edges[i].isPathway = true;
						}
						else if(edges[i].cell1 == neighbour && edges[i].cell2 == currentCell)
						{
							edges[i].isPathway = true;
						}
					}*/
				}
			}
		}
	}
			maze.setEdges(edges);
}
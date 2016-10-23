/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <iostream>
#include <unordered_set>
#include <stack>


#include "depthFirstSearchSolver.h"

using namespace std;

/* Constructor */
DepthFirstSearchSolver::DepthFirstSearchSolver()
{

}

/***************************************************************************** 
	Function that solves a maze

	maze - the maze object
	
******************************************************************************/
void DepthFirstSearchSolver::solveMaze(Maze& maze)
{
	/* Setting up local variables/objects */
	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(maze.getWidth()-1, maze.getHeight()-1);
	Cell * currentCell = nullptr;
	vector<Edge> pathways;

	/* Setting up local data structures
		cellStack: used to keep track of solution
	*/
	stack<Cell*> cellStack;

	/* Set all cells as unvisited */
	for(int i = 0; i < maze.getWidth(); i++)
	{
		for(int j = 0; j < maze.getHeight(); j++)
		{
			Cell * cell = maze.getCell(i,j);
			cell->setNotVisited();
		}
	}

	cellStack.push(startCell);

	/* Main body of algorithm */
	bool foundValidNeighbour;
	while(currentCell != endCell)
	{
		currentCell = cellStack.top();
		currentCell->setVisited();

		if(currentCell == nullptr)
		{
			/* Maze cannot be solved */
			cout << "This maze cannot be solved." << endl;
			return;
		}

		/* Get all neighbouring cells */
		for( Cell * neighbour : currentCell->getNeighbourCells() )
		{
			foundValidNeighbour = false;

			/* If neighbour has not been visited, 'move' to it */
			if(!neighbour->isVisited())
			{
				cellStack.push(neighbour);
				foundValidNeighbour = true;
				break;
			}
		}
		
		/* If no unvisited neighbour found, backtrace by one cell */
		if(!foundValidNeighbour)
		{
			cellStack.pop();
		}
	}

	/* Now add cell pathway to maze object. Trace through maze solution
	backwards */
	/* First push last cell onto stack */
	cellStack.push(endCell);
	for (int i = cellStack.size(); cellStack.size() != 1; i--)
	{
		Cell * cell1 = cellStack.top();
		cellStack.pop();
		Cell * cell2 = cellStack.top();

		maze.addPathway(Edge(cell1,cell2));
	}
}
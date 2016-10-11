//remove later
#include <iostream>
#include <unordered_set>
#include <stack>


#include "depthFirstSearchSolver.h"

using namespace std;

/* Constructor */
DepthFirstSearchSolver::DepthFirstSearchSolver()
{

}

void DepthFirstSearchSolver::solveMaze(Maze& maze)
{
	/* Setting up local variables/objects */
	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(maze.getWidth()-1, maze.getHeight()-1);
	Cell * currentCell = nullptr;
	vector<Edge> pathways;

	/* Setting up local data structures
		cellStack: used to keep track of visited cells
		pathwayStack: used to keep track of pathway
		pathwaySet: used to keep track of visisted pathways
	*/
	stack<Cell*> cellStack;
	stack<Edge*> pathwayStack;

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
			cout << "error" << endl;
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

	/* Now add cell pathway to maze object as vector of edges */
	/* First push last cell onto stack */
	cellStack.push(endCell);
	/* Go through stack, adding two cells to Edge at a time */
	for (int i = cellStack.size(); cellStack.size() != 1; i--)
	{
		Cell * cell1 = cellStack.top();
		cellStack.pop();
		Cell * cell2 = cellStack.top();


		maze.addPathway(Edge(cell1,cell2));

	}

	// pathways = maze.getPathways();

	// cout << "contents of maze pathways: " << endl;
	// for(int i = 0; i < pathways.size(); i++)
	// {
	// 	int x, y;
	// 	x = pathways[i].getCellOne()->getCoordinates().xPos;
	// 	y = pathways[i].getCellOne()->getCoordinates().yPos;
	// 	cout << y << "," << x <<  " - ";

	// 	x = pathways[i].getCellTwo()->getCoordinates().xPos;
	// 	y = pathways[i].getCellTwo()->getCoordinates().yPos;

	// 	cout << y << "," << x << endl;
	// }
}
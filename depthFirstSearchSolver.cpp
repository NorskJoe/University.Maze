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

void DepthFirstSearchSolver::solveMaze(Maze& maze, vector<Edge>& edges)
{
	cout << "Solving with DFS" << endl;

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
	//unordered_set<Edge*> pathwaySet;

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
	bool foundPathway;
	bool foundValidNeighbour;
	int count = 0;
	while(currentCell != endCell)
	{
		currentCell = cellStack.top();
		currentCell->setVisited();
		

		if(currentCell == nullptr)
		{
			//error
			cout << "error" << endl;
		}


			int count = 0;

		for( Cell * neighbour : currentCell->getNeighbourCells() )
		{
			foundValidNeighbour = false;
			int x, y;

			if(!neighbour->isVisited())
			{
				x = neighbour->getCoordinates().xPos;
				y = neighbour->getCoordinates().yPos;
				cellStack.push(neighbour);

				foundValidNeighbour = true;
				count++;
				break;
			}

		}
		
		if(!foundValidNeighbour)
		{
			int x, y;
			Cell * cell = cellStack.top();
			x = cell->getCoordinates().xPos;
			y = cell->getCoordinates().yPos;
			cellStack.pop();
		}

	}



	/* Now add cell pathway to maze object as vector of edges */
	/* First push last cell onto stack */
	cellStack.push(endCell);


	/* DEBUGGING */
	// cout << "stack contains: " << endl;
	// for(int i = cellStack.size(); cellStack.size()!=0; i--)
	// {
	// 	Cell * cell = cellStack.top();
	// 	cellStack.pop();
	// 	int x, y;

	// 	x = cell->getCoordinates().xPos;
	// 	y = cell->getCoordinates().yPos;

	// 	cout << y << "," << x << endl;

	// }


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
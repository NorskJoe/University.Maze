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
		
		cout <<  "stack size: " << cellStack.size() << endl;


		//DEBUGGING
		cout << "currentCell: " << currentCell->getCoordinates().yPos << "," << currentCell->getCoordinates().xPos << endl;
		//cout << "endCell: " << endCell->getCoordinates().xPos << "," << endCell->getCoordinates().yPos << endl;
		//

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


			if(count == 0)
			{
				cout << "neighbours are: " << endl;
				for( Cell * ngh : currentCell->getNeighbourCells() )
				{
					x = ngh->getCoordinates().xPos;
					y = ngh->getCoordinates().yPos;
					cout << y << "," << x << endl;
				}
				count++;
			}

			if(!neighbour->isVisited())
			{
				x = neighbour->getCoordinates().xPos;
				y = neighbour->getCoordinates().yPos;
				cellStack.push(neighbour);
				cout << "pushed: " << y << "," << x << endl << endl;;

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
			cout << "popped: " << y << "," << x << endl << endl;
		}




		//cout << "currentCells neighbour count: " << currentCell->getNeighbourCount() << endl;

		// for( Edge pathway : currentCell->getNeighbours() )
		// {
		// 	foundPathway = false;

		// 	cout << "currentCell nghbr count: " << currentCell->getNeighbourCount() << endl;

		// 	cout << "currentCell neighours: " << endl;
		// 	for( Edge path : currentCell->getNeighbours() )
		// 	{

		// 		cout << path.getCellOne()->getCoordinates().xPos << "," << path.getCellOne()->getCoordinates().yPos << " - " << path.getCellTwo()->getCoordinates().xPos << "," << path.getCellTwo()->getCoordinates().yPos << endl;
		// 	}

		// 	/* If pathway has not been visisted */
		// 	//if(pathwaySet.find(&pathway) == pathwaySet.end())
		// 	//{
		// 	if(pathway.checkVisited() == false)
		// 	{

		// 		//pathwaySet.insert(&pathway);
		// 		pathwayStack.push(&pathway);
		// 		pathway.setVisited();

		// 		/* Add neighouring cells to stack */
		// 		cellStack.push(pathway.getNeighbouringCell(currentCell));

		// 		//DEBUGGING
		// 		Cell * pushed = pathway.getNeighbouringCell(currentCell);
		// 		cout << "pushed: " << pushed->getCoordinates().xPos << "," << pushed->getCoordinates().yPos << endl;
		// 		//


		// 		cout << "found a pathway" << endl << endl;
		// 		foundPathway = true;
		// 		count++;
		// 		break;
		// 	//}
		// 	}
		// }

		// if(!foundPathway)
		// {
		// 	/* Reached dead end, no unvisited neighbours */
		// 	if(currentCell == endCell)
		// 	{
		// 		break;
		// 	}
		// 	else
		// 	{
		// 		pathwayStack.pop();
		// 		cellStack.pop();
		// 		cout << "popped" << endl;
		// 	}
		// }

	}



	/* Now add cell pathway to maze object as vector of edges */
	/* First push last cell onto stack */
	cellStack.push(endCell);

	
	/* DEBUGGING */
	cout << "stack contains: " << endl;
	for(int i = cellStack.size(); cellStack.size()!=0; i--)
	{
		Cell * cell = cellStack.top();
		cellStack.pop();
		int x, y;

		x = cell->getCoordinates().xPos;
		y = cell->getCoordinates().yPos;

		cout << y << "," << x << endl;

	}


	/* Go through stack, adding two cells to Edge at a time */
	for (int i = cellStack.size(); cellStack.size() != 0; i--)
	{
		int x, y;
		Cell * cell1 = cellStack.top();
		cellStack.pop();
		Cell * cell2 = cellStack.top();
		cellStack.pop();

		maze.addPathway(Edge(cell1,cell2));
	}


	/* Go through pathwayStack and mark as solved */
	// while(pathwayStack.size() > 0)
	// {
	// 	pathwayStack.top()->setSolvedPathway();
	// 	pathwayStack.pop();
	// }
}
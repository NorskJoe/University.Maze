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

	//cout << "startCell: " << startCell->getCoordinates().xPos << "," << startCell->getCoordinates().yPos << endl;

	cellStack.push(startCell);

	/* Main body of algorithm */
	bool foundPathway;
	int count = 0;
	while(count < 5)
	{
		currentCell = cellStack.top();
		
		//cout <<  "stack size: " << cellStack.size() << endl;


		//DEBUGGING
		cout << "currentCell: " << currentCell->getCoordinates().xPos << "," << currentCell->getCoordinates().yPos << endl;
		cout << "endCell: " << endCell->getCoordinates().xPos << "," << endCell->getCoordinates().yPos << endl;
		//

		if(currentCell == nullptr)
		{
			//error
			cout << "error" << endl;
		}

		//cout << "currentCells neighbour count: " << currentCell->getNeighbourCount() << endl;

		for( Edge pathway : currentCell->getNeighbours() )
		{
			foundPathway = false;

			cout << "currentCell nghbr count: " << currentCell->getNeighbourCount() << endl;

			cout << "currentCell neighours: " << endl;
			for( Edge path : currentCell->getNeighbours() )
			{

				cout << path.getCellOne()->getCoordinates().xPos << "," << path.getCellOne()->getCoordinates().yPos << " - " << path.getCellTwo()->getCoordinates().xPos << "," << path.getCellTwo()->getCoordinates().yPos << endl;
			}

			/* If pathway has not been visisted */
			//if(pathwaySet.find(&pathway) == pathwaySet.end())
			//{
			if(pathway.checkVisited() == false)
			{

				//pathwaySet.insert(&pathway);
				pathwayStack.push(&pathway);
				pathway.setVisited();

				/* Add neighouring cells to stack */
				cellStack.push(pathway.getNeighbouringCell(currentCell));

				//DEBUGGING
				Cell * pushed = pathway.getNeighbouringCell(currentCell);
				cout << "pushed: " << pushed->getCoordinates().xPos << "," << pushed->getCoordinates().yPos << endl;
				//


				cout << "found a pathway" << endl << endl;
				foundPathway = true;
				count++;
				break;
			//}
			}
		}

		if(!foundPathway)
		{
			/* Reached dead end, no unvisited neighbours */
			if(currentCell == endCell)
			{
				break;
			}
			else
			{
				pathwayStack.pop();
				cellStack.pop();
				cout << "popped" << endl;
			}
		}

	}

	/* Go through pathwayStack and mark as solved */
	while(pathwayStack.size() > 0)
	{
		pathwayStack.top()->setSolvedPathway();
		pathwayStack.pop();
	}
}
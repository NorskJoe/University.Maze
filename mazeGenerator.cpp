#include <random>

#include "mazeGenerator.h"

using namespace std;

/* Constructor */
MazeGenerator::MazeGenerator(int w, int h, int s)
{
	width = w;
	height = h;
	seed = s;
}

/* Implemented using the Aldous-Broder algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2011/1/17/maze-generation-aldous-broder-algorithm */
Maze MazeGenerator::makeMaze(vector<edge>& edges)
{
	int totalCells, remainingCells, edgeCount=0, xPos, yPos;

	Maze maze(width, height);
	totalCells = width * height;
	Cell * currentCell, * nextCell;
	vector< vector<Cell *> > cells = maze.getMaze();

	/* Get number generator */
	mt19937 mt(seed);
	/* Choose a random vertex to start generation */
	xPos = mt() % width;
	yPos = mt() % height;
	currentCell = maze.getCell(xPos,yPos);
	currentCell->setVisited();
	remainingCells = totalCells - 1;

	/* Main body of algorithm */
	while(remainingCells > 0)
	{
		int nextX, nextY, random;

		/* Get a random adjacent cell.
			flag used to keep nextCell within the maze bounds */
		bool flag = false;
		while(flag == false)
		{	
			xPos = currentCell->getCoordinates().xPos;
			yPos = currentCell->getCoordinates().yPos;

			/* Get the next random direction 0-3 */
			random = mt() % NUMBER_OF_DIRECTIONS;

			if(random == NORTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_NORTH;
				/* Check next cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					flag = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is unvisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
					}

				}
			}

			else if(random == EAST)
			{
				nextX = xPos + MOVE_EAST;
				nextY = yPos;
				/* Check cell is within bounds */
				if(nextX >= 0 && nextX < width)
				{
					flag = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
					}
				}
			}

			else if(random == SOUTH)
			{
				nextX = xPos;
				nextY = yPos + MOVE_SOUTH;
				/* Check cell is within bounds */
				if(nextY >= 0 && nextY < height)
				{
					flag = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
					}
				}
			}

			else if(random == WEST)
			{
				nextX = xPos + MOVE_WEST;
				nextY = yPos;
				/* Check cell is within bounds */
				if(nextX >= 0 && nextX < width)
				{
					flag = true;
					nextCell = cells[nextX][nextY];
					/* Check next cell is invisited */
					if(nextCell->isVisited() == false)
					{
						/* Add currentCell and nextCell to edge structure */
						edges.push_back(edge());
						edges[edgeCount].cell1 = currentCell;
						edges[edgeCount].cell2 = nextCell;
						nextCell->setVisited();
						remainingCells--;
						edgeCount++;
					}
				}
			}
		}
		currentCell = nextCell;
		flag = false;
	}
	maze.setEdgeCount(edgeCount);
	maze.setEdges(edges);

	return maze;
}

#include <vector>
#include <iostream>

#include "maze.h"
#include "aldousBroderGenerator.h"

using namespace std;

/* Initialise an empty maze of cells */
Maze::Maze(int h, int w, int count)
{
	height = h;
	width = w;
	edgeCount = count;

	for(int i = 0; i < height; i++)
	{
		/* Initialise rows based on height */
		vector<Cell *> currentRow;
		/* Initialise each cell/column in that row */
		for(int j = 0; j < width; j++)
		{
			Cell * newCell = new Cell(i, j);
			currentRow.push_back(newCell);
		}
		cells.push_back(currentRow);
	}
}

void Maze::makeMaze(vector<edge>& edges, Maze& maze, int mazeType)
{
	if(mazeType == ALDOUS_BRODER)
	{
		AldousBroderGenerator generator(maze.getWidth(), maze.getHeight());
		generator.makeMaze(edges, maze);
	}
}

/* Adds the currentCell and nextCell to the edge structure */
void Maze::addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell * currentCell, Cell * nextCell)
{
	edges.push_back(edge());
	edges[edgeCount].cell1 = currentCell;
	edges[edgeCount].cell2 = nextCell;
	nextCell->setVisited();
	remainingCells--;
	edgeCount++;
}

Cell * Maze::getCell(int x, int y)
{
	return cells[x][y];
}

void Maze::setEdgeCount(int count)
{
	edgeCount = count;
}

void Maze::setWidth(int w)
{
	width = w;
}

void Maze::setHeight(int h)
{
	height = h;
}

void Maze::setEdges(vector<edge>& newEdges)
{
	edges = newEdges;
}

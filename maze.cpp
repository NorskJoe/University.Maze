#include <vector>

#include "maze.h"


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

/* Getters and setters */
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

void Maze::setEdges(vector<Edge>& newEdges)
{
	edges = newEdges;
}


/* When given a cell, see if it has an adjacent cell as part of an edge/pathway */
/*Cell * Maze::getOtherCell(Cell * cell)
{
	unsigned i;
	for(i = 0; i < edges.size(); i++)
	{
		if(cell == edges[i].cell1)
		{
			return edges[i].cell2;
		}
		else if (cell == edges[i].cell2)
		{
			return edges[i].cell1;
		}
	}
	
	return nullptr;

}*/
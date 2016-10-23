/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <vector>

#include "maze.h"


using namespace std;

/***************************************************************************** 
	Function that initialises a maze of cells

	h - the new height of the maze
	w - the new width of the maze
	count - the number of edges that will exist in the maze
	
******************************************************************************/
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

/***************************************************************************** 
	Function that checks if a given cell is in the bounds of the maze

	x - the x position of the cell
	y - the y position of the cell
	
******************************************************************************/
bool Maze::existsInMaze(int x, int y)
{
	return (x >= 0 && x < width && y >= 0 && y < height);
}

/* Getters and setters */
Cell * Maze::getCell(int x, int y) const
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

void Maze::setPathways(vector<Edge>& newPathways)
{
	pathways = newPathways;
}
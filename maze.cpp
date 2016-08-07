#include "Maze.h"

/* Currently commented out because causing errors */
//Maze::Maze()
//{
//}

Maze::Maze(int h, int w, int edges)
{
	height = h;
	width = w;
	edgeCount = edges;
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


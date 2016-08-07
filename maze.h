/*
	The maze class declarations and definitions
*/

#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "edge.h"

using namespace std;

class Maze
{
private:
	int height, width, edgeCount;
	vector<Edge> edges;
public:
	/* Constructors */
	Maze() :
		height(0),
		width(0),
		edgeCount(0)
	{};
	Maze(int h, int w, int edges);

	/* Functions */
	int getHeight() { return height; }
	int getWidth() { return width; }
	int getEdgeCount() { return edgeCount; }
	
	void setEdgeCount(int count);
	void setWidth(int w);
	void setHeight(int h);
};

#endif // MAZE_H

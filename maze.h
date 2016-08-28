#ifndef MAZE_H
#define MAZE_H

#include <vector>
#include "cell.h"

using namespace std;

/* edge structure holds the two cells in the edge */
struct edge
{
	Cell * cell1;
	Cell * cell2;
};

class Maze
{
private:
	int height, width, edgeCount;
	vector<edge> edges;
	vector< vector<Cell *> > cells;
public:
	/* Constructors */
	Maze() :
		height(0),
		width(0),
		edgeCount(0)
	{};
	Maze(int, int, int=0);

	/* Functions */
	int getHeight() { return height; }
	int getWidth() { return width; }
	int getEdgeCount() { return edgeCount; }
	vector<edge> getEdges() { return edges; }
	Cell * getCell(int x, int y);
	vector< vector<Cell *> > getMaze() { return cells; }
	
	void setEdgeCount(int count);
	void setWidth(int w);
	void setHeight(int h);
	void setEdges(vector<edge>&);

};

#endif
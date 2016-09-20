#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

using namespace std;

/* Definitions used for random direction choosing, and for traversing 
the maze grid */
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NUMBER_OF_DIRECTIONS 4
#define MOVE_NORTH 1
#define MOVE_SOUTH -1
#define MOVE_EAST 1
#define MOVE_WEST -1

/* edge structure holds the two cells in the edge */
struct edge
{
	Cell * cell1;
	Cell * cell2;
};

class Maze
{
protected:
	int height, width, edgeCount, seed;
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
	void makeMaze(vector<edge>& edges, Maze&, int mazeType);
	void solveMaze(int solveType);
	void addNewEdge(vector<edge>&, int&, int&, Cell*, Cell*);

	int getHeight() { return height; }
	int getWidth() { return width; }
	int getEdgeCount() { return edgeCount; }
	int getSeed() { return seed; }
	vector<edge> getEdges() { return edges; }
	Cell * getCell(int x, int y);
	vector< vector<Cell *> > getMaze() { return cells; }
	
	void setEdgeCount(int count);
	void setWidth(int w);
	void setHeight(int h);
	void setEdges(vector<edge>&);

};

#endif
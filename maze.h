/* Maze class */

#ifndef MAZE_H
#define MAZE_H

#include "cell.h"

using namespace std;


/*struct edge
{
	unsigned x1, x2, y1, y2;
};*/

struct pathway
{
	Cell * cell1;
	Cell * cell2;
};

class Maze
{
private:
	int height, width, edgeCount;
	//vector<edge> edges;
	vector<pathway> path;
	vector< vector<Cell *> > cells;
public:
	/* Constructors */
	Maze() :
		height(0),
		width(0),
		edgeCount(0)
	{};
	Maze(int, int, int);

	/* Functions */
	int getHeight() { return height; }
	int getWidth() { return width; }
	int getEdgeCount() { return edgeCount; }
	//vector<edge> getEdges() { return edges; }
	vector<pathway> getPaths() { return path; }
	Cell * getCell(int x, int y);
	
	// Maze generateMaze(int w, int h, int edgeCount, int seed);
	// Maze generateMaze(int w, int h, int edgeCount, vector<edge>&);
	void setEdgeCount(int count);
	void setWidth(int w);
	void setHeight(int h);
	//void setEdges(vector<edge>&);
	void setPath(vector<pathway>&);

};

#endif
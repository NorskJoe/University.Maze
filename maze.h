/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#ifndef MAZE_H
#define MAZE_H

#include "cell.h"
#include "edge.h"

using namespace std;

class Maze
{
protected:
	int height, width, edgeCount;
	unsigned long seed;
	vector<Edge> edges;
	vector<Edge> pathways;
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
	int getHeight() const { return height; }
	int getWidth() const { return width; }
	int getEdgeCount() const { return edgeCount; }
	unsigned long getSeed() const { return seed; }
	vector<Edge> getEdges() { return edges; }
	vector<Edge> getPathways() { return pathways; }
	vector< vector<Cell *> > getMaze() { return cells; }
	Cell * getCell(int x, int y) const;
	bool existsInMaze(int x, int y);

	void setEdgeCount(int count);
	void setSeed(unsigned long s) {this->seed = s; }
	void setWidth(int w);
	void setHeight(int h);
	void setEdges(vector<Edge>&);
	void setPathways(vector<Edge>&);
	void addPathway(Edge pathway) { this->pathways.push_back(pathway); }

};

#endif
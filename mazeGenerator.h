#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"

//using namespace std;

/* Definitions for generation methods.  Used to implement a factory pattern */
#define ALDOUS_BRODER 1
#define ELLERS 2


class MazeGenerator
{
public:
	/* Constructor */
	MazeGenerator();

	/* Functions*/
	static MazeGenerator* getGenerator(int);
	virtual void makeMaze(Maze& maze, vector<edge>& edges) = 0; 
	void addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell* currentCell, Cell* nextCell);
};

#endif
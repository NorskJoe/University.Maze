#ifndef MAZE_FACTORY_H
#define MAZE_FACTORY_H

#include <vector>

#include "maze.h"

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

class GenerationFactory
{
protected:
	int width, height, seed;
public:
    /* Constructor */
	GenerationFactory(int w, int h, int s);

	/* Functions */
	/* Factory method */
	void makeMaze(vector<edge>&, Maze&, int);
	void addNewEdge(vector<edge>&, int&, int&, Cell*, Cell*);
	
};

#endif
#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"

/* Definitions used for random direction choosing, and for traversing the maze grid */
#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NUMBER_OF_DIRECTIONS 4
#define MOVE_NORTH 1
#define MOVE_SOUTH -1
#define MOVE_EAST 1
#define MOVE_WEST -1

class MazeGenerator
{
private:
	int width, height, seed;
public:
    /* Constructor/Destructor */
	MazeGenerator(int w, int h, int s);
    //~MazeGenerator();

	/* Functions */
	Maze makeMaze(vector<edge>&);
	
};

#endif
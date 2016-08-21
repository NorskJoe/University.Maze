#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"

#define NORTH 0
#define SOUTH 1
#define EAST 2
#define WEST 3
#define NUMBER_OF_DIRECTIONS 4
#define MOVE_NORTH 1
#define MOVE_SOUTH -1
#define MOVE_EAST 1
#define MOVE_WEST -1

class mazeGenerator
{
private:
	int width, height, seed;
public:
	mazeGenerator(int w, int h, int s);

	/* Functions */
	Maze makeMaze(vector<edge>&);
	void setSeed(int);
	
};

#endif
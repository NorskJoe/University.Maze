#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"

#define NORTH 1
#define SOUTH 2
#define EAST 3
#define WEST 4
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
	
};

#endif
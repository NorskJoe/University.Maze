#ifndef ELLERS_H
#define ELLERS_H

#include "mazeGenerator.h"

class EllersGenerator: public MazeGenerator
{
public:
	/* Constructor */
	EllersGenerator();

	void makeMaze(Maze&, vector<edge>&);
};

#endif
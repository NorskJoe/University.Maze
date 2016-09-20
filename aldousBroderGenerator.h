#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include "mazeGenerator.h"

class AldousBroderGenerator: public MazeGenerator
{
public:
	/* Constructor */
	AldousBroderGenerator();

	void makeMaze(Maze&, vector<edge>&);
};

#endif
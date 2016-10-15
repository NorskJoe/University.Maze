#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include "mazeGenerator.h"

class AldousBroderGenerator: public MazeGenerator
{
public:
	/* Constructor */
	AldousBroderGenerator();

	void makeMaze(Maze&, mt19937&, vector<Edge>&);
};

#endif
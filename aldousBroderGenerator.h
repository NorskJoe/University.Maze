#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include "generationFactory.h"

class AldousBroderGenerator: public Maze
{
public:
	/* Constructor */
	AldousBroderGenerator(vector<edge>&, Maze&);

	Maze makeMaze();
};

#endif
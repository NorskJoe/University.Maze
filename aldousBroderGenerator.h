#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include <vector>

class AldousBroderGenerator: public Maze
{
public:
	/* Constructor */
	AldousBroderGenerator(int, int);

	void makeMaze(vector<edge>&, Maze&);
};

#endif
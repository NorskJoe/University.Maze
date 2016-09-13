#ifndef ELLERS_H
#define ELLERS_H

#include <vector>

class EllersGenerator: public Maze
{
public:
	/* Constructor */
	EllersGenerator(int, int);

	void makeMaze(vector<edge>&, Maze&);
};

#endif
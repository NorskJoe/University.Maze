#ifndef ELLERS_H
#define ELLERS_H

#include "mazeGenerator.h"

#define JOIN 0
#define NOT_JOIN 1
#define JOIN_CHOICE 2

class EllersGenerator: public MazeGenerator
{
public:
	/* Constructor */
	EllersGenerator();

	void makeMaze(Maze&, mt19937&, vector<Edge>&);
};

#endif
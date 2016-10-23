/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#ifndef ALDOUS_BRODER_H
#define ALDOUS_BRODER_H

#include "mazeGenerator.h"

enum direction
{
	NORTH,
	EAST,
	SOUTH,
	WEST,
	DIRECTION_COUNT
};

class AldousBroderGenerator: public MazeGenerator
{
public:
	/* Constructor */
	AldousBroderGenerator();

	void makeMaze(Maze&, mt19937&, vector<Edge>&);
};

#endif
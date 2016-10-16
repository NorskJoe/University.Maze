#ifndef ELLERS_H
#define ELLERS_H

#include <map>

#include "mazeGenerator.h"

#define JOIN 0
#define NOT_JOIN 1
#define JOIN_CHOICE 2

class EllersGenerator: public MazeGenerator
{
public:
	/* Constructor */
	EllersGenerator();

	/* Inherited function */
	void makeMaze(Maze&, mt19937&, vector<Edge>&);

	/* Other functions */
	void mergeCells(Cell *, Cell *, multimap<int, Cell *> &, 
		multimap<Cell *,int> &, vector<Edge>&, int&);
	int getRowSetCount(multimap<int, Cell *>&, multimap<Cell *, int>&, int, Maze&);
	int getNumberOfCellsInSet();
	void addNextRow(Maze&, int, int&, multimap<Cell *, int>&);
};

#endif
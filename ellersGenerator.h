#ifndef ELLERS_H
#define ELLERS_H

#include <map>

#include "mazeGenerator.h"

#define JOIN 0
#define NOT_JOIN 1
#define JOIN_CHOICE 2

class EllersGenerator: public MazeGenerator
{
private:

	/* Other functions */
	void mergeCells(Cell *, Cell *, multimap<Cell *,int> &, 
		vector<Edge>&, int&);
	int getRowSetCount(multimap<Cell *, int>&, int, Maze&);
	void addNextRow(mt19937&, Maze&, int, multimap<Cell *, int>&, 
		vector<Edge>&, int&, int&);
	int getCellCount(int, multimap<Cell *, int>, int);
public:
	/* Constructor */
	EllersGenerator();

	/* Inherited function */
	void makeMaze(Maze&, mt19937&, vector<Edge>&);

};

#endif


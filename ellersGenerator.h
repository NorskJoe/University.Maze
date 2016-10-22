#ifndef ELLERS_H
#define ELLERS_H

#include <map>

#include "mazeGenerator.h"

enum join
{
	JOIN,
	NOT_JOIN,

	JOIN_CHOICE

};

class EllersGenerator: public MazeGenerator
{
private:
	struct EllersCell
	{
		Cell * cell;
		int setNumber;
	};
	std::vector<vector<EllersCell>> cellMap;
	/* Functions */
	void mergeCells(Cell *, Cell *, multimap<Cell *,int> &, 
		vector<Edge>&, int&);
	int getRowSetCount(const multimap<Cell *,int>&, const int, const Maze&);
	void addNextRow(mt19937&, const Maze&, int, multimap<Cell *, int>&, 
		vector<Edge>&, int&, int&);
	int getCellCount(const int, const multimap<Cell *, int>, const int);
public:
	/* Constructor */
	EllersGenerator();

	/* Inherited function */
	void makeMaze(Maze&, mt19937&, vector<Edge>&);

};

#endif


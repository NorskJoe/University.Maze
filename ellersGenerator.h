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
	void mergeCells(Cell *, Cell *, multimap<Cell *,int> &, 
		vector<Edge>&, int&);
	int getRowSetCount(multimap<Cell *, int>&, int, Maze&);
	// void getInstancesOfSet(int, int&, multimap<Cell *, int>&);
	void addNextRow(mt19937&, Maze&, int, multimap<Cell *, int>&, 
		vector<Edge>&, int&, int&);
	//vector<Cell *> getCellsInSet(int, multimap<Cell *, int>);
	int getCellCount(int, multimap<Cell *, int>, int);
};

#endif




	// while(cellCount >= 2)
			// {
			// 	topCell = maze.getCell(col, row);
			// 	x = topCell->getCoordinates().xPos;
			// 	y = topCell->getCoordinates().yPos;
			// 	cout << "have second cell: " << row << "," << col << endl;
			// 	cout << "cell count iteration is: " << cellCount << endl;
			// 	cout << "cells added is: " << cellAdded << endl;

			// 	if(cellCount == 2 && !cellAdded)
			// 	{
			// 		cout << "joining last available cell" << endl;
			// 		Cell * bottomCell = maze.getCell(col, row+1);
			// 		mergeCells(topCell, bottomCell, c_to_sMap, edges, 
			// 			edgeCount);
			// 		cellCount--;
			// 		col++;
			// 		addedCells++;
			// 		cout << endl;
			// 		//break;
			// 	}

			// 	else if(gen() % JOIN_CHOICE == JOIN)
			// 	{
			// 		Cell * bottomCell = maze.getCell(col, row+1);
			// 		mergeCells(topCell, bottomCell, c_to_sMap, edges, 
			// 			edgeCount);
			// 		cellAdded = true;
			// 		addedCells++;
			// 		cellCount--;
			// 		col++;
			// 	}
			// 	else
			// 	{
			// 		cout << "didnt join" << endl;
			// 		col++;
			// 		cellCount--;
			// 	}
			// }
			// setCount--;
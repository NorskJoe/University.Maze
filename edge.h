/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#ifndef EDGE_H
#define EDGE_H

class Cell;

class Edge
{
private:
	Cell * cell1, * cell2;

public:
	/* Constructors */
	Edge(Cell * cell1, Cell * cell2): cell1(cell1), cell2(cell2) {};

	Cell * getCellOne() { return cell1; }
	Cell * getCellTwo() { return cell2; }
};

#endif
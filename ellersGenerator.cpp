/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <random>
#include <iostream>

#include <vector>
#include <map>
#include <algorithm>
#include <list>

#include "ellersGenerator.h"

using namespace std;

/* Constructor for making the generator object */
EllersGenerator::EllersGenerator()
{

}

/***************************************************************************** 
	Overidden function to generate a new maze.

	maze - main maze object
	gen - random number generator, already seeded
	edges - a vector of edges that represent pathways in maze

	Implemented using Ellers's algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2010/12/29/maze-
	generation-eller-s-algorithm 
******************************************************************************/
void EllersGenerator::makeMaze(Maze& maze, mt19937& gen, vector<Edge>& edges)
{
	int width, height, setNumber, edgeCount;

	width = maze.getWidth();
	height = maze.getHeight();
	edgeCount = 0;

	multimap<Cell *, int> cell_to_setMap;

	/* The number that will be used to add cells to a new set */
	setNumber = 1;
	/* Add all cells to a distinct set */
	for(int i = 0; i < width; i++)
	{
		Cell * cell = maze.getCell(i, 0);
		cell_to_setMap.insert(pair<Cell *, int>(cell, setNumber));

		setNumber++;
	}


	bool finalRow = false;
	bool firstRow = true;
	for(int i = 0; i < height; i++)
	{
		if(i == height-1)
		{
			finalRow = true;
		}
		if(i > 0 && firstRow)
		{
			firstRow = false;
		}

		/* Go through cells in row, deciding whether to join or not */
		for(int j = 0; j < width-1; j++)
		{
			/* For final row, join all adjacent cells in distinct sets */
			if(finalRow)
			{
				Cell * cell1 = maze.getCell(j, i);
				Cell * cell2 = maze.getCell(j+1, i);
				mergeCells(cell1, cell2, cell_to_setMap, 
					edges, edgeCount);
			}

			else
			{
				int choice = gen() % JOIN_CHOICE;

				if(choice == JOIN)
				{
					Cell * cell1 = maze.getCell(j, i);
					Cell * cell2 = maze.getCell(j+1, i);

					/* If the two cells are not already in the same set, 
					merge them into a single set */				
					mergeCells(cell1, cell2, cell_to_setMap,
						edges, edgeCount);
				}
			}
		}
		
		/* If reach final row, do not add neighbours from row below */
		if(!finalRow)
		{
			addNextRow(gen, maze, i, cell_to_setMap, 
				edges, edgeCount, setNumber);
		}

		/* Clear map data for previous row */
		if(!firstRow)
		{
			for(int j = 0; j < width; j++)
			{
				Cell * cell = maze.getCell(j, i-1);

				if(cell_to_setMap.find(cell) != cell_to_setMap.end())
				{
					cell_to_setMap.erase(cell);
				}

			}
		}

	}

	maze.setEdges(edges);
	maze.setEdgeCount(edgeCount);
}

/***************************************************************************** 
	Function to merge two adjacent cells together

	cell1 - first cell in edge
	cell2 - second cell in edge
	c_to_sMap - the map representing what set each cell is in
	edges - the list of edges in the maze
	edgeCount - the number of edges in the list

******************************************************************************/
void EllersGenerator::mergeCells(Cell * cell1, Cell * cell2, 
	multimap<Cell*,int> & c_to_sMap, vector<Edge>& edges, int& edgeCount)
{
	multimap<Cell *, int>::iterator c_to_sIt;

	/* First check that the two cells are not already in the same set */
	int setOne = -1, setTwo = -1;
	c_to_sIt = c_to_sMap.find(cell1);
	if(c_to_sIt != c_to_sMap.end())
	{
		setOne = c_to_sIt->second;
	}

	c_to_sIt = c_to_sMap.find(cell2);
	if(c_to_sIt != c_to_sMap.end())
	{
		setTwo = c_to_sIt->second;
	}

	if(setOne != setTwo)
	{
		/* Clear the unused elements in the map for efficiency */
		c_to_sMap.erase(cell1);
		c_to_sMap.erase(cell2);
		int setNumber = setOne;

		/* Find all other cells in set two, and change their set to set one
		for continuity */
		for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
		{
			if(it->second == setTwo)
			{
				it->second = setOne;
			}
		}
		
		addNewEdge(edges, edgeCount, cell1, cell2);

		/* Add the new elements to map, merge into cell1's set */
		c_to_sMap.insert(pair<Cell *, int>(cell1, setNumber));
		c_to_sMap.insert(pair<Cell *, int>(cell2, setNumber));

	}
}

/***************************************************************************** 
	Function that will return the number of distinct sets in a given row

	c_to_sMap - the map representing what set each cell is in
	rowNumber - the row that is being counted
	width - the width of the maze
 
******************************************************************************/
int EllersGenerator::getRowSetCount(const multimap<Cell *,int> & c_to_sMap, 
	const int rowNumber, const Maze& maze)
{
	int width = maze.getWidth();
	/* Maintain a list of already counted sets */
	list<int> countedSets;

	for(int i = 0; i < width; i++)
	{
		Cell * cell = maze.getCell(i, rowNumber);
		int set = c_to_sMap.find(cell)->second;

		/* Check to see if set is already in the list */
		if(find(countedSets.begin(), countedSets.end(), set) 
			== countedSets.end())
		{
			countedSets.push_back(set);
		}

	}

	return countedSets.size();
}

/***************************************************************************** 
	Function that will randomly add adjacent cells below the current row

	gen - the random number generator
	maze - the maze object
	row - the current row number
	c_to_sMap - the map representing what set each cell is in
	edges - the vector of edges in the maze
	edgeCount - the number of edges in the edge vector
	setNumber - the current setNumber being used to assign to new cells

******************************************************************************/
void EllersGenerator::addNextRow(mt19937& gen, const Maze& maze, int row, 
	multimap<Cell *, int> & c_to_sMap, vector<Edge>& edges, int& edgeCount, 
	int& setNumber)
{
	int width = maze.getWidth();
	int col = 0;

	int setCount = getRowSetCount(c_to_sMap, row, maze);

	while(setCount > 0)
	{
		Cell * topCell = maze.getCell(col, row);
		
		int setNumber = c_to_sMap.find(topCell)->second;
		int cellCount = getCellCount(setNumber, c_to_sMap, row);

		if(cellCount == 1)
		{
			Cell * bottomCell = maze.getCell(col, row+1);
			mergeCells(topCell, bottomCell, c_to_sMap, edges, edgeCount);
			setCount--;
			col++;
		}

		else
		{
			int cellsToJoin = gen() % cellCount;

			if(cellsToJoin == 0)
			{
				cellsToJoin = 1;
			}

			int difference = cellCount - cellsToJoin;

			while(cellsToJoin > 0)
			{
				/* Randomly decide to skip cell or not */
				int random = gen() % JOIN_CHOICE;
				if(cellsToJoin > 1)
				{
					if(random == NOT_JOIN)
					{	
						/* Skip the current cell, join the next instead */
						col++;
						Cell * topCell  = maze.getCell(col, row);
						Cell * bottomCell = maze.getCell(col, row+1);
						mergeCells(topCell, bottomCell, c_to_sMap, edges, 
							edgeCount);
						cellsToJoin--;
					}
				}
				else
				{
					Cell * topCell  = maze.getCell(col, row);
					Cell * bottomCell = maze.getCell(col, row+1);
					mergeCells(topCell, bottomCell, c_to_sMap, edges, 
						edgeCount);
					cellsToJoin--;
					col++;
				}
			}
			setCount--;
			col += difference;
		}
	}

	/* For any cells not already in a set, add to a new unique set */
	for(int i = 0; i < width; i++)
	{
		Cell * cell = maze.getCell(i, row+1);
		unsigned set = c_to_sMap.find(cell)->second;

		if(set > c_to_sMap.size() || set <= 0)
		{
			c_to_sMap.insert(pair<Cell *, int>(cell, setNumber));
			setNumber++;
		}
	}

}

/***************************************************************************** 
	Function that returns the number of cells in a given set and row

	currentSet - the current set number
	c_to_sMap - the map representing what set each cell is in
	row - the current row number

******************************************************************************/
int EllersGenerator::getCellCount(const int currentSet,
	const multimap<Cell *, int> c_to_sMap, const int row)
{
	int count = 0;

	for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
	{
		if(it->second == currentSet)
		{
			if(it->first->getCoordinates().yPos == row)
			{
				count++;
			}

		}
	}

	return count;
}
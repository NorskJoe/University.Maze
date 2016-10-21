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

/* Implemented using Ellers's algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2010/12/29/maze-
	generation-eller-s-algorithm */
void EllersGenerator::makeMaze(Maze& maze, mt19937& gen, vector<Edge>& edges)
{
	int width, height, setNumber, edgeCount;

	width = maze.getWidth();
	height = maze.getHeight();
	edgeCount = 0;

	multimap<Cell *, int> cell_to_setMap;

	setNumber = 1;
	/* Add all cells to a distinct set */
	for(int j = 0; j < width; j++)
	{
		Cell * cell = maze.getCell(j, 0);
		cell_to_setMap.insert(pair<Cell *, int>(cell, setNumber));

		setNumber++;

	}


	bool finalRow = false;
	for(int i = 0; i < height; i++)
	{
		if(i == height-1)
		{
			finalRow = true;
		}

		/* Go through cells in row, deciding whether to join or not */
		for(int j = 0; j < width-1; j++)
		{
			/* For final row, join all adjacent cells in distinct */
			if(finalRow)
			{
				Cell * cell1 = maze.getCell(j, i);
				Cell * cell2 = maze.getCell(j+1, i);
				mergeCells(cell1, cell2, cell_to_setMap, edges, edgeCount);
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
			addNextRow(gen, maze, i, cell_to_setMap, edges, edgeCount,
				setNumber);
		}

	}

	maze.setEdges(edges);
	maze.setEdgeCount(edgeCount);
}

/* Function that will take two cells and merge them into one set, and add
them into an edge structure  */
void EllersGenerator::mergeCells(Cell * cell1, Cell * cell2, multimap<Cell*, 
	int> & c_to_sMap, vector<Edge>& edges, int& edgeCount)
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
		int x, y;

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

/* Function that will get the total number of sets in a given row,
used to join with neighbours below this row */
int EllersGenerator::getRowSetCount(multimap<Cell *, int> & c_to_sMap, 
	int rowNumber, Maze& maze)
{
	const int width = maze.getWidth();
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

/* Function that will randomly choose neighbours to add to set 
from row below.
	-if a set only has one cell, it must add an edge
	-if a cell is the last member of a set without an edge, an edge must
	 not be added */
void EllersGenerator::addNextRow(mt19937& gen, Maze& maze, int row, 
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

int EllersGenerator::getCellCount(int currentSet,
	multimap<Cell *, int> c_to_sMap, int row)
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
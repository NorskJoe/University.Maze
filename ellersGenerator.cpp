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

	// multimap<int, Cell *> set_to_cellMap;
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
		cout << "doing row: " << i << endl;
		if(i == height-1)
		{
			finalRow = true;
		}

		cout << "adding horizontally" << endl;
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
				// cout << "choice is: " << choice << endl;
				// cout << "cell1: ";
				// Cell * cellll = maze.getCell(j, i);
				// x = cellll->getCoordinates().xPos;
				// y = cellll->getCoordinates().yPos;
				// cout << y << "," << x << endl;
				if(choice == JOIN)
				{
					//cout << "joined" << endl;
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
	// int x, y;
	// cout << endl << "cell_to_setMap cointains: " << endl;
	// for(auto it = cell_to_setMap.begin(); it != cell_to_setMap.end(); it++)
	// {
	// 	x = it->first->getCoordinates().xPos;
	// 	y = it->first->getCoordinates().yPos;
	// 	cout << y << "," << x << " : " << it->second << endl;
	// }

	maze.setEdges(edges);
	maze.setEdgeCount(edgeCount);
}

/* Function that will take two cells and merge them into one set, and add
them into an edge structure  */
void EllersGenerator::mergeCells(Cell * cell1, Cell * cell2, multimap<Cell*, 
	int> & c_to_sMap, vector<Edge>& edges, int& edgeCount)
{
	multimap<Cell *, int>::iterator c_to_sIt;

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

		x = cell1->getCoordinates().xPos;
		y = cell1->getCoordinates().yPos;
		cout << "joined cells: " << y << "," << x << " - ";
		x = cell2->getCoordinates().xPos;
		y = cell2->getCoordinates().yPos;
		cout << y << "," << x << endl;

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
	
	//cout << "adding vertically" << endl;

	int setCount = getRowSetCount(c_to_sMap, row, maze);
	//cout << "set count in row: " << row << " is: " << setCount << endl;

	// cout << "c_to_sMap contains: " << endl;
	// for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
	// {
	// 	x = it->first->getCoordinates().xPos;
	// 	y = it->first->getCoordinates().yPos;
	// 	cout << y << "," << x << " : " << it->second << endl;
	// }
	// cout << endl;

	int col = 0;
	while(setCount > 0)
	{
		Cell * topCell = maze.getCell(col, row);
		// x = topCell->getCoordinates().xPos;
		// y = topCell->getCoordinates().yPos;
		// cout << "have new cell: " << y << "," << x << endl;
		int setNumber = c_to_sMap.find(topCell)->second;
		// cout << "set number is: " << setNumber << endl;
		int cellCount = getCellCount(setNumber, c_to_sMap, row);
		// cout << "cell count is: " << cellCount << endl << endl;

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
			cout << "cellsToJoin: " << cellsToJoin << endl;
			int difference = cellCount - cellsToJoin;

			while(cellsToJoin > 0)
			{
				Cell * topCell  = maze.getCell(col, row);

				Cell * bottomCell = maze.getCell(col, row+1);
				mergeCells(topCell, bottomCell, c_to_sMap, edges, edgeCount);
				cellsToJoin--;
				col++;
			}
			setCount--;
			col += difference;

		
		}
	}

	/* Add any cells not already in a set, add to a new set */
	for(int i = 0; i < width; i++)
	{
		Cell * cell = maze.getCell(i, row+1);
		// x = cell->getCoordinates().xPos;
		// y = cell->getCoordinates().yPos;
		//cout << "editing cell: " << y << "," << x << endl;

		unsigned set = c_to_sMap.find(cell)->second;

		if(set > c_to_sMap.size() || set <= 0)
		{
			c_to_sMap.insert(pair<Cell *, int>(cell, setNumber));
			setNumber++;
		}
	}

	// cout << "c_to_sMap contains: " << endl;
	// for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
	// {
	// 	x = it->first->getCoordinates().xPos;
	// 	y = it->first->getCoordinates().yPos;
	// 	cout << y << "," << x << " : " << it->second << endl;
	// }
	// cout << endl;

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
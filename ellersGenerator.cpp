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
	int width, height, setNumber, edgeCount, setCount;

	width = maze.getWidth();
	height = maze.getHeight();
	setNumber = 1;
	edgeCount = 0;

	// multimap<int, Cell *> set_to_cellMap;
	multimap<Cell *, int> cell_to_setMap;

	bool finalRow = false;
	for(int i = 0; i < height; i++)
	{
		/* Add all cells to a distinct set */
		for(int j = 0; j < width; j++)
		{
			//for(int j = 0; j < width; j++)
			//{
			Cell * cell = maze.getCell(j, i);

			// set_to_cellMap.insert(pair<int, Cell *>(setNumber, cell));
			cell_to_setMap.insert(pair<Cell *, int>(cell, setNumber));

			setNumber++;
			//}

		}


		cout << "doing row: " << i << endl;
		if(i == height-1)
		{
			finalRow = true;
		}

		/* Go through cells in row, deciding whether to join or not */
		for(int j = 0; j < width-1; j++)
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
		
		/* If reach final row, do not add neighbours from row below */
		if(!finalRow)
		{
			/* Get the total number of sets in this row */
			setCount = getRowSetCount(cell_to_setMap, i, maze);
			cout << "number of sets in row: " << i << " is " << setCount << endl;

			/* For each set, choose a neighbour from below to join set.
			Each set should be joined at least once */
			//while(setCount != 0)
			{
			addNextRow(gen, maze, i, cell_to_setMap, edges, edgeCount);
				
			}
		}


		/* Discard all mappings from row, won't be needed in next iteration */
		for(int j = 0; j < width; j++)
		{
			// set_to_cellMap.clear();
			cell_to_setMap.clear();
		}


	}

		// cout << "set_to_cellMap contains: " << endl;
		// for(auto it = set_to_cellMap.begin(); it != set_to_cellMap.end(); it++)
		// {
		// 	x = it->second->getCoordinates().xPos;
		// 	y = it->second->getCoordinates().yPos;
		// 	cout << it->first << ":" << y << "," << x << endl;
		// }

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
void EllersGenerator::mergeCells(Cell * cell1, Cell * cell2, multimap<Cell*, int> & c_to_sMap,
	vector<Edge>& edges, int& edgeCount)
{
	// multimap<int, Cell *>::iterator s_to_cIt;
	multimap<Cell *, int>::iterator c_to_sIt;

	int setOne, setTwo;
	c_to_sIt = c_to_sMap.find(cell1);
	setOne = c_to_sIt->second;

	c_to_sIt = c_to_sMap.find(cell2);
	setTwo = c_to_sIt->second;

	if(setOne != setTwo)
	{
		/* Clear the unused elements in the map for efficiency */
		c_to_sMap.erase(cell1);
		c_to_sMap.erase(cell2);
		// s_to_cMap.erase(setOne);
		// s_to_cMap.erase(setTwo);
		int setNumber = setOne;
		
		addNewEdge(edges, edgeCount, cell1, cell2);

		/* Add the new elements to map, merge into cell1's set */
		// s_to_cMap.insert(pair<int, Cell *>(setNumber, cell1));
		// s_to_cMap.insert(pair<int, Cell *>(setNumber, cell2));

		c_to_sMap.insert(pair<Cell *, int>(cell1, setNumber));
		c_to_sMap.insert(pair<Cell *, int>(cell2, setNumber));

		// cout << "elements with key " << setNumber << ": " << s_to_cMap.count(setNumber) << endl;

		// cout << "elements with key " << cell1 << ": " << c_to_sMap.count(cell1) << endl << endl;

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

void EllersGenerator::getInstancesOfSet(int setNumber, int&setCount, 
	multimap<Cell *,int>& c_to_sMap)
{

	for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
	{
		if(it->second == setNumber)
		{
			setCount++;
		}
	}
	
}

/* Function that will randomly choose neighbours to add to set 
from row below.
	-if a set only has one cell, it must add an edge
	-if a cell is the last member of a set without an edge, an edge must
	 not be added */
void EllersGenerator::addNextRow(mt19937& gen, Maze& maze, int row, 
	multimap<Cell *, int> & c_to_sMap, vector<Edge>& edges, int& edgeCount)
{
	int width = maze.getWidth();
	int x, y;
	cout << "row: " << row << endl;

	for(int i = 0; i < width; i++)
	{
		//cout << "i: " << i << endl;
		Cell * topCell = maze.getCell(i, row);

		// cout << "have cell: ";
		// x = topCell->getCoordinates().xPos;
		// y = topCell->getCoordinates().yPos;
		// cout << y << "," << x << endl;

		/* Find the set number of this cell, then find how many cells 
		share the same set number */
		multimap<Cell *, int>::iterator it;
		it = c_to_sMap.find(topCell);
		int setNumber = it->second;
		int cellCount = 0;
		getInstancesOfSet(setNumber, cellCount, c_to_sMap);
		// cout << "cellCount is: " << cellCount << endl;

		/* If only cell in set, join to below neighbour */
		if(cellCount == 1)
		{
			Cell * bottomCell = maze.getCell(i, row+1);
			mergeCells(topCell, bottomCell, c_to_sMap, edges, edgeCount);

		}
		else
		{
			/* Randomly decide to add cells, make sure that at least one 
			cell is left NOT joined, and that at least one cell is joined */
			int cellsToJoin = gen() % cellCount;
			/* Ensure at least one cell in set is joined */
			if(cellsToJoin <= 0)
			{
				cellsToJoin = 1;
			}

			cout << "cells to join: " << cellsToJoin << endl;
			
			while(cellsToJoin > 0 && i < width)
			{
				int chosen = gen() % JOIN_CHOICE;

				Cell * topCell = maze.getCell(i, row);
				/* Choose a random cell */
				if(chosen == JOIN)
				{
					Cell * bottomCell = maze.getCell(i, row+1);
					mergeCells(topCell, bottomCell, c_to_sMap, edges, edgeCount);
					cellsToJoin--;
				}
				else
				{
					if(cellsToJoin == 1)
					{
						Cell * bottomCell = maze.getCell(i, row+1);
						mergeCells(topCell, bottomCell, c_to_sMap, edges, edgeCount);
					}
					else
					{
						i++;
					}
				}

			}
		}


		// cout << "cell_to_setMap cointains: " << endl;
		// for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
		// {
		// 	x = it->first->getCoordinates().xPos;
		// 	y = it->first->getCoordinates().yPos;
		// 	cout << y << "," << x << " : " << it->second << endl;
		// }
		// cout << endl;


	}
}
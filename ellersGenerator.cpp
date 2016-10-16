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

	multimap<int, Cell *> set_to_cellMap;
	multimap<Cell *, int> cell_to_setMap;

	int x, y;


	bool finalRow = false;
	for(int i = 0; i < height; i++)
	{
		/* Add all cells to a distinct set */
		for(int j = 0; j < width; j++)
		{
			//for(int j = 0; j < width; j++)
			//{
			Cell * cell = maze.getCell(j, i);

			set_to_cellMap.insert(pair<int, Cell *>(setNumber, cell));
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
				mergeCells(cell1, cell2, set_to_cellMap, cell_to_setMap,
					edges, edgeCount);

			}
			
		}
		
		/* If reach final row, do not add neighbours from row below */
		if(!finalRow)
		{
			/* Get the total number of sets in this row */
			setCount = getRowSetCount(set_to_cellMap, cell_to_setMap, i, maze);
			cout << "number of sets in row: " << i << " is " << setCount << endl;

			/* For each set, choose a neighbour from below to join set.
			Each set should be joined at least once */
			//while(setCount != 0)
			{
				addNextRow(maze, i, setCount, cell_to_setMap);
				
			}
		}


		/* Discard all mappings from row, won't be needed in next iteration */
		for(int j = 0; j < width; j++)
		{
			set_to_cellMap.clear();
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
them into an edge structure */
void EllersGenerator::mergeCells(Cell * cell1, Cell * cell2, multimap<int,
	Cell*> & s_to_cMap, multimap<Cell*, int> & c_to_sMap,
	vector<Edge>& edges, int& edgeCount)
{
	multimap<int, Cell *>::iterator s_to_cIt;
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
		s_to_cMap.erase(setOne);
		s_to_cMap.erase(setTwo);
		int setNumber = setOne;
		
		addNewEdge(edges, edgeCount, cell1, cell2);

		/* Add the new elements to map, merge into cell1's set */
		s_to_cMap.insert(pair<int, Cell *>(setNumber, cell1));
		s_to_cMap.insert(pair<int, Cell *>(setNumber, cell2));

		c_to_sMap.insert(pair<Cell *, int>(cell1, setNumber));
		c_to_sMap.insert(pair<Cell *, int>(cell2, setNumber));

		// cout << "elements with key " << setNumber << ": " << s_to_cMap.count(setNumber) << endl;

		// cout << "elements with key " << cell1 << ": " << c_to_sMap.count(cell1) << endl << endl;

	}
	// cout << "edges contains: " << endl;
	// for(unsigned i = 0; i < edges.size(); i++)
	// {
	// 	int x, y;
	// 	Cell * cellOne = edges[i].getCellOne();
	// 	Cell * cellTwo = edges[i].getCellTwo();
	// 	x = cellOne->getCoordinates().xPos;
	// 	y = cellOne->getCoordinates().yPos;
	// 	cout << y << "," << x << " - ";

	// 	x = cellTwo->getCoordinates().xPos;
	// 	y = cellTwo->getCoordinates().yPos;
	// 	cout << y << "," << x << endl;
	// }
	// cout << endl;
}

/* Function that will get the total number of sets in a given row,
used to join with neighbours below this row */
int EllersGenerator::getRowSetCount(multimap<int, Cell *> & s_to_cMap, 
	multimap<Cell *, int> & c_to_sMap, int rowNumber, Maze& maze)
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

int getNumberOfCellsInSet()
{
	return 0;
}

/* Function that will randomly choose neighbours to add to set 
from row below.
	-if a set only has one cell, it must add an edge
	-if a cell is the last member of a set without an edge, an edge must
	 not be added */
void EllersGenerator::addNextRow(Maze& maze, int row, int& setCount,
	multimap<Cell *, int> & c_to_sMap)
{
	int width = maze.getWidth();
	int x, y;
	cout << "row: " << row << endl;

	for(int i = 0; i < width; i++)
	{
		//cout << "i: " << i << endl;
		Cell * topCell = maze.getCell(i, row);

		cout << "have cell: ";
		x = topCell->getCoordinates().xPos;
		y = topCell->getCoordinates().yPos;
		cout << y << "," << x << endl;

		cout << "cell_to_setMap cointains: " << endl;
		for(auto it = c_to_sMap.begin(); it != c_to_sMap.end(); it++)
		{
			x = it->first->getCoordinates().xPos;
			y = it->first->getCoordinates().yPos;
			cout << y << "," << x << " : " << it->second << endl;
		}


	}
	setCount--;
}
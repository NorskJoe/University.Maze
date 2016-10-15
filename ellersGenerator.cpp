#include <random>
#include <iostream>

#include <vector>
#include <set>
#include <unordered_map>

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
	cout << "in ellers generator" << endl;
	int width, height, setNumber, edgeCount;

	width = maze.getWidth();
	height = maze.getHeight();
	setNumber = 0;
	edgeCount = 0;

	//vector< set< vector<Cell *> > > cellSets;
	unordered_map<int, Cell *> set_to_cellMap;
	unordered_map<Cell *, int> cell_to_setMap;

	/*  Iterators */
	unordered_map<int, Cell *>::const_iterator set_to_cellIterator;
	unordered_map<Cell *, int>::const_iterator cell_to_setIterator;

	int x, y;

	/* Add all cells in first row to a distinct set */
	for(int i = 0; i < width; i++)
	{
		Cell * cell = maze.getCell(i, 0);

		//set< vector<Cell *> > cells;
		//cellSets.push_back(cells);
		set_to_cellMap[setNumber] = cell;
		cell_to_setMap[cell] = setNumber;


		setNumber++;

	}

	// cout << "set_to_cellMap contains: " << endl;
	// for(auto it = set_to_cellMap.begin(); it != set_to_cellMap.end(); it++)
	// {
	// 	cout << it->first << ":" << it->second << endl;
	// }

	// cout << endl << "cell_to_setMap cointains: " << endl;
	// for(auto it = cell_to_setMap.begin(); it != cell_to_setMap.end(); it++)
	// {
	// 	cout << it->first << ":" << it->second << endl;
	// }

	bool finalRow = false;
	bool firstRow = true;
	bool join;
	//for(int i = 0; i < height; i++)
	//{
		/* Reached the last row of cells */
		if(finalRow)
		{

		}

		/* Go through cells in first row, 
		deciding whether to join or not */
		if(firstRow)
		{
			for(int j = 0; j < width-1; j++)
			{
				int choice = gen() % JOIN_CHOICE;
				if(choice == JOIN)
				{
					join = true;
				}
				else
				{
					join = false;
				}

				/* If the choice is to join, create a new edge 
				and merge the sets */
				if(join)
				{
					int first, second;
					Cell * cell1 = maze.getCell(j, 0);
					Cell * cell2 = maze.getCell(j+1, 0);

					cell_to_setIterator = cell_to_setMap.find(cell1);
					first = cell_to_setIterator->second;

					cell_to_setIterator = cell_to_setMap.find(cell2);
					second = cell_to_setIterator->second;

					if(first != second)
					{
						cout << "joining the two cells" << endl;
						addNewEdge(edges, edgeCount, cell1, cell2);
					}


				}
			}

			firstRow = false;
		}
	//}
	maze.setEdges(edges);
	maze.setEdgeCount(edgeCount);
}
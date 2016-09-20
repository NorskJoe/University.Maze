#ifndef MAZE_GENERATOR_H
#define MAZE_GENERATOR_H

#include "maze.h"

using namespace std;

/* Definitions for generation and solving methods.  Used to implement a factory pattern */
#define ALDOUS_BRODER 1
#define ELLERS 2
#define DFS 3
#define BFS 4
#define DIJKSTRA_MANHATTAN 5
#define DIJKSTRA_EUCLIDEAN 6

class MazeGenerator
{
public:
	/* Constructor */
	MazeGenerator();

	/* Functions*/
	static MazeGenerator getGenerator(int);
	void makeMaze(Maze& maze, vector<edge>& edges); 
	void addNewEdge(vector<edge>& edges, int& edgeCount, int& remainingCells, Cell* currentCell, Cell* nextCell);
};

#endif
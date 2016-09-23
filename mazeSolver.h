#ifndef MAZE_SOLVER_H
#define MAZE_SOLVER_H

#include "maze.h"

using namespace std;

/* Definitions for solving options.  Used to implement a factory pattern */
#define DFS 3
#define BFS 4
#define DIJKSTRA_MANHATTAN 5
#define DIJKSTRA_EUCLIDEAN 6

class MazeSolver
{
public:
	/* Constructor */
	MazeSolver();

	/* Functions */
	static MazeSolver* getSolver(int solverType);
	virtual void solveMaze(Maze& maze, vector<edge>& edges) = 0;
};

#endif
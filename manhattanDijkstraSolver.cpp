#include <unordered_map>
#include <unordered_set>
#include <limits>

#include "manhattanDijkstraSolver.h"
#include "minHeap.h"

using namespace std;

/* Constructor */
DijkstraManhattanSolver::DijkstraManhattanSolver()
{

}

/* Main component of algorithm based on explanation at: 
https://rosettacode.org/wiki/Dijkstra%27s_algorithm#C.2B.2B

Heuristic estimates based on explanation at:
http://theory.stanford.edu/~amitp/GameProgramming/Heuristics.html#S7 */
void DijkstraManhattanSolver::solveMaze(Maze& maze)
{
	/* Set up variables and local data structures */
	int width = maze.getWidth();
	int height = maze.getHeight();
	const int INFINITY = numeric_limits<int>::max();

	unordered_map<Cell *, int> minDistance;
	unordered_map<Cell *, Cell *> previous;
	MinHeap heap;

	Cell * startCell = maze.getCell(0,0);
	Cell * endCell = maze.getCell(width-1, height-1);

	/* First mark all cells as unvisited and 
	give a distance cost of infinity */
	for(int i = 0; i < width; i++)
	{
		for(int j = 0; j < height; j++)
		{
			Cell * cell = maze.getCell(i,j);
			cell->setNotVisited();
			minDistance[cell] = INFINITY;
		}
	}

	/* Start of algorithm */
	minDistance[startCell] = 0;
	heap.insert(startCell, minDistance[startCell]);
	startCell->setVisited();

	while(heap.getSize() > 0)
	{
		Cell * currentCell = heap.getMinCell();
		heap.deleteMin();

		for(Cell * neighbour : currentCell->getNeighbourCells())
		{
			int heuristic = heuristicEstimate(maze, neighbour);

			int cost = COST_OF_MOVING_CELL + heuristic;

			if(cost < minDistance[neighbour])
			{
				minDistance[neighbour] = cost;
				heap.insert(neighbour, cost);
				previous[neighbour] = currentCell;
			}
		}
	}

	/* Trace back through path map to find solution */
	Cell * currentCell = endCell;
	unordered_map<Cell *, Cell *>::const_iterator nextCell;
	while(currentCell != startCell)
	{
		nextCell = previous.find(currentCell);
		maze.addPathway(Edge(currentCell, nextCell->second));
		currentCell = nextCell->second;
	}

}

int DijkstraManhattanSolver::heuristicEstimate(Maze& maze, Cell * cell)
{
	return (maze.getWidth() - cell->getCoordinates().yPos-1)  + 
		(maze.getHeight() - cell->getCoordinates().xPos-1);
}
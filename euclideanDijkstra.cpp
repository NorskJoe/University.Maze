#include <cmath>

#include "euclideanDijkstra.h"

using namespace std;

/* Constructor */
DijkstraEuclidean::DijkstraEuclidean()
{

}

int DijkstraEuclidean::heuristicEstimate(Maze& maze, Cell * cell)
{	
	int x = maze.getWidth() - cell->getCoordinates().xPos-1;
	int y = maze.getHeight() - cell->getCoordinates().yPos-1;
	return (int)sqrt((x*x) + (y*y));
}
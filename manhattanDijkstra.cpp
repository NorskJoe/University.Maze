#include "manhattanDijkstra.h"

/* Constructor */
DijkstraManhattan::DijkstraManhattan()
{

}


int DijkstraManhattan::heuristicEstimate(Maze& maze, Cell * cell)
{
	return (maze.getWidth() - cell->getCoordinates().xPos-1)  + 
		(maze.getHeight() - cell->getCoordinates().yPos-1);
}
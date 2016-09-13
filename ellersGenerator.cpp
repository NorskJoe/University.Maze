#include <random>

#include "ellersGenerator.h"

using namespace std;

/* Constructor for making the generator object */
EllersGenerator::EllersGenerator(int w, int h)
{
	width = w;
	height = h;
}

/* Implemented using Ellers's algorithm 
	based on explanation at: http://weblog.jamisbuck.org/2010/12/29/maze-generation-eller-s-algorithm */
void EllersGenerator::makeMaze(vector<edge>& edges, Maze& maze)
{
	

}
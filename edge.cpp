//remove later
#include <iostream>

#include "edge.h"
#include "cell.h"

//remove later
using namespace std;

/* Given a cell, get its neighbouring cell in the Edge */
Cell * Edge::getNeighbouringCell(Cell * cell)
{
	//std::cout << "in getNeighbouringCell" << std::endl;

	if(cell == this->getCellOne())
	{
		//cout << "returning cell2" << endl;
		return this->getCellTwo();
	}
	else if(cell == this->getCellTwo())
	{
		//cout << "returning cell1" << endl;
		return this->getCellOne();
	}
	else
	{
		/* Error */
		return nullptr;
	}
}
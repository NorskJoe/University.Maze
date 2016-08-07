#include "cell.h"


class Edge
{
private:
	Cell *cell1, *cell2;
	bool hasWall;
public:
	/* Constructors */
	Edge();
	
	/* Functions */
	bool getWall() { return hasWall; }
	Cell* getCell1() { return cell1; }
	Cell* getCell2() { return cell2; }
};


#ifndef CELL_H
#define CELL_H


class Cell
{
private:
	int xPos, yPos;
public:
	/* Constructors */
	Cell() :
		xPos(0),
		yPos(0)
	{};
	Cell(int x, int y);

	/* Functions */
	int getCellX() { return xPos; }
	int getCellY() { return yPos; }
	
};

#endif // CELL_H
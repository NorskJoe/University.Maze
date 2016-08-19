#ifndef CELL_H
#define CELL_H

/* Used to hold the position of a cell */
struct coordinates
{
	int xPos, yPos;
};

class Cell
{
private:
	struct coordinates xy;
public:
	/* Constructors */
	Cell() :
		xy()
	{};
	Cell(int x, int y);

	/* Functions */
	struct coordinates getCell();
	//Cell * getOtherCell(Cell * cell);
};

#endif // CELL_H
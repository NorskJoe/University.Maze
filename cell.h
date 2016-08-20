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
	bool visited = false;
public:
	/* Constructors */
	Cell() :
		xy()
	{};
	Cell(int x, int y);

	/* Functions */
	struct coordinates getCell();
	//Cell * getOtherEdge(Cell * cell);
	bool isVisited() { return visited; }
	void setVisited() { this->visited = true; }
};

#endif // CELL_H
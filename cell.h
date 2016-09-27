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
	bool visited;
public:
	/* Constructors */
	Cell() :
		xy()
	{};
	Cell(int x, int y);

	/* Functions */
	struct coordinates getCoordinates();
	bool isVisited() { return visited; }
	void setVisited() { this->visited = true; }
	void setNotVisited() { this->visited = false; }
};

#endif // CELL_H
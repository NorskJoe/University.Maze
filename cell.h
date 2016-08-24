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
	/* Constructors/Destructors */
	Cell() :
		xy()
	{};
	Cell(int x, int y);
	//~Cell();

	/* Functions */
	// CHANGE TO getCoordinates
	struct coordinates getCoordinates();
	bool isVisited() { return visited; }
	void setVisited() { this->visited = true; }
};

#endif // CELL_H
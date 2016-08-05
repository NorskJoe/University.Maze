/*
	The maze class declarations and definitions
*/

class Maze
{
private:
	int height, width, edgeCount;
public:
	Maze() :
		height(0),
		width(0),
		edgeCount(0)
	{};
	Maze(int h, int w, int edges);

	int getHeight() { return height; }
	int getWidth() { return width; }
	int getEdgeCount() { return edgeCount; }
};


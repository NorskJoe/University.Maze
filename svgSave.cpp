#include <fstream>
#include <vector>

#include "svgSave.h"

using namespace std;

bool SVGsave(string fileName, Maze& maze)
{
	int height, width, edgeCount;

	width = maze.getWidth();
	height = maze.getHeight();

	ofstream out(fileName.c_str());

	if(out.is_open() == false)
	{
		return false;
	}

	/* Writing header info */
	out << "<svg width='" << width*CELL_SIZE << "' ";
	out << "height='" << height*CELL_SIZE << "' ";
	out << "xmlns='http://www.w3.org/2000/svg' >" << endl;
	out << "<rect width='" << width*CELL_SIZE << "' ";
	out << "height='" << height*CELL_SIZE << "' ";
	out << "style='fill:black' />" << endl;

	/* Get edges */
	vector<edge> edges = maze.getEdges();
	

	/* Footer info */
	out << "</svg>" << endl;
	


	return false;
}
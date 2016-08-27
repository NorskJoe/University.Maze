#include <fstream>
#include <vector>
#include <iostream>

#include "svgSave.h"

using namespace std;

bool SVGsave(string fileName, Maze& maze)
{
	int height, width;

	width = maze.getWidth();
	height = maze.getHeight();

	ofstream out(fileName.c_str());

	if(out.is_open() == false)
	{
		return false;
	}

	/* Writing header info */
	out << "<svg viewbox='0 0 1 1' width='" << width*CELL_SIZE << "' ";
	out << "height='" << height*CELL_SIZE << "' ";
	out << "xmlns='http://www.w3.org/2000/svg' >" << endl;
	out << "<rect width='" << width*CELL_SIZE << "' ";
	out << "height='" << height*CELL_SIZE << "' ";
	out << "style='fill:blue' />" << endl;

	/* Get edges */
	vector<edge> edges = maze.getEdges();
	int x1, x2, y1, y2;

	for(int i = 0; i < maze.getEdgeCount(); i++)
	{
		Cell * cellOne = edges[i].cell1;
		Cell * cellTwo = edges[i].cell2;
		x1 = cellOne->getCoordinates().xPos;
		y1 = cellOne->getCoordinates().yPos;
		x2 = cellTwo->getCoordinates().xPos;
		y2 = cellTwo->getCoordinates().yPos;

		out << "<line stroke='white' ";
		out << "x1='" << x1*CELL_SIZE+OFFSET << "' ";
		out << "x2='" << x2*CELL_SIZE+OFFSET << "' ";
		out << "y1='" << y1*CELL_SIZE+OFFSET << "' ";
		out << "y2='" << y2*CELL_SIZE+OFFSET << "' ";
		out << "stroke-width='" << STROKE_WIDTH << "' />" << endl;
	}

	/* Footer info */
	out << "</svg>" << endl;
	
	return true;
}
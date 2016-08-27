#include <fstream>
#include <iostream>
#include <vector>

#include "fileHandler.h"


using namespace std;

/* Default constructor */
FileHandler::FileHandler()
{

}

bool FileHandler::saveBinaryFile(string fileName, Maze& maze)
{
    output.open(fileName.c_str());

    if(output.is_open() == false)
    {
        return false;
    }

    /* Writing file header data */
    int width = maze.getWidth();
    int height = maze.getHeight();
    int edgeCount = maze.getEdgeCount();

    output.write((char*)&width, sizeof(width));
    output.write((char*)&height, sizeof(height));
    output.write((char*)&edgeCount, sizeof(edgeCount));

    /* Writing edge data to file */
    vector<edge> edges = maze.getEdges();
    for(vector<edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        int x1, y1, x2, y2;

        x1 = it->cell1->getCoordinates().xPos;
        y1 = it->cell1->getCoordinates().yPos;
        x2 = it->cell2->getCoordinates().xPos;
        y2 = it->cell2->getCoordinates().yPos;

        output.write((char*)&x1, sizeof(x1));
        output.write((char*)&y1, sizeof(y1));
        output.write((char*)&x2, sizeof(x2));
        output.write((char*)&y2, sizeof(y2));
    }

    /* Close and return */ 
    output.close();
    return true;
}

bool FileHandler::saveSVGFile(string fileName, Maze& maze)
{
	int height, width;

	width = maze.getWidth();
	height = maze.getHeight();

	output.open(fileName.c_str());

	if(output.is_open() == false)
	{
		return false;
	}

	/* Writing header info */
	output << "<svg viewbox='0 0 1 1' width='" << width*CELL_SIZE << "' ";
	output << "height='" << height*CELL_SIZE << "' ";
	output << "xmlns='http://www.w3.org/2000/svg' >" << endl;
	output << "<rect width='" << width*CELL_SIZE << "' ";
	output << "height='" << height*CELL_SIZE << "' ";
	output << "style='fill:blue' />" << endl;

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

		output << "<line stroke='white' ";
		output << "x1='" << x1*CELL_SIZE+OFFSET << "' ";
		output << "x2='" << x2*CELL_SIZE+OFFSET << "' ";
		output << "y1='" << y1*CELL_SIZE+OFFSET << "' ";
		output << "y2='" << y2*CELL_SIZE+OFFSET << "' ";
		output << "stroke-width='" << STROKE_WIDTH << "' />" << endl;
	}

	/* Footer info */
	output << "</svg>" << endl;
	
	return true;
}

Maze FileHandler::loadBinaryFile (string fileName, vector<edge>& edges) 
{
	input.open(fileName.c_str());

    /* Check validity of file, return empty maze if fails */
  	if(input.is_open() == false)
  	{
  		cout << "Unable to open file." << endl;
        return Maze();
  	}

  	// get length of file:
    input.seekg (0, input.end);
    int length = input.tellg();
    input.seekg (0, input.beg);

    /* Getting maze information from start of file */
  	unsigned width = 0, height = 0, edgeCount = 0;

  	input.read((char*)&width, sizeof(width));
  	input.read((char*)&height, sizeof(height));
  	input.read((char*)&edgeCount, sizeof(edgeCount));

  	/* Check maze dimension validity, return empty if fail */
  	if(width == 0 || height == 0 || edgeCount == 0)
  	{
  		cout << "Width or height of maze cannot be less than 1." << endl;
        return Maze();
  	}

    /* Check maze is a square */
    if(width != height)
    {
        cout << "The maze must be a square." << endl;
        return Maze();
    }

    /* Initialise maze of cells */
    Maze maze(width, height, edgeCount);

    /* Getting the edge information from file */
    int edgeCounter = 0;
    while(input.tellg() != length)
    {

        unsigned x1, x2, y1, y2;
        input.read((char*)&x1, sizeof(x1));
        input.read((char*)&y1, sizeof(y1));
        input.read((char*)&x2, sizeof(x2));
        input.read((char*)&y2, sizeof(y2));

        /* Check if edges read in are within bounds of the maze */
        if(x1 < 0 || x1 > width || x2 < 0 || x2 > width || y1 < 0 || y1 > height || y2 < 0 || y2 > height)
        {
            cout << "Error reading in " << fileName << ". Some edges are outside the bounds of the maze." << endl;
            return Maze();
        }

        edges.push_back(edge());
        edges[edgeCounter].cell1 = maze.getCell(x1, y1);
        edges[edgeCounter].cell2 = maze.getCell(x2, y2);

        edgeCounter++;

    }
    maze.setEdges(edges);

  	return maze;
}
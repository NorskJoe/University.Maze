#include <fstream>
#include <iostream>
#include <vector>

#include "fileHandler.h"

using namespace std;

/* Default constructor */
FileHandler::FileHandler()
{

}

/* Function to save an existing maze's attributes to a .maze binary file */
bool FileHandler::saveBinaryFile(string fileName, Maze& maze)
{
    ofstream output;
    output.open(fileName.c_str());

    if(!output.is_open())
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
    vector<Edge> edges = maze.getEdges();
    for(vector<Edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        int x1, y1, x2, y2;

        Cell * cell1 = it->getCellOne();
        Cell * cell2 = it->getCellTwo();

        x1 = cell1->getCoordinates().xPos;
        y1 = cell1->getCoordinates().yPos;
        x2 = cell2->getCoordinates().xPos;
        y2 = cell2->getCoordinates().yPos;

        output.write((char*)&x1, sizeof(x1));
        output.write((char*)&y1, sizeof(y1));
        output.write((char*)&x2, sizeof(x2));
        output.write((char*)&y2, sizeof(y2));
    }

    if(!output.good())
    {
        return false;
    }

    /* Close and return */ 
    output.close();
    return true;
}

/* Function to save an existing maze to an svg file */
bool FileHandler::saveSVGFile(string fileName, Maze& maze)
{
	int height, width;
	width = maze.getWidth();
	height = maze.getHeight();
    ofstream output;
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
    output << "style='fill:black' />" << endl;

    /* Get edges and write edge info */
    vector<Edge> edges = maze.getEdges();
    int x1, x2, y1, y2;
    for(int i = 0; i < maze.getEdgeCount(); i++)
    {
        //cout << "true? (1==true): " << edges[i].isPathway << endl;
        string strokeColour = "white";
        // if(edges[i].isPathway)
        // {
        //     strokeColour = "rgb(255,0,0)";
        // }
        // else
        // {
        //     strokeColour = "rgb(255,255,255";
        // }


        Cell * cellOne = edges[i].getCellOne();
        Cell * cellTwo = edges[i].getCellTwo();
        x1 = cellOne->getCoordinates().xPos;
        y1 = cellOne->getCoordinates().yPos;
        x2 = cellTwo->getCoordinates().xPos;
        y2 = cellTwo->getCoordinates().yPos;

        output << "<line stroke='" << strokeColour << "' ";
        output << "x1='" << x1*CELL_SIZE+OFFSET << "' ";
        output << "x2='" << x2*CELL_SIZE+OFFSET << "' ";
        output << "y1='" << y1*CELL_SIZE+OFFSET << "' ";
        output << "y2='" << y2*CELL_SIZE+OFFSET << "' ";
        output << "stroke-width='" << STROKE_WIDTH << "' />" << endl;
    }

    /* Footer info */
    output << "</svg>" << endl;

    if(!output.good())
    {
        //error
        return false;
    }

    output.close();


	return true;
}

/* Function to load a binary file with a .maze extension, and generate a maze 	with the information */
bool FileHandler::loadBinaryFile (string fileName, vector<Edge>& edges, Maze& maze) 
{
    ifstream input;
	input.open(fileName.c_str(), ios::binary | ios::in);

    /* Check validity of file, return empty maze if fails */
  	if(input.is_open() == false)
  	{
  		cout << "Unable to open file " << fileName << endl;
        return false;
  	}

  	/* get length of file */
    input.seekg (0, input.end);
    int length = input.tellg();
    input.seekg (0, input.beg);

    /* Getting maze information from start of file */
  	unsigned width = 0, height = 0, edgeCount = 0;
  	input.read((char*)&width, sizeof(width));
  	input.read((char*)&height, sizeof(height));
  	input.read((char*)&edgeCount, sizeof(edgeCount));

    /* Initialise maze of cells */
    maze = Maze(width, height, edgeCount);

    /* Getting the edge information from file */
    unsigned edgeCounter = 0;
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
            return false;
        }

        /* Create an edge  */
        Cell * cell1 = maze.getCell(x1, y1);
        Cell * cell2 = maze.getCell(x2, y2);
        edges.push_back(Edge(cell1, cell2));
        //edges[edgeCounter].cell1 = maze.getCell(x1, y1);
        //edges[edgeCounter].cell2 = maze.getCell(x2, y2);
        edgeCounter++;
    }

    /* return an empty maze if the file is invalid */
   	if(!checkFileValidity(width, height, edgeCount, edgeCounter))
   	{
   		return false;
   	}
    if(!input.good())
    {
        return false;
    }

    maze.setEdges(edges);
    input.close();
  	return true;
}

/* This function checks the validity of the maze and the .maze file */
bool FileHandler::checkFileValidity(unsigned width, unsigned height, unsigned edgeCount, unsigned edgesRead)
{
	unsigned totalCells = width*height;
	/* Check enough edges exist */
	if(edgeCount != totalCells-1)
	{
		cout << "There is an error in the .maze file." << endl;
		return false;
	}
	/* Check the validity of the maze size */
	else if(width == 0 || height == 0 || edgeCount == 0)
	{
		cout << "The width and height of the maze must be at least 1" << endl;
		return false;
	}
	/* Check the maze is a square */
	else if(width != height)
	{
		cout << "The maze must be a square. i.e. the width and height should be the same." << endl;
		return false;
	}
	/* Check the header info matches the number of edges read */
	else if(edgeCount != edgesRead)
	{
		cout << "There is an error in the .maze file." << endl;
		return false;
	}
	else
	{
		return true;
	}
}
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

#include "binaryLoad.h"

Maze loadBinFile (string progName, vector<edge>& edges) 
{
  	ifstream bin_file(progName.c_str(), ios::binary | ios::in);
    /* Check validity of file, return empty maze if fails */
  	if(!bin_file.is_open())
  	{
  		cout << "Unable to open file." << endl;
        return Maze();
  	}

  	// get length of file:
    bin_file.seekg (0, bin_file.end);
    int length = bin_file.tellg();
    bin_file.seekg (0, bin_file.beg);

    /* Getting maze information from start of file */
  	unsigned width = 0, height = 0, edgeCount = 0;

  	bin_file.read((char*)&width, sizeof(width));
  	bin_file.read((char*)&height, sizeof(height));
  	bin_file.read((char*)&edgeCount, sizeof(edgeCount));

  	//DEBUGGING
  	cout << "width: " << width << endl;
  	cout << "height: " << height << endl;
  	cout << "edges: " << edgeCount << endl;
    //DEBUGGING

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
    while(bin_file.tellg() != length)
    {

        unsigned x1, x2, y1, y2;
        bin_file.read((char*)&x1, sizeof(x1));
        bin_file.read((char*)&y1, sizeof(y1));
        bin_file.read((char*)&x2, sizeof(x2));
        bin_file.read((char*)&y2, sizeof(y2));

        /* Check if edges read in are within bounds of the maze */
        if(x1 < 0 || x1 > width || x2 < 0 || x2 > width || y1 < 0 || y1 > height || y2 < 0 || y2 > height)
        {
            cout << "Error reading in " << progName << ". Some edges are outside the bounds of the maze." << endl;
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
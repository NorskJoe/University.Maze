#include <fstream>
#include <vector>

#include "binarySave.h"

using namespace std;

bool saveBinFile(string fileName, Maze& maze)
{
    ofstream out(fileName.c_str(), ios::binary);

    if(out.is_open() == false)
    {
        return false;
    }

    /* Writing file header data */
    int width = maze.getWidth();
    int height = maze.getHeight();
    int edgeCount = maze.getEdgeCount();

    out.write((char*)&width, sizeof(width));
    out.write((char*)&height, sizeof(height));
    out.write((char*)&edgeCount, sizeof(edgeCount));

    /* Writing edge data to file */
    vector<edge> edges = maze.getEdges();
    for(vector<edge>::iterator it = edges.begin(); it != edges.end(); ++it)
    {
        int x1, y1, x2, y2;

        x1 = it->cell1->getCoordinates().xPos;
        y1 = it->cell1->getCoordinates().yPos;
        x2 = it->cell2->getCoordinates().xPos;
        y2 = it->cell2->getCoordinates().yPos;

        out.write((char*)&x1, sizeof(x1));
        out.write((char*)&y1, sizeof(y1));
        out.write((char*)&x2, sizeof(x2));
        out.write((char*)&y2, sizeof(y2));
    }

    /* Close and return */ 
    out.close();
    return true;
}
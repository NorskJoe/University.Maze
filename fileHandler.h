#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "maze.h"

#define CELL_SIZE 100
#define OFFSET 50
#define STROKE_WIDTH 50

class FileHandler
{
private:
	ifstream input;
	ofstream output;
public:
	/* Constructor */
	FileHandler();

	/* Functions */
	bool saveBinaryFile(std::string, Maze&);
	bool saveSVGFile(std::string, Maze&);
	Maze loadBinaryFile(std::string, vector<edge>&);

};

#endif
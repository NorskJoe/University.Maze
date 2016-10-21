#ifndef FILE_HANDLER_H
#define FILE_HANDLER_H

#include "maze.h"

/* Definitions used when writing an svg file */
#define CELL_SIZE 100
#define OFFSET 50
#define STROKE_WIDTH 50

class FileHandler
{
public:
	/* Constructor */
	FileHandler();

	/* Functions */
	bool saveBinaryFile(std::string, Maze&);
	bool saveSVGFile(std::string, Maze&);
	bool loadBinaryFile(std::string, vector<Edge>&, Maze&);
	bool checkFileValidity(unsigned w, unsigned h, unsigned edgeCount, 
		unsigned edgesRead);

};

#endif
#ifndef SVG_H
#define SVG_H

#include <string>
#include "maze.h"

#define CELL_SIZE 100
#define OFFSET 50
#define STROKE_WIDTH 50

bool SVGsave(std::string, Maze&);

#endif
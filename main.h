/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include "maze.h"

using namespace std;

const string LOAD_BINARY_FILE = "--lb";
const string SAVE_SVG_FILE = "--sv";
const string SAVE_BINARY_FILE = "--sb";
const string GENERATE_ALDOUS_BRODER = "--ga";
const string GENERATE_ELLERS = "--ge";
const string SOLVE_DFS = "--pd";
const string SOLVE_BFS = "--pb";
const string SOLVE_MANHATTAN = "--pm";
const string SOLVE_EUCLIDEAN = "--pe";

int programUsage(string programName);

bool getSeedArguments(Maze&, mt19937&, string, string, string);
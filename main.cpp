/*
	Main entry point of maze project
*/

#include <iostream>

using namespace std;

const string LOAD_BINARY_FILE = "--lb";
const string GENERATE_WITH_SEED = "--g";
const string SAVE_SVG_FILE = "--sv";
const string SAVE_BINARY_FILE = "--sb";
const string EMPTY_ARGUMENT = "";

int main(int argc, char **argv)
{
	/* Flags used for command line arguments */
	bool loadBinary = false;
	bool loadSeed = false;
	bool saveSVG = false;
	bool saveBinary = false;

	string programName = argv[0];

	/* Run through arguments entered, ignoring program name */
	for (int i = 1; i < argc; i++)
	{
		string currentArgument = argv[i];


	}
}
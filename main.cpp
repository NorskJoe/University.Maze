/*
	Main entry point of maze project
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

#include "binaryLoad.h"
#include "mazeGenerator.h"
#include "binarySave.h"
#include "svgSave.h"

using namespace std;

const string LOAD_BINARY_FILE = "--lb";
const string GENERATE_WITH_SEED = "--g";
const string SAVE_SVG_FILE = "--sv";
const string SAVE_BINARY_FILE = "--sb";

const int BUFFER = 1000;

int programUsage(string programName);

int main(int argc, char **argv)
{
	/* Flags used for command line arguments */
	bool loadBinary = false;
	bool loadSeed = false;
	bool saveSVG = false;
	bool saveBinary = false;

	long seed;
	int width, height;
	ifstream infile;
	vector<edge> edges;
	Maze maze;

	string programName = argv[0];

	/* Run through arguments entered, ignoring program name */
	for (int i = 1; i < argc; i++)
	{
		string currentArgument = argv[i];

		if (currentArgument == LOAD_BINARY_FILE)
		{
			/* First check if another generation option has been entered */
			if (loadSeed == true)
			{
				cout << "Invalid command line arguments." << endl;
				return programUsage(programName);
			}
			loadBinary = true;
			/* Check another argument exists */
			if (i + 1 != argc)
			{
				/* Get and validate file to load. 
					Generate the outline of maze */
				maze = loadBinFile(argv[i+1], edges);

				if(maze.getWidth() == 0 || maze.getHeight() == 0)
				{
					cout << "There was an error in the file: " << argv[i+1] << endl;
					return programUsage(programName);
				}
			}
			else
			{
				return programUsage(programName);
			}
		}

		else if (currentArgument == GENERATE_WITH_SEED)
		{
			/* First check if another generation option has been entered */
			if (loadBinary == true)
			{
				cout << "Invalid command line arguments." << endl;
				return programUsage(programName);
			}
			loadSeed = true;
			/* Check another argument exists */
			if (i + 1 != argc)
			{
				/* Get and validate seed argument */
				istringstream iss(argv[i + 1]);
				if (iss >> seed)
				{
					/* Valid seed, check if width and height entered */
					istringstream iss(argv[i + 2]);
					if (iss >> width)
					{
						istringstream iss(argv[i + 3]);
						if (iss >> height)
						{
							/* Valid width and height entered */

						}
						else
						{
							cout << "Width and/or height values invalid" << endl;
							return programUsage(programName);
						}
					}
					else
					{
						/* Width value not entered, checking next argument
						  validity */
						if (argv[i + 2] == SAVE_BINARY_FILE || argv[i + 2] 
							== SAVE_SVG_FILE)
						{
							/* Width and height not entered, default to 10 */
							cout << "Width and height not entered. Defaulting to 10x10... " << endl;
							width = 10;
							height = 10;
						}
						else
						{
							/* Invalid arguments entered */
							cout << "Invalid command line arguments." << endl;
							return programUsage(programName);
						}
					}
				}
				/* No seed entered */
				else
				{
					/* Checking if next argument is valid */
					if (argv[i + 1] != SAVE_BINARY_FILE && argv[i + 1] 
						!= SAVE_SVG_FILE)
					{
						cout << "Invalid command line arguments. No seed entered" << endl;
						return programUsage(programName);
					}
					else
					{
						/* Seed must be generated */
						cout << "Generating seed... " << endl;
						cout << "Width & Height defaulting to 10x10..." << endl;
						seed = 10;
						width = 10;
						height = 10;
					}
				}
				mazeGenerator generator = mazeGenerator(width, height, seed);
				maze = generator.makeMaze(edges);
			}
			else 
			{
				cout << "Error in command line arguments." << endl;
				programUsage(programName);
			}
		}

		else if (currentArgument == SAVE_SVG_FILE)
		{
			/* Check validity of filename */
			if(i + 1 != argc)
			{
				string fileName = argv[i + 1];
				if (fileName.substr(fileName.find_last_of(".") + 1) == "svg")
				{
					/* Valid filename */
					saveSVG = true;
					SVGsave(argv[i+1], maze);

				}
				else
				{
					/* Invalid filename */
					cout << "Invalid filename entered." << endl;
					return programUsage(programName);
				}
			}
			else
			{
				cout << "ERROR: please specify a filename to save." << endl;
			}
		}

		else if (currentArgument == SAVE_BINARY_FILE)
		{
			/* Check validity of filename */
			if(i + 1 != argc)
			{
				string fileName = argv[i + 1];
				if (fileName.substr(fileName.find_last_of(".") + 1) == "maze")
				{
					/* Valid filename */
					saveBinary = true;
					saveBinFile(fileName, maze);
				}
				else
				{
					/* Invalid filename */
					cout << "Invalid filename entered." << endl;
					return programUsage(programName);
				}
			}
			else
			{
				cout << "ERROR: please specify a filename to save." << endl;
			}
		}
	}

	/* Final validity check of arguments */
	if (loadBinary == false && loadSeed == false)
	{
		cout << "No valid maze generation option found." << endl;
		return programUsage(programName);
	}

	if (saveBinary == false && saveSVG == false)
	{
		cout << "No valid file saving option found." << endl;
		return programUsage(programName);
	}


	//DEBUGGING PATH
	cout << "STORED: " << endl;
	for(vector<edge>::iterator it = edges.begin(); it != edges.end(); ++it)
	{
		cout << it->cell1->getCell().xPos << endl;
		cout << it->cell1->getCell().yPos << endl;
		cout << it->cell2->getCell().xPos << endl;
		cout << it->cell2->getCell().yPos << endl;
	}
	//DEBUGGING

	// DEBUGGING ARGS
	cout << "arguments are: " << endl;
	cout << "loadBinary: " << loadBinary << endl;
	cout << "loadSeed: " << loadSeed << endl;
	cout << "width: " << maze.getWidth() << endl;
	cout << "height: " << maze.getHeight() << endl;
	cout << "edges: " << maze.getEdgeCount() << endl;
	cout << "saveBinary: " << saveBinary << endl;
	cout << "saveSVG: " << saveSVG << endl;
	// DEBUGGING

	/* At this point, all arguments and variables are valid */
	

	return 0;
}

/* Function to display the proper program usage to the user */
int programUsage(string programName)
{
	/* Correct usage of arguments */
	cout << endl;
	cout << "The correct use of arguments are: " << endl;
	cout << "\t" << programName << "<[--g seed width height] OR ";
	cout << "[--g seed] OR [--g] OR [--lb infile]> " << endl;
	cout << "\t<[--sv filename.svg] AND\\OR [--sb filename.maze]>" << endl << endl;
	/* Explanation of arguments */
	cout << "<--g> flag generates a new maze from seed. <seed> is the optional seed ";
	cout << "to be used for generation. <width> and <height> are the optional ";
	cout << "desrired width and height of the maze." << endl << endl;
	cout << "<--lb> flag will load an existing maze from a .maze file. ";
	cout << "<infile> is the specified .maze file to load a maze from." << endl << endl;
	cout << "<--sv> flag will tell the program to save the maze in an .svg file. ";
	cout << "This file must have the .svg file extension. " << endl << endl;
	cout << "<--sb> flag will tell the program to save the maze in a .maze file ";
	cout << "in binary form." << endl << endl;
	
	return -1;
}
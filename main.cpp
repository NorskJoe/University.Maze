#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <random>

#include "main.h"
#include "maze.h"
#include "mazeGenerator.h"
#include "mazeSolver.h"
#include "fileHandler.h"

using namespace std;

/* MAIN FUNCTION */
int main(int argc, char **argv)
{
	/* Flags used for command line arguments */
	bool loadBinary = false;
	bool loadAldous = false;
	bool loadEllers = false;
	bool saveSVG = false;
	bool saveBinary = false;
	/* Variables used for initialising and storing information of maze */
	unsigned long seed;
	int width, height, mazeType;
	mt19937 generator;
	/* The maze object and its pathways */
	Maze maze;
	vector<Edge> edges;
	vector<Edge> pathways;

	FileHandler file;

	const string programName = argv[0];
	string svgFileName;
	string binaryFileName;

	/* Run through arguments entered, ignoring program name */
	/* 	CHECKING GENERATION ARGUMENTS */
	for (int i = 1; i < argc; i++)
	{
		string currentArgument = argv[i];
		/* Load and initialise maze from a binary file */
		if (currentArgument == LOAD_BINARY_FILE)
		{
			/* First check if another generation option has been entered */
			if (loadAldous == true || loadEllers == true)
			{
				cout << "Only one maze generation option can be entered." << endl;
				return programUsage(programName);
			}
			loadBinary = true;
			/* Check another argument exists */
			if (i + 1 != argc)
			{
				/* Get and validate file to load */
				if(!file.loadBinaryFile(argv[i+1], edges, maze))
				{
					return programUsage(programName);
				}
			}
			else
			{
				cout << "No valid filename found." << endl;
				return programUsage(programName);
			}
		}
		/* Generate a new maze */
		else if (currentArgument == GENERATE_ALDOUS_BRODER)
		{
			/* First check if another generation option has been entered */
			if (loadBinary == true || loadEllers == true)
			{
				cout << "Only one maze generation option can be entered." << endl;
				return programUsage(programName);
			}

			/* Check another argument exists */
			if (i + 1 != argc)
			{
				/* Get and validate seed argument */
				//istringstream iss(argv[i + 1]);
				if (argv[i+1] != SAVE_BINARY_FILE 
					&& argv[i+1] != SAVE_SVG_FILE
					&& argv[i+1] != SOLVE_EUCLIDEAN
					&& argv[i+1] != SOLVE_DFS
					&& argv[i+1] != SOLVE_BFS
					&& argv[i+1] != SOLVE_MANHATTAN)
				{
					if(!getSeedArguments(maze, generator, argv[i+1], argv[i+2], argv[i+3]))
					{
						return programUsage(programName);
					}
		
				}
				/* No seed entered */
				else
				{
					/* Checking if next argument is valid */
					if (argv[i+1] != SAVE_BINARY_FILE 
						&& argv[i+1] != SAVE_SVG_FILE 
						&& argv[i+1] != SOLVE_DFS
						&& argv[i+1] != SOLVE_BFS
						&& argv[i+1] != SOLVE_MANHATTAN
						&& argv[i+1] != SOLVE_EUCLIDEAN)
					{
						cout << "Invalid command line arguments. No seed entered" << endl;
						return programUsage(programName);
					}
					else
					{
						/* Seed must be generated */
						cout << "Generating seed... " << endl;
						mt19937 mt(time(nullptr));
						seed = mt();
						cout << "Seed for this generation: " << seed << endl;
						cout << "Width & Height defaulting to 10x10..." << endl;
						width = 10;
						height = 10;
						maze.setSeed(seed);
						maze.setWidth(width);
						maze.setHeight(height);

					}
				}
				/* All generation options are valid.  Create the maze */
				/* Set maze generation variables */
				cout << "Generating a maze using the Aldous Broder algorithm..." << endl;
				loadAldous = true;
				mazeType = ALDOUS_BRODER;
				width = maze.getWidth();
				height = maze.getHeight();
				seed = maze.getSeed();
				maze = Maze(width, height, seed);
				/* Dynamically create a generator object based on maze type using a factory method.  Generator object will then generate the maze */
				MazeGenerator* mazeGenerator;
				mazeGenerator = MazeGenerator::getGenerator(mazeType);
				mazeGenerator->makeMaze(maze, generator, edges);

				
			}
			/* Not enough arguments have been entered */
			else 
			{
				cout << "Error in command line arguments. Not enough arguments entered. " << endl;
				return programUsage(programName);
			}
		}

		else if(currentArgument == GENERATE_ELLERS)
		{
			/* First check if another generation option has been entered */
			if (loadBinary == true || loadAldous == true)
			{
				cout << "Only one maze generation option can be entered." << endl;
				return programUsage(programName);
			}

			/* Check another argument exists */
			if (i + 1 != argc)
			{
				if (argv[i+1] != SAVE_BINARY_FILE 
					&& argv[i+1] != SAVE_SVG_FILE
					&& argv[i+1] != SOLVE_EUCLIDEAN
					&& argv[i+1] != SOLVE_DFS
					&& argv[i+1] != SOLVE_BFS
					&& argv[i+1] != SOLVE_MANHATTAN)
				{
					if(!getSeedArguments(maze, generator, argv[i+1], argv[i+2], argv[i+3]))
					{
						return programUsage(programName);
					}
		
				}
				/* No seed entered */
				else
				{
					/* Checking if next argument is valid */
					if (argv[i+1] != SAVE_BINARY_FILE 
						&& argv[i+1] != SAVE_SVG_FILE 
						&& argv[i+1] != SOLVE_DFS
						&& argv[i+1] != SOLVE_BFS
						&& argv[i+1] != SOLVE_MANHATTAN
						&& argv[i+1] != SOLVE_EUCLIDEAN)
					{
						cout << "Invalid command line arguments. No seed entered" << endl;
						return programUsage(programName);
					}
					else
					{
						/* Seed must be generated */
						cout << "Generating seed... " << endl;
						mt19937 mt(time(nullptr));
						seed = mt();
						cout << "Seed for this generation: " << seed << endl;
						cout << "Width & Height defaulting to 10x10..." << endl;
						width = 10;
						height = 10;
						maze.setWidth(width);
						maze.setHeight(height);
						maze.setSeed(seed);

					}
				}
				/* All generation options are valid.  Create the maze */
				/* Set maze generation variables */
				cout << "Generating a maze using Ellers algorithm..." << endl;
				loadEllers = true;
				mazeType = ELLERS;
				width = maze.getWidth();
				height = maze.getHeight();
				seed = maze.getSeed();
				maze = Maze(width, height, seed);
				/* Dynamically create a generator object based on maze type */
				MazeGenerator* mazeGenerator;
				mazeGenerator = MazeGenerator::getGenerator(mazeType);
				mazeGenerator->makeMaze(maze, generator, edges);

			}



			/* Not enough arguments have been entered */
			else 
			{
				cout << "Error in command line arguments. Not enough arguments entered. " << endl;
				programUsage(programName);
			}
		}

		/* CHECKING SOLVING ARGUMENTS */
		else if(currentArgument == SOLVE_DFS)
		{
			MazeSolver* solver;
			solver = MazeSolver::getSolver(DFS);
			solver->solveMaze(maze);
		}

		else if(currentArgument == SOLVE_BFS)
		{
			MazeSolver* solver;
			solver = MazeSolver::getSolver(BFS);
			solver->solveMaze(maze);
		}

		else if(currentArgument == SOLVE_MANHATTAN)
		{

		}

		else if(currentArgument == SOLVE_EUCLIDEAN)
		{
			
		}

		/* CHECKING SAVING OPTIONS */
		else if (currentArgument == SAVE_SVG_FILE)
		{
			/* Check more arguments exist */
			if(i + 1 != argc)
			{
				svgFileName = argv[i + 1];
				/* Check file extension */
				if (svgFileName.substr(svgFileName.find_last_of(".") + 1) == "svg")
				{
					/* Valid filename */
					saveSVG = true;
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
				cout << "Error in command line arguments. No filename found for saving svg." << endl;
				return programUsage(programName);
			}
		}

		else if (currentArgument == SAVE_BINARY_FILE)
		{
			/* Check more arguments exist */
			if(i + 1 != argc)
			{
				binaryFileName = argv[i + 1];
				/* Check filename extension */
				if (binaryFileName.substr(binaryFileName.find_last_of(".") + 1) == "maze")
				{
					/* Valid filename */
					saveBinary = true;
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
				cout << "Error in command line arguments. No filename found for saving binary file." << endl;
				return programUsage(programName);
			}
		}
	}

	/* Final validity check of arguments */
	if (loadBinary == false && loadAldous == false && loadEllers == false)
	{
		cout << "No valid maze generation option found." << endl;
		return programUsage(programName);
	}

	if (saveBinary == false && saveSVG == false)
	{
		cout << "No valid file saving option found." << endl;
		return programUsage(programName);
	}

	/* Saving files are performed last two ensure all edges and 
	pathways are correct */
	/* Saving SVG File */
	if(saveSVG == true)
	{
		cout << "Saving svg file...";
		if(file.saveSVGFile(svgFileName, maze) == false)
		{
			cout << "Error saving " << svgFileName << ". Check the file name is valid." << endl;
			return programUsage(programName);
		}
		cout << "... saved!" << endl;
	}
	/* Saving Binary File */
	if(saveBinary == true)
	{
		cout << "Saving binary .maze file...";
		if(file.saveBinaryFile(binaryFileName, maze) == false)
		{
			cout << "Error saving " << binaryFileName << ". Check the file name is valid." << endl;
			return programUsage(programName);
		}
		cout << "... saved!" << endl;
	}

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
	cout << "desrired width and height of the maze.  Note that if these are entered, you must also enter a seed." << endl << endl;
	cout << "<--lb> flag will load an existing maze from a .maze file. ";
	cout << "<infile> is the specified .maze file to load a maze from." << endl << endl;
	cout << "<--sv> flag will tell the program to save the maze in an .svg file. ";
	cout << "This file must have the .svg file extension. " << endl << endl;
	cout << "<--sb> flag will tell the program to save the maze in a .maze file ";
	cout << "in binary form." << endl << endl;
	
	return -1;
}

/* Function to parse seed, width and height arguments from cmd */
bool getSeedArguments(Maze& maze, mt19937& gen, string seed, 
	string widthArg, string heightArg)
{
	int w, h;
	unsigned long s;

	istringstream iss(seed);
	if(iss >> s)
	{
		istringstream iss(widthArg);
		if(iss >> w)
		{
			istringstream iss(heightArg);
			if(iss >> h)
			{
				if(h != w)
				{
					cout << "The maze must be a square." << endl;
					return false;
				}
				gen.seed(s);
				cout << "The seed for this generation is: " << s << endl;
			}
			else
			{
				/* height invalid */
				cout << "Width and/or height values invalid" << endl;
				return false;
			}
		}

		else
		{
			/* width invalid */
			if (widthArg == SAVE_BINARY_FILE 
				|| widthArg == SAVE_SVG_FILE)
			{
				/* Width and height not entered, default to 10x10 */
				cout << "Width and height not entered. Defaulting to 10x10... " << endl;
				w = 10;
				h = 10;
			}
			/* Invalid input after seed and before saving options */
			else
			{
				cout << "Invalid command line arguments." << endl;
				return false;
			}
		}
	}
	else
	{
		/* seed invalid */
		return false;
	}

	maze.setWidth(w);
	maze.setHeight(h);
	maze.setSeed(s);

	return true;
}
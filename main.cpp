/*
	Main entry point of maze project
*/

/* REMOVE THIS WHEN RUNNING IN LINUX */
#define _CRT_SECURE_NO_DEPRECATE

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

/* Testing using boost */
//#include <boost\filesystem.hpp>

using namespace std;

const string LOAD_BINARY_FILE = "--lb";
const string GENERATE_WITH_SEED = "--g";
const string SAVE_SVG_FILE = "--sv";
const string SAVE_BINARY_FILE = "--sb";
const string EMPTY_ARGUMENT = "";

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
	FILE *fileLoad;
	FILE *fileSave;

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
				/* Get and validate file to load */
				fileLoad = fopen(argv[i+1], "r");
				if (fileLoad == NULL)
				{
					cout << "Error locating and opening file: " 
						<< argv[i + 1] << endl;
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
							/* Valid width and height entered*/
						}
						else
						{
							cout << "Height value invalid" << endl;
							return programUsage(programName);
						}
					}
					else
					{
						/* Width value not entered, checking next argument
						  validity */
						if (argv[i + 1] != SAVE_BINARY_FILE || argv[i + 1] 
							!= SAVE_SVG_FILE)
						{
							/* Invalid arguments entered */
							cout << "Invalid command line arguments." << endl;
							return programUsage(programName);
						}
						else
						{
							/* Either width and height not entered */
							cout << "Width value not entered." << endl;
							width = 69;
							height = 69;
							continue;
						}
					}
				}
				else
				{
					/* No seed found. Checking if next argument is valid */
					if (argv[i + 1] != SAVE_BINARY_FILE && argv[i + 1] 
						!= SAVE_SVG_FILE)
					{
						cout << "Invalid command line arguments." << endl;
						cout << argv[i + 1] << endl;
						return programUsage(programName);
					}
					else
					{
						/* Seed must be generated */
						cout << "Generating seed... " << endl;
						width = 1000;
						height = 1000;
					}
				}
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
			string fileName = argv[i + 1];
			if (fileName.substr(fileName.find_last_of(".") + 1) == "svg")
			{
				/* Valid filename */
				saveSVG = true;
				ofstream svgFile(argv[i+1]);
			}
			else
			{
				/* Invalid filename */
				cout << "Invalid filename entered." << endl;
				return programUsage(programName);
			}
		}

		else if (currentArgument == SAVE_BINARY_FILE)
		{
			/* Check validity of filename */
			string fileName = argv[i + 1];
			if (fileName.substr(fileName.find_last_of(".") + 1) == "maze")
			{
				/* Valid filename */
				saveBinary = true;
				ofstream binaryFile(argv[i+1]);
			}
			else
			{
				/* Invalid filename */
				cout << "Invalid filename entered." << endl;
				return programUsage(programName);
			}
		}
	}


	/* Check validity of arguments */
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


	cout << "arguments are: " << endl;
	cout << "loadBinary: " << loadBinary << endl;
	cout << "loadSeed: " << loadSeed << endl;
	cout << "width: " << width << endl;
	cout << "height: " << height << endl;
	cout << "saveBinary: " << saveBinary << endl;
	cout << "saveSVG: " << saveSVG << endl;// DEBUGGING

	cin.ignore(); // DEBUGGING
	return 0;
}

/* Function to display the proper program usage to the user */
int programUsage(string programName)
{
	cin.ignore(); // DEBUGGING
	return -1;
}

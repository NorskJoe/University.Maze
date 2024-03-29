s3542413 - Joseph Johnson

Differences from Assignment One:
- Some parts of the code from assignment one have been changed

- Aldous Broder algorithm has been refactored

- An Edge class was added, and the edge struct removed.  This seemed easier to work with

- Although seeding was not broken, it has been changed to make it more efficient.  The mt19337 object is now passed to functions where it is needed.

- After saving files, I validate the file using good()

- Fixed an error where the program would not work if a seed argument was not entered


Compiling:
 - source /opt/rh/devtoolset-4/enable must be entered into the command line before compiling

 - to compile, type 'make'.  This compiles with the debugging flags required for running the program in dbg

 - to clean the directory of compiled files and the executable, type 'make clean'

 - the executable file created by compiling is called 'maze'

 - to run the executable type ./maze into the command line, followed by the appropriate flags


Flags:
 - --ga: tells the program to generate a maze using the aldous-broder algorithm

 - --ge: tells the program to generate a maze using the ellers algorithm

 - --ge or --ga can be followed by the optinal commands of <seed> <width> <height>

 - if seed is entered, width and height must also be entered

 - if seed is not entered, you cannot specify width and height.  The maze size will default to 10x10.

 - --lb: tells the program to generate a maze from a binary file.  The binary file must have a .maze file extension.  The filename must follow the --lb flag

 - --sb: tells the program to save the maze information in a binary file with a .maze file extension.  The filename must be specified after the --sb flag

 - --sv: tells the program to save the maze to a svg file with a .svg file extension.  THe filename must be specified after the --sv flag.

 - --pm: tells the program to solve a maze using Dijkstra's algorithm using Manhattan cost heuristics

 - --pe: tells the program to solve a maze using Dijkstra's algorithm using Euclidean cost heuristics


Program Usage:
 - --ge OR --ga OR --lb generation options must be used, they cannot be used in conjunction.

 - --sb AND/OR --sv saving options must be used.  At least one or both needs to be chosen.

 - binary files must have the file extension .maze.  svg files must have the file extension .svg.  These must be explicity entered by the user.


Seeding:
- if the user enters a <seed> option, that is used to generate the maze.

- if the user enters the same seed again, with width and height attributes also being equal, the exact same maze will be produced.

- if no seed is entered by the user, a seed will be created based on the current time.  In this case, mazes generated at different times will always be different.

- when a seed is generated by the current time, it will be displayed to the user.  The seed displayed can be entered by the user to create an identical maze at any other time


Unresolved errors:
- None that I know of


Design Patterns:
- The factory pattern is used both for maze solving and maze generating.  See mazeSolver.cpp and mazeGenerator.cpp


Inheritance and Polymorphism:
- Inheritance and polymorphism have been used to reduce code re-usage, in particular for Dijkstra'a algorithm. See dijkstraSolver.cpp, manhattanDijkstra.cpp and euclideanDijkstra.cpp.  As well as mazeSolver.cpp and mazeGenerator.cpp


Other Notes:
 - I did most of my compiling and testing on my home computer running Ubuntu 16.04.  I tested it on the RMIT servers once all functionality was complete, there were some minor errors which had to be fixed.

 - My first and my final version of my class diagram are included in my submission

 - I tested my maze generation and solving algorithms on mazes up to 1000x1000
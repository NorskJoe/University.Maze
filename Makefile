FLAGS = -Wall -pedantic -std=c++14
DEBUG = -g -ggdb
PROG = maze
OBJ = main.o maze.o mazeGenerator.o cell.o fileHandler.o

%.o: %.cpp
	g++ $(FLAGS) $(DEBUG) -c $< -o $@

all: $(OBJ)
	g++ -o $(PROG) $(OBJ)

clean:
	rm -f $(OBJ) $(PROG)
/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include <vector>

class Cell;

using namespace std;

/***************************************************************************** 
	Heap class based on explanation at: http://www.codeproject.
	com/Tips/816934/Min-Binary-Heap-Implementation-in-Cplusplus
	
******************************************************************************/

class MinHeap
{
private:
	struct Data
	{
		Cell * cell;
		int priority;
	};
	vector<Data> heapVector;

	/* Functions */
	void bubbleDown(int index);
	void bubbleUp(int index);

public:
	/* Constructors */
	MinHeap();

	/* Functions */
	void insert(Cell * cell, int priority);
	Cell * getMinCell();
	void deleteMin();
	int getSize();
};
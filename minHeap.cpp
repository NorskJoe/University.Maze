/*******************************************************************************
	Author: Joseph Johnson
	Student Number: s3542413

	Programming Using C++ - Semester 2. 2016
*******************************************************************************/
#include "minHeap.h"

MinHeap::MinHeap()
{

}

/***************************************************************************** 
	Function that moves a node down the tree until it finds its correct place

	index - the index of the node to be moved
	
******************************************************************************/
void MinHeap::bubbleDown(int index)
{
	int length = heapVector.size();
	int leftChild = 2*index + 1;
	int rightChild = 2*index + 2;

	/* Check is index is a leaf */
	if(leftChild >= length)
	{
		return;
	}

	int minIndex = index;

	int currentPriority = heapVector[index].priority;
	int leftChildPriority = heapVector[leftChild].priority;
	int rightChildPriority = heapVector[rightChild].priority;

	/* Check left child */
	if(currentPriority > leftChildPriority)
	{
		minIndex = leftChild;
	}

	currentPriority = heapVector[minIndex].priority;

	/* Check right child */
	if((rightChild < length) && 
		(currentPriority > rightChildPriority))
	{
		minIndex = rightChild;
	}

	/* Swap positions */
	if(minIndex != index)
	{
		Data temp = heapVector[index];
		heapVector[index] = heapVector[minIndex];
		heapVector[minIndex] = temp;
		/* Recursive call */
		bubbleDown(minIndex);
	}
}

/***************************************************************************** 
	Function that moves a node up the tree until it finds its correct place

	index - the index of the node to be moved
	
******************************************************************************/
void MinHeap::bubbleUp(int index)
{
	/* Check if already at top */
	if(index == 0)
	{
		return;
	}

	int parentIndex = (index-1)/2;
	/* Parse data */
	Data parent = heapVector[parentIndex];
	Data current = heapVector[index];
	int parentPriority = parent.priority;
	int currentPriority = current.priority;

	/* Check if larger than parent and swap positions */
	if(parentPriority > currentPriority)
	{
		Data temp = heapVector[parentIndex];
		heapVector[parentIndex] = heapVector[index];
		heapVector[index] = temp;
		/* Recursive call */
		bubbleUp(parentIndex);
	}
}

/***************************************************************************** 
	Function that inserts a new node as a leaf

	cell - the new cell that is being added
	priority - the priority/cost of this cell.  Used for heuristics
	
******************************************************************************/
void MinHeap::insert(Cell * cell, int priority)
{
	/* Create new data struct */
	Data newNode;
	newNode.cell = cell;
	newNode.priority = priority;


	/* Add node to the bottom of the tree and bubble up */
	int length = heapVector.size();

	heapVector.push_back(newNode);

	bubbleUp(length);
}

/***************************************************************************** 
	Function that returns the cell at the top of the heap
	
******************************************************************************/
Cell * MinHeap::getMinCell()
{
	Data data = heapVector[0];
	return data.cell;
}

/***************************************************************************** 
	Function that removes the node from the top of the heap
	
******************************************************************************/
void MinHeap::deleteMin()
{
	int length = heapVector.size();

	/* Check the heap has nodes */
	if(length == 0)
	{
		return;
	}

	heapVector[0] = heapVector[length-1];
	heapVector.pop_back();

	bubbleDown(0);

}

int MinHeap::getSize()
{
	return heapVector.size();
}
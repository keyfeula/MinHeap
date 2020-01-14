#pragma once
/**
heap.h
Purpose: Header file that defines the prototype of the functions for heap.cpp

@author Key Feula
*/



/**
The Element class represents an Element object which has a private data member that is an integer named key
It has a getter and a setter to access and modify the value of key
*/
class Element {
public:
	Element(int value, int vertexNum);
	Element();
	
	int getKey() { return key; }
	void setKey(int value) { key = value; }
	int getVertex() { return vertex; }
	void setVertex(int value) { vertex = value; }
	
private:
	int key;  //Weight
	int vertex;
};


/**
The heap class represents a heap object. It contains an int capacity, which is how many elements it can contain,
an int size, which is how many elements are currently in the heap, and an Element array pointer that can be
used to dynamically allocate memory for the array. It contains getters and setters for these data members
and functions that return the positions of the left child, right child, and parent of a node.
*/

class Heap {
public:
	Heap(int capacity, int size);
	Heap();

	int getCapacity() { return capacity; }
	int getSize() { return size; }
	int getElementValue(int index) { return H[index].getKey(); }
	Element getElement(int index) { return H[index]; }
	Element* getHeapPointer() { return H; }

	void setCapacity(int heapCapacity) { capacity = heapCapacity; }
	void setSize(int heapSize) { size = heapSize; }
	void setElementValue(int value,int index) { H[index].setKey(value); }
	void setHeapPointer(Element * heapPointer) { H = heapPointer; }

	int leftChildPos(int position) {
		return position * 2 + 1;
	}
	int rightChildPos(int position) {
		return position * 2 + 2;
	} 
	int parentPos(int position) {
		return (position - 1) / 2;
	}

	
private:
	Element *H; //Make a destructor for this
	int capacity;
	int size;
};


Heap initialize(int n);
void Heapify(Heap &heap, int position);
void buildHeap(Heap &heap, Element A[], int n);
void insert(Heap &heap, int flag, int k);
Element deleteMin(Heap &heap, int flag);
void decreaseKey(Heap &heap, int flag, int index, int value);
void printHeap(Heap &heap);

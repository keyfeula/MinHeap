#include "heap.h"
#include <iostream>
#include <cmath>

using namespace std;
/**
heap.cpp
This file contains the methods needed to create a min heap and maintain the min heap property

@author Key Feula
*/



/**
Constructor for an Element object
@param value  value of the Element's key
*/
Element::Element(int value, int vertexNum) {
	setKey(value);
	setVertex(vertexNum);
}


/**
Default constructor for an Element object
*/
Element::Element() {
	setKey(0);
}


/**
Constructor for a Heap object. Creates an array of size capacity

@param capacity  capacity of the heap
@param size  current size of the heap
*/
Heap::Heap(int capacity, int size) {
	setCapacity(capacity);
	setSize(size);
	H = new Element[capacity];
}


/**
Default constructor for a Heap object
*/
Heap::Heap() {
	setCapacity(0);
	setSize(0);
}


/**
Initializes a Heap object of capacity n and size 0 and returns it to the caller

@param n  capacity of the heap
*/
Heap initialize(int n) {
	return Heap(n, 0);
}


/**
Heapify maintains the min heap property of a heap by ensuring that each node is smaller than it's children nodes,
if it has any.

@param heap  heap object
@param position  position of the node to start the Heapify operation on
*/
void Heapify(Heap &heap, int position) {
	int leftPos = heap.leftChildPos(position);
	int rightPos = heap.rightChildPos(position);
	int smallestPos = position;
	
	if (leftPos < heap.getSize() && heap.getElementValue(leftPos) < heap.getElementValue(position)) {
		smallestPos = leftPos;
	}
	if (rightPos < heap.getSize() && heap.getElementValue(rightPos) < heap.getElementValue(smallestPos)) {
		smallestPos = rightPos;
	}
	if (smallestPos != position) {
		int smallestValue = heap.getElementValue(smallestPos);
		heap.setElementValue(heap.getElementValue(position), smallestPos);
		heap.setElementValue(smallestValue, position);
		Heapify(heap, smallestPos);
	}
}


/**
The buildHeap method builds a min heap from an Element array of size n using the Heapify method

@param heap  heap object
@param A  Element array
@param n  size of the Element array
*/
void buildHeap(Heap &heap, Element A[], int n) {
	for (int i = 0; i < n; i++) {
		heap.setElementValue(A[i].getKey(), i);
		heap.setSize(heap.getSize() + 1);
	}
	for (int i = n / 2; i >= 0; i--) {
		Heapify(heap, i);
	}
}


/**
The insert method inserts an int k into the heap and decides whether to print the contents given the flag value
If the heap is full, a new, larger heap is created and the elements are copied into it from the old heap, which
is then deleted.

@param heap  heap object
@param flag  if flag is 1, do not print heap info, it it's 2 print heap info before and after the value is inserted
@param k  int to be inserted into the heap at the last position in the array
*/
void insert(Heap &heap, int flag, int k) {
	
		if (heap.getSize() == heap.getCapacity()) {
			int height = (int)log2(heap.getSize());
			int newCapacity = pow(2, height + 1);
			Element *temp = new Element[newCapacity];
			std::copy(heap.getHeapPointer(), heap.getHeapPointer() + heap.getSize(), temp);
			delete[] heap.getHeapPointer();
			heap.setHeapPointer(temp);
			heap.setCapacity(newCapacity);
		}

		if (flag == 1) {
			heap.setSize(heap.getSize() + 1);
			decreaseKey(heap, 1, heap.getSize() - 1, k);
		}
		else if (flag == 2) {
			printHeap(heap);
			heap.setSize(heap.getSize() + 1);
			decreaseKey(heap, 1, heap.getSize() - 1, k);
			printHeap(heap);
		}

}


/**
The decreaseKey method decreases the value of the Element's key at the given index and decides whether or not
to print the heap info given the flag value

@param heap  heap object
@param flag  if the flag value is 1, nothing is printed, if it's 2, the heap info is printed before and after
     the key value is decreased
@param index  index of the Element whose key is to be decreased
@param value  new, decreased value of the key at the index
*/
void decreaseKey(Heap &heap, int flag, int index, int value) {
	
	if (index < heap.getCapacity()) {

		if (flag == 2) {
				printHeap(heap);
		}
		
		heap.setElementValue(value, index);

		while (index > 0 && heap.getElementValue(heap.parentPos(index)) > heap.getElementValue(index)) {
			int temp = heap.getElementValue(heap.parentPos(index));
			heap.setElementValue(heap.getElementValue(index), heap.parentPos(index));
			heap.setElementValue(temp, index);
			index = heap.parentPos(index);
		}

		if (flag == 2) {
			printHeap(heap);
		}

	}
}


/**
The deleteMin method deleted the minimum element of the heap, which is located at the first index, then returns it

@param heap  heap object
@param flag  if the flag value is 1, nothing is printed, if it's 2, the heap info is printed before and after
     the minimum value is removed from the heap
@return  returns the Element object that was deleted from the heap
*/
Element deleteMin(Heap &heap, int flag) {
	if (heap.getSize() < 1) {
		cout << "The heap is empty";
	}
	else if (flag != 1 && flag != 2) {
		cout << "Invalid flag value";
	}
	else {

		if (flag == 2) {
			printHeap(heap);
		}

		Element min = heap.getElement(0);
		heap.setElementValue(heap.getElementValue(heap.getSize() - 1), 0);
		heap.setSize(heap.getSize() - 1);
		Heapify(heap, 0);

		if (flag == 2) {
			printHeap(heap);
		}
		
		return min;
	}
}


/**
The printHeap method prints the current capacity, size, and contents of the array

@param heap  heap object whose info is to be printed
*/
void printHeap(Heap &heap) {
	cout << "The capacity is " << heap.getCapacity() << ".\n";
	cout << "Size is " << heap.getSize() << ".\n";
	
	if (heap.getSize() > 0) {
		for (int i = 0; i < heap.getSize(); i++) {
			cout << heap.getElementValue(i) << " ";
		}
		cout << "\n";
	}
}


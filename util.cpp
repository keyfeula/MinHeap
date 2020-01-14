#include "util.h"
#include "heap.h"

#include <iostream>
#include <fstream>

using namespace std;
/**
util.cpp
Implements nextCommand method which takes console input and performs actions based on the input

@author Key Feula
*/

Heap heap;
/**
The next command method performs heap operations based on char and int input from the console

@param i  pointer to int input for index from the console in main.cpp
@param v  pointer to int input for value from the console in main.cpp
@param f  pointer to int input for flag from the console in main.cpp
*/
int nextCommand(int *i, int *v, int *f) {
	char c;
	
	while(1){

		//scan char from user
		scanf("%c", &c);
		
		if (c == ' ' || c == '\t' || c == '\n'){
			continue;
		}

		//Exit the program
		if (c == 'S' || c == 's') {
			printf("COMMAND: %c.\nThe program is going to be terminated.\n", c);
			break;
		}

		//Read element array from HEAPinput.txt and perform buildHeap on the array
		else if (c == 'R' || c == 'r') {
			printf("COMMAND: R.\n");

			//Check if the heap has been initialized
			if (heap.getCapacity() <= 0) {
				printf("Sorry!!! It cannot be done. Please initialize the heap first.\n");
				break;
			}

			int capacity;
			int value;
			Element *temp;
			ifstream InFile;
			InFile.open("HEAPinput.txt");
			
			//Copy values from the file into a temp array, build the min heap, then delete the temp array
			if (InFile.is_open()) {
					
				InFile >> capacity;

				if(capacity > heap.getCapacity()){
					printf("Sorry!!! It cannot be done. Please increase the capacity of heap first.\n");
					break;
				}
				
				temp = new Element[capacity];
				int counter = 0;

					for (int i = 0; i < capacity; i++) {
						InFile >> value;
						if (value != NULL) {
							counter++;
						}
						temp[i].setKey(value);
					}

					if (counter < capacity) {
						printf("Sorry!!! It cannot be done. The number of elements in file is less than as specified in the beginning of file.\n");
						break;
					}
		            

					InFile.close();
					buildHeap(heap, temp, capacity);
					delete[] temp;
			}
			else {
				printf("There was a problem opening file HEAPinput.txt for reading.");
			}
			break;
		}

		//Write heap info to the console
		else if (c == 'W' || c == 'w'){

			printf("COMMAND: %c. \n", c);

			//Check if the heap has been initialized
			if (heap.getCapacity() > 0) {
				printHeap(heap);
			}
			else {
				printf("Sorry!!! It cannot be done. Please initialize the heap first.\n");
			}
			break;
		}
		

		//Decrease the value of the key at the index, and print heap info depending on flag value
		else if (c == 'K' || c == 'k'){
			scanf("%d", f); scanf("%d", i); scanf("%d", v);
			printf("COMMAND: %c %d %d %d.\n", c, *f, *i, *v);

			//Check if the heap has been initialized
			if (heap.getCapacity() <= 0) {
				printf("Sorry!!! It cannot be done. Please initialize the heap first and put the elements into it.\n");
			}

			//Check if the index is within the bounds of the array
			else if (*i > heap.getSize() || *i < 1) {
				printf("There are only %d elements in the heap. Hence this operation cannot be completed.\n", heap.getSize());
			}

			//Check if the new value is less than the value already at the given index
			else if(heap.getElementValue(*i - 1) < *v){
				printf("%d cannot be larger than the current value in the heap at index %d. Hence this operation cannot be completed.\n", *v, *i);
			}

			//If everything checks out, decrease the key of the element at the given index
			else {
				decreaseKey(heap, *f, *i - 1, *v);
			}
			break;
		}

		//Initialize the heap using the capacity input from the console
 		else if (c == 'C' || c == 'c'){
			scanf("%d", f);
			printf("COMMAND: %c %d. \n", c, *f);

			//Check if the capacity value is a positive integer
			if (*f > 0) {
				heap = initialize(*f);
			}
			else {
				printf("Heap capacity must be greater than 0.");
			}
			break;
 		}

		//Insert element with a key from the user input into the heap
		else if (c == 'I' || c == 'i') {
			scanf("%d", f); scanf("%d", v);

			//Check if heap has been initialized
			if (heap.getCapacity() > 0) {
				printf("COMMAND: %c %d %d. \n", c, *f, *v);
				insert(heap, *f, *v);
			}
			else {
				printf("COMMAND: %c %d %d. \n", c, *f, *v);
				printf("Sorry!!! It cannot be done. Please initialize the heap first.\n");
			}
			break;
		}

		//Delete minimum element from the heap and print heap info depending on flag value
		else if (c == 'D' || c == 'd') {
			scanf("%d", f);
			printf("COMMAND: %c %d. \n", c, *f);

			//Check if the heap has been initialized
			if (heap.getCapacity() <= 0) {
				printf("Sorry!!! It cannot be done. Please initialize the heap first and put the elements into it.\n");
			}

			//Check if the heap is empty
			else if (heap.getSize() <= 0) {
				printf("There are no elements in heap to delete.\n");
			}

			//Delete and return min element
			else if (heap.getSize() > 0) {
				Element deleted = deleteMin(heap, *f);
				printf("%d\n", deleted);
			}
			break;
		}

		printf("Invalid Command\n");
	}
	return c;
}
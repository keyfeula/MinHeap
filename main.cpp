//=============================================================================
// The following is a partial program that calls "nextCommand" in util.cpp.
//=============================================================================
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include "heap.h"
#include <iostream>


int main() {
	// variables for the parser...
	char c;
	int i, v, f;
	while(1){
		c = nextCommand(&i, &v, &f);
		switch (c) {
			case 'S': exit(0);
			default: break;
		}
	}
	exit(0);
}


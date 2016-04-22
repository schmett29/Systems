#include <stdio.h>
#include "myalloc.h"

void *myalloc2(int size);
void coalesce();
void mark(int *p);
void sweep(int *p);

//helper functions
int *isPtr(int *p);
int blockMarked(int *p);
void markBlock(int *p);
void unmarkBlock(int *p);
int blockAllocated(int *p);
void allocateBlock(int *p);
void unallocateBlock(int *p);
int length(int *p);
int *nextBlock(int *p);


int *start;

void myallocinit(int size) {
  int blocklen = ((size + 3) / 8 + 1) * 8;   // the next highest multiple of 8
  start = (int *)malloc(blocklen + 8);        // 8 bytes for the padding,
                                                              // and sentinel header
  if (start == NULL) {
    printf("Cannot init that much space\n");
    exit(1);
  }

  //at this point, blocklen is highest multiple of 8, and
  //start points to an address with blocklen + 8 (a real call
  //to the OS malloc). the +8 is for two extra words: for a sentinal and padding at the front

  start ++;                                 // align on a 4-byte boundary for beginning of usable memory
  *start = blocklen;                    //store the size of usable memory in the first word (our control word for the usable memory)
  *(nextBlock(start)) = 1;            //a way to start the beginning of the bloc of usable memory.
                                                //remember, the sentinel will have length 0 and is the last block
                                                //and the first word is for control of the whole block
}

void printallocation() {
	// prints the current size and allocation of each block
	int i;
	int b;
	char AorU;
	for(i = 0; i < len(start);i++){
  		printf("Block %d: address: %d\t size %d\t %s\n", );
  	}
}

void *myalloc(int size) {
	// use first-fit, splitting the block as much as possible
	// (even if that creates a very small block)

	// call coallesce when it cannot find any sufficiently-large free blocks
	// then searches the block list again
  
}

void *myalloc2(int size) {
 
}

void myfree(void *p) {
	// mark the freed block as unallocated
 
}

void coalesce() {
	// coalesce all adjoining free blocks in the block list
  
} 

void mygc() {
  
}

void mark(int *p) {
 
}

void sweep(int *ptr) {
 
}

int *isPtr(int *p) {  // this is a very inefficient algorithm
  
}

int blockMarked(int *p) {
  
}

void markBlock(int *p) {
  
}

void unmarkBlock(int *p) {
 
}

int blockAllocated(int *p) {
 
}

void allocateBlock(int *p) {
  
}

void unallocateBlock(int *p) {
  
}

int *nextBlock(int *p) {
 
}

int length(int *p) {
  
}

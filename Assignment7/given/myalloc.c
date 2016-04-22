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
  //i'll give you this to start with, rememebr, it creates  a
  //block of memory for us to use in our psuedo heap                      
  int blocklen = ((size + 3) / 8 + 1) * 8;  // the next highest multiple of 8
  start = (int *)malloc(blocklen + 8);     // 8 bytes for the padding, 
                                            // and sentinel header
  if (start == NULL) {
    printf("Cannot init that much space\n");
    exit(1);
  }

  //at this point, blocklen is highest multiple of 8, and
  //start points to an address with blocklen + 8 (a real call
  //to the OS malloc). the +8 is for two extra words: for a sentinal and padding at the front

  start ++;                                 // align on a 4-byte boundary
  *start = blocklen;                  //store the size of usable memory in the first word (our control word for the usable memory)
  *(nextBlock(start)) = 1;          //a way to start the beginning of the bloc of usable memory.
                                                  //remember, the sentinel will have length 0 and is the last block
                                                //and the first word is for control of the whole block
  puts("initialized");
}

void printallocation() {
  // prints the current size and allocation of each block
  int *ptr = start;
  int i = 0;
  int size;

  size = (*ptr)/8*8;
  printf("size is: %d\n", size);

  //now fill in the rest
  while((*ptr)/8*8 != 0){
    size = (*ptr)/8*8;
    printf("size is: %d\n", size);
    if((*ptr)%2 == 1){
      printf("Block %d: address: %d\t size %d\t %s\n", i, *ptr, size,"allocated");
    }
    else{
      printf("Block %d: address: %d\t size %d\t %s\n", i, *ptr, size,"unallocated");
    }
    i++;
    ptr = ptr + size/4;
  }
}

void *myalloc(int size) {
  // use first-fit, splitting the block as much as possible
  // (even if that creates a very small block)

  // call coallesce when it cannot find any sufficiently-large free blocks
  // then searches the block list again

  void *ptr = myalloc2(size);
  //now fill in the reat (remember to coalesce if myallco2 does not find a spot
  return ptr;
}

void *myalloc2(int size) {
  int newsize = ((size+3) / 8 + 1) * 8; //best new size
  int *ptr = start; //start at the begining header
  int *newptr; //an extra pointer
  //do the rest (remember, you can use first fit and don't forget to make the
  //the remaining block unallocated)
  //this sets up a sequential search through the partition, a better way is to use linked lists
  //and will give you extra points (describe this in yuour writeup)
  return ptr+1; //pointer to payload
}

void myfree(void *p) {
  // mark the freed block as unallocated

  //send in pointer to payload
  //so get to header and free the block
  }

void coalesce() {
  // coalesce all adjoining free blocks in the block list

  int *ptr = start; //start at the begining header
  int *nextptr; //an extra pointer
  //fill in the rest
  } 

void mygc() {
  int **max = (int **) 0xbfffffffUL;   // the address of the top of the stack
  int* q;
  int **p = &q;    // the address of the bottom of the stack
  //now fill in the rest
}

void mark(int *p) {
  int i;
  int *ptr;
  //go for it
}

void sweep(int *ptr) {
  //fill in the rest
}

int *isPtr(int *p) {  
 // this is a very inefficient algorithm
 //return the pointer or NULL
 }

int blockMarked(int *p) {
   //your code
}

void markBlock(int *p) {
  //your code
}

void unmarkBlock(int *p) {
 //your code
 //remember you are dealign with the 2nd lowest order bit
}

int blockAllocated(int *p) {
  //your code
}

void allocateBlock(int *p) {
  //your code
}

void unallocateBlock(int *p) {
  //your code
}

int *nextBlock(int *p) {
  //your code
}

int length(int *p) {
 //your code
//remember return number of WORDS not bytes
}

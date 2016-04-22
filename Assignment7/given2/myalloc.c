#include "myalloc.h"
#define _GNU_SOURCE
#include <stdio.h>
#include <assert.h>
#include <signal.h>

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


int *start; // at cw
int hsize; // size of the heap

void myallocinit(int size) { 
  //i'll give you this to start with, rememebr, it creates  a
  //block of memory for us to use in our psuedo heap                      
  int blocklen = ((size + 3) / 8 + 1) * 8;  // the next highest multiple of 8
  hsize = blocklen;
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
  int size = *start;

  //size = (*start)/8*8;
  //printf("size is: %d\n", size);

  //now fill in the rest
  while(length(ptr) != 0){
    //size = (*ptr)/8*8;
    //printf("size is: %d\n", size);
    if(blockAllocated(ptr) == 1){
      printf("Block %d: address: %u\t size %d\t %s\n", i, ptr, length(ptr),"allocated");
    }
    else if(blockAllocated(ptr) == 0){
      printf("Block %d: address: %u\t size %d\t %s\n", i, ptr, length(ptr),"unallocated");
    }
    i++;
    ptr = nextBlock(ptr);
    size = *ptr;
  }
  printf("\n");
}

void *myalloc(int size) {
  // use first-fit, splitting the block as much as possible
  // (even if that creates a very small block)

  // call coallesce when it cannot find any sufficiently-large free blocks
  // then searches the block list again

  void *ptr = myalloc2(size);
  //now fill in the reat (remember to coalesce if myallco2 does not find a spot
  printf("myalloc: %u\n", ptr);
  ///*
  if(ptr == NULL){
    coalesce();
    ptr = myalloc2(size);
    printf("PNULL: %u\n", ptr);
  }
  //*/
  
  //puts("about to be done\n");
  
  return ptr; // to pyaload
}

void *myalloc2(int size) {
  int newsize = ((size+3) / 8 + 1) * 8; //best new size
  int *ptr = start; //start at the begining header
  printf("IN myalloc2: address of the first block is %u\n", ptr);
  printf("IN myallac2: length of first block: %d, length required of new block: %d\n", *ptr, newsize);
  int *newptr; //an extra pointer
  int currentsize = *(start); // A variable that has the current size
  int tempns = 0;
  //do the rest (remember, you can use first fit and don't forget to make the
  //the remaining block unallocated)
  //this sets up a sequential search through the partition, a better way is to use linked lists
  //and will give you extra points (describe this in yuour writeup)
  while(currentsize != 1){
    if(!blockAllocated(ptr) && currentsize >= newsize){
      *(ptr) = newsize; 
      //*ptr = newsize;
      allocateBlock(ptr);
      newptr = nextBlock(ptr);
      tempns = (currentsize)-newsize;
      if(tempns > 0){ // of block is bigger than necessary -> split into two blocks
        *(newptr) = tempns;
      }
      //ptr++;
      return ptr+1; //pointer to payload (user space)
    }
    ptr = nextBlock(ptr);
    currentsize = *(ptr);
    //printf("currentsize: %u\n", currentsize);
  }
  return NULL;
}

void myfree(void *p) {
  // mark the freed block as unallocated

  //send in pointer to payload
  //so get to header and free the block
  printf("IN myfree: want to free users heap memory at location: %u\n",p);
  printf("IN myfree: now turn users's heap location into pointer to control word which is: %u\n",p-4);

  unallocateBlock(p-4);
  }

void coalesce() {
  // coalesce all adjoining free blocks in the block list
  int *ptr = start; //start at the begining header
  int *nextptr; //an extra pointer
  //fill in the rest
  puts("\nabout to coalesce\n");
  while (length(ptr)){ // the heap
    nextptr = nextBlock(ptr);
    // If it's allocated, it needs to be skipped
    if (blockAllocated(ptr)){
      ptr = nextBlock(ptr);
      continue;
    }
    // If the concurrent block is allocated, skip
    else if(blockAllocated(nextptr)){
      ptr = nextBlock(ptr);
      continue;
    }
    // If it is the end, skip
    else if(*(nextptr) == 1){
      ptr = nextBlock(ptr);
      continue;
    }
    else{
      *(ptr) += length(nextptr);
    }
  }
} 

void mygc() {
  //int **max = (int **) 0xbfffffffUL;   // the address of the top of the stack
  unsigned long stack_bottom;
  int **max =  (int **) GC_init();   // get the address of the bottom of the stack
  int* q;
  int **p = &q;    // the address of the bottom of the stack
  
  while (p < max) {
    //printf("0. p: %u, *p: %u max: %u\n",p,*p,max);
    mark(*p);
    printf("checking mark: %u\n", *p);
    p++;
  }

  //now fill in the rest think sweep , think coalesce
  sweep(q);
  coalesce();

}

void mark(int *p) {
  int i;
  int *ptr;
  //printf("going to mark: %u\n", p);
  //go for it
  /* FROM SLIDES:
  if(!is_ptr(p)) return;
  if(markBitSet(p)) return;
  setMarkBit(p);
  for(i=0; i<length(p); i++){
    mark(p[i]);
  }
  return;
  */
  ptr = isPtr(p);
  printf("isPtr: %u\n", ptr);
  if(ptr==NULL){
    printf("not a pointer\n");
    return;
  }
  if(blockMarked(ptr)){
    printf("pointer, but already marked\n");
    return;
  }
  if(blockAllocated(ptr) == 0){
    printf("pointer, but not allocated\n");
    return;
  }
  printf("about to mark block: %u\n", ptr);
  markBlock(ptr);
  for (i = 0; i < length(ptr)/4; i++){ // gives bytes instead of words
    mark(ptr+i);
  }

}

void sweep(int *ptr) {
  //fill in the rest
  /* FROM SLIDE:
  while(ptr<end){
    if markBitSet(ptr){
      clearMarkBit();
    }
    else if (allocateBitSet(ptr)){
      free(p);
    }
    ptr+= length(ptr);
  }
  */
  printf("During SWEEP phase, checking block mark bit and it is %d\n",blockMarked(ptr));
  ptr = start;
  while(length(ptr)){ //(ptr->end)
    if(blockMarked(ptr)){
      unmarkBlock(ptr);
    }
    else if(blockAllocated(ptr)){
      myfree(ptr);
    }
    ptr = nextBlock(ptr);
  }
  }

int *isPtr(int *p) {  
 // this is a very inefficient algorithm
 //return the pointer or NULL
  int *ptr = start; //our start
  int size = hsize/4;
  /*
  printf("the start is: %u\n",ptr);
  printf("+ size of heap: %d\n",size);
  //printf("+ size old method: %d\n",size);
  printf("the end is: %u\n",(ptr+size));
  */
  //printf("checking if pointer\n");
  //now do the rest
  if(ptr <= p && p <= (ptr+size)){
    return p;
  }
  else{
    return NULL;
  }
 }

int blockMarked(int *p) {
   //your code
  return *p != *p;
}

void markBlock(int *p) {
  //your code
  *(p) = *(p)+2;
}

void unmarkBlock(int *p) {
 //your code
 //remember you are dealign with the 2nd lowest order bit
  *(p) = *(p)-2;
}

int blockAllocated(int *p) {
  if((*p)%2 == 1){
    return 1;
  }
  else if((*p)%2 == 0){
    return 0;
  }
}

void allocateBlock(int *p) {
  //(*p)%2 == 1;
  *(p) = *(p)+1;
}

void unallocateBlock(int *p) {
  //(*p)%2 == 0;
  printf("\nunallocating: %u\n\n", p);
  *(p) = *(p)-1;
  //puts("unallocated");
}

int *nextBlock(int *p) {
  return p + length(p)/4;
}

int length(int *p) { //size
//your code:
return *(p)/8*8;
//remember return number of WORDS not bytes
}

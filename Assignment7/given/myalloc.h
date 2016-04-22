#include <stdio.h>
#include <stdlib.h>

void myallocinit(int size);
void *myalloc(int size);
void myfree(void *ptr);
void printmyallocation();
void mygc();

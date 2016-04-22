#include "myalloc.h"

int main() {
  double *p1, *p2;
  myallocinit(56);
  printallocation();
  p1 = (double *)myalloc(20);
  printallocation();
  p2 = (double *)myalloc(10);
  printf("test1: %u\n", p2);
  printallocation();
  myfree(p1);
  printallocation();
  myfree(p2);
  printallocation();
  p1 = (double *)myalloc(20);
  printallocation();
  p2 = (double *)myalloc(24);
  printallocation();
  myfree(p1);
  printallocation();
  myfree(p2);
  printallocation();
  p1 = (double *)myalloc(56);
  printallocation();
}
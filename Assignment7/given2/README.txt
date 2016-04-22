Author: David Schmetterling
Section: 02

Files to be compiled:
test1.c
test2.c
test3.c
test4.c
test5.c
myalloc.c
getStack.c

What works fully:
my_test1.exe
my_test2.exe

What works partially:
my_test3.exe
my_test4.exe
my_test5.exe

What is wrong?
The problem seems to be in the mark and sweep algorithm that I based off of the powerpoint slides. It seems to not be marking blocks as still allocated even though myfree() was called, so the mark algorithm probably is not correctly identifying garbage.
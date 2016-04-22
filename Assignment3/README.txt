README
- David Schmetterling

For Part A:
Compile the files:
1) assignemnt3PartA.c
2) mystringPartA.c
3) mystringPartA.h

For Part B:
Compile the files:
1) assignment3PartB.c
2) definitions.c
3) definitions.h

**NOTE**
Part B is incomplete
I began writing the majority of the code in assignment3PartB.c but realized that it was getting too confusing and I kept getting segmentation falt when trying to display the first word if the String Container was empty (just printing out the first word). So I began converting the the massive function into smaller functions as outlined in the commented out regions. The plan was to:
	1) Add lines to stringContainer - file opener sets this up
	2) Create word containers
	3) Create lines within each word container
	4) Add each word to a linked list (check if they are already in it)
	5) Print out frequency of each word
	6) Print out the word with the maximum frequency
Unfortunately I ran out of time when writing the error check to see if the word already existed in the linked list. However I wrote code that would print out the frequency and line numbers of each word (by calling displayStringList(stringContainer). I did not implement a funciton to print out the word with the maximum frequency, but to do this you would just loop through the linked list of words and compare each word's frequency to that of a local variable that is the current word with the highest frequency, then print that variable.

/*
David Schmetterling
Section 02

Made all the parts as seperate functions. They are exectuable in main if you uncomment their respective variables (a,b,c,d). C and D will print out by default. The program only recognized  input text that is in capital letters (I was not sure if this was how it was supposed to be written or not).

*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

void getArray(char **t);
void printLine(char *line);
char * findMatch(char *text);
char * findMatchNonContiguous(char *text);
char * findMatchNonContiguous2(char *text);
char * findMatchNonContiguous3(char *text);
int findMatches(char *text);

enum Statetype {START,G,C,A};

int main(){
	char *text, *pattern; //pointers to the charater
	char *t, *a, *b, *c; // some pointer variables
	int d; // some integers
	printf("Input : \t");
	getArray(&text);
	printf("Output: \t");
//	a = findMatch(text);
//	if(a != NULL){
//		printLine(a);
//	}
//	b = findMatchNonContiguous2(text);
//	if(b != NULL){
//		printLine(b);
//	}
	c = findMatchNonContiguous3(text);
	if(c != NULL){
		printLine(c);
	}
	d = findMatches(text);
	printf("%d contiguous matches were found\n",d);
	
}

//int getArray(char **line)
void getArray(char **t){
	char b;
	int i=0;
	*t = (char*)malloc(sizeof(char));
	b = getchar();
	while( b != '\n'){
		*(*t+i) = b;  //remember at this point size = 0
		//printf("a = %c\n",*(a+size));
		b = getchar();
		i++;
		*t = realloc(*t, i+1);
   	}
	*(*t+i) = '\0';
}

//void printLine(char line[])
void printLine(char *text){
	int i = 0;
	while (*(text+i) != '\0'){
		//printf("a = %c\n",*(a+i));
		printf("%c",*(text+i)); //no end of line
		i++;
	}
	printf("\n");
}

// PART A
char * findMatch(char *text){
	int i = 0;
	char *c;
	enum Statetype state = START;
 	//enum Boolean found = false;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (*(text+i) != '\0'){
    
    switch (state) {
      case START:
        if (*(text+i) == 'G'){
          state = G;
	  c = (text+i);
	}
        else{
          state = START;
	}
        break;
      case G:
        if (*(text+i) == 'C'){
          state = C;
	}
        else if (*(text+i) == 'G'){
          state = G;
	}
        else{
          state = START;
	}
        break;
      case C:
        if (*(text+i) == 'A'){
          state = A;
	}
	else if (*(text+i) == 'G'){
          state = G;
	}
        else{
          state = START;
	}
        break;
        
      case A:
        if (*(text+i) == 'G'){
  	  printf("Countiguous match found starting at %d:\n", i-3);
	  return c;
	}
        else{
          state = START;
	}
        break;
    }
    i++;
  }
  puts("No contiguous match found");
  return NULL;
}

//PART B
char * findMatchNonContiguous(char *text){
	int i = 0;
	char *c;
	enum Statetype state = START;
 	//enum Boolean found = false;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (*(text+i) != '\0'){
    
    switch (state) {
      case START:
        if (*(text+i) == 'G'){
          state = G;
	  c = (text+i);
	}
        else{
          state = START;
	}
        break;
      case G:
        if (*(text+i) == 'C'){
          state = C;
	}
        break;
      case C:
        if (*(text+i) == 'A'){
          state = A;
	}
        break;
        
      case A:
        if (*(text+i) == 'G'){
          state = G;
  	  printf("Contiguous match found starting at %d:\n", i-3);
	  return c;
	}
        break;
    }
    i++;
  }
  puts("No contiguous match");
  return NULL;
}

//PART C
char * findMatchNonContiguous3(char *text){
	int i = 0, skips = 0, strt;
	char *c;
	enum Statetype state = START;
 	//enum Boolean found = false;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (*(text+i) != '\0'){
    
    switch (state) {
      case START:
        if (*(text+i) == 'G'){
          state = G;
	  c = (text+i);
	  strt = i;
	}
        break;
      case G:
        if (*(text+i) == 'C'){
          state = C;
	}
	else{
	  skips++;
	}
        break;
      case C:
        if (*(text+i) == 'A'){
          state = A;
	}
	else{
	  skips++;
	}
        break;
      case A:
        if (*(text+i) == 'G'){
          if(skips > 10){
  	  	printf("A non accurate non-contiguous match found starting at %d that skips %d character(s):\n", strt, skips);
		return c;
	  }
	  else{
	  printf("Found a non-contiguous match starting at at %d that skips %d character(s):\n", strt,skips);
		return c;
	  }
	}
	else{
		skips++;
	}
        break;
    }
    i++;
  }
  puts("No contiguous match");
  return NULL;
}

// PART D
int findMatches(char *text){
	int i = 0, count = 0;
	char *c;
	enum Statetype state = START;
 	//enum Boolean found = false;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (*(text+i) != '\0'){
    
    switch (state) {
      case START:
        if (*(text+i) == 'G'){
          state = G;
	  c = (text+i);
	}
        else{
          state = START;
	}
        break;
      case G:
        if (*(text+i) == 'C'){
          state = C;
	}
        else if (*(text+i) == 'G'){
          state = G;
	}
        else{
          state = START;
	}
        break;
      case C:
        if (*(text+i) == 'A'){
          state = A;
	}
	else if (*(text+i) == 'G'){
          state = G;
	}
        else{
          state = START;
	}
        break;
        
      case A:
        if (*(text+i) == 'G'){
  	  count++;
	  state = G;
	}
        else{
          state = START;
	}
        break;
    }
    i++;
  }
  return count;
}


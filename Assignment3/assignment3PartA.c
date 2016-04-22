/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "mystringPartA.h"

char * findMatch(String *text, String *pattern);

enum Statetype {IN, OUT};

int main(){
	char *t, *a, *b, *c; // some pointer variables
	printf("Input text: \t");
	String *text = make_string(); //pointers to the charater
	printf("Input Pattern: \t");
	String *pattern = make_string(); //pointers to the charater
	printf("Output: \t");
	a = findMatch(text, pattern);
	if(a == NULL){
		printf("No match found\n");
	}
	else{
		printf("%s\n", a);
	}
}

// PART A
char * findMatch(String *text, String *pattern){
	int i = 0, j = 0, start = 0;
	char *t = text->chars;
	char *p = pattern->chars;
	char *c = NULL;
	enum Statetype state = OUT;
 	//enum Boolean found = false;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (*(t + i) != '\0'){
    
    switch (state) {
      case OUT:
        if (*(t+i) == *(p+j)){
          j++;
          start = i;
          if(*(p+j) == '\0'){
          	c = t+i;
          	printf("Match found starting at %d: ", start);
          	return c;
          }
	  state = IN;
		}
	  else{
	  	j=0;
	  }
	  break;
	  case IN:
	  	if(*(t+i) != *(p+j)){
	  		i = start;
	  		j = 0;
	  state = OUT;
		}
	  	else{
	  		j++;
	  		if(*(p+j) == '\0'){
	  			c = t+i;
          		printf("Match found starting at %d: ", start);
	  			return c;
	  		}
	  	}
	  	break;
	  }
	  i++;
	}
	return c;
	printf("\n");
}
	  	




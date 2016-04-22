/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int getLine(char *line);
//void printLine(char *line, int size);
void findFred(char *line, int size);
#define MAX 80

enum Statetype {START,s1,s2,s3,s4};
enum Boolean {true,false};

int main(){
	char m[80];
	char *a;
	int i,size=0;
	printf("Input : \t");
	size = getLine(m);
	printf("Output: \t");
	findFred(m,size);
}

//int getLine(char line[])
int getLine(char *line){
	char *a,b;
	int i,size=0;
	a = line;
	b = getchar();
	while( b != '\n' && size < 80)
    {
		*(a+size) = b;  //remember at this point size = 0
		//printf("a = %c\n",*(a+size));
		size++;
		b = getchar();
    }
	return size;
}


//void changeCap(char line[], int size)
void findFred(char *line, int size){
	int i=0;
	char *a;
  enum Statetype state = START;
  enum Boolean error = false;
	a = line;
	//*a = *a - 97 + 65; //change the first letter of first word to be Upper Case
	while (i < size){
	    
	    switch (state) {
	      case START:
		if (*(a+i) == '/'){
		  state = s1;
		}
		else if(*(a+i) == '"'){
		  state = s4;
		  printf("%c",*(a+i));
		  error = true;
		}
		else{
		  state = START;
		  printf("%c", *(a+i));
		}
		break;
	      case s1:
		if (*(a+i) == '*'){
		  state = s2;
		  printf("%c",' ');
		  error = true;
		}
		else if(*(a+i) == '/'){
		  state = s1;
		  //print the previous character '/'
		  printf("%c", *(a+i-1));
		}
		else{
		  state = START;
		  //print the previous character '/'
		  printf("%c", *(a+i-1));
		  printf("%c", *(a+i));
		}
		break;
	      case s2:
		if (*(a+i) == '*'){
		  state = s3;
		}
		else{
		  state = s2;
		}
		break; 
	      case s3:
		if (*(a+i) == '/'){
		  state = START;
		  error = false;
		}
		else{
		  state = s3;
		}
		break; 
	      case s4:
		if (*(a+i) == '"'){
		  state = START;
		  printf("%c",*(a+i));
		  error = false;
		}
		else{
		  state = s4;
		  printf("%c",*(a+i));
		}
		break;
	    }
	    i++;
	    if(i==size){
		if(error == true){
		  printf("%c",'\n');
		  printf("Error: unterminated comment");	
		}
	    }
	  }
	printf("%c",'\n');

}

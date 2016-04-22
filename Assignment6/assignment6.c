/*
David Schmetterling
Section 02
*/

#include <stdio.h>    /* standard I/O routines.                */
#include <unistd.h>   /* defines pipe(), amongst other things. */
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <ctype.h>
#include <string.h>
#define MAXLINE 80

void p1();
void p2();
void p3();
char * returnLine(FILE *fp); //returns line or NULL (if at end of file)
int test_eol(char a);
int test_eof(char a);

int fd1[2], fd2[2], fd3[2], fd4[2];
int main(void){
	char c;
	pid_t pid;

	if (pipe(fd1) < 0){
		fprintf(stderr, "pipe error \n");
	}
	if (pipe(fd2) < 0){
		fprintf(stderr, "pipe error \n");
	}
	if (pipe(fd3) < 0){
		fprintf(stderr, "pipe error \n");
	}
	if (pipe(fd4) < 0){
		fprintf(stderr, "pipe error \n");
	}
	
	pid = fork(); //creates first child
	// For testing:
	// printf("I am the parent after creating child: %d\n", pid);
	if (pid == 0){//tweedledum
		// For testing:
		//printf("I am child 1: %d\n", pid);
		p1();
		exit(0);
	}
	pid = fork();
	if (pid == 0){
		// For testing:
		// printf("I am child 2, #%d\n", pid);
		p2();
		exit(0);
	}
	pid = fork();
	if (pid == 0){
		// For testing:
		// printf("I am child 3, #%d\n", pid);
		p3();
		exit(0);
	}

	//CLOSE ALL PIPES - just in case
	close(fd1[0]);
	close(fd1[1]);
	close(fd2[0]);
	close(fd2[1]);
	close(fd3[0]);
	close(fd3[1]);
	close(fd4[0]);
	close(fd4[1]);

	waitpid(-1,NULL,0);
	puts("Output file created, named: mobydicknew.txt");
	exit(0);
}

void p1(){
	FILE *fp;
	int n, i;
	//char *line = (char *)malloc(sizeof(char)*80);
	char *line;
	char next[81];
	close(fd1[0]); // Parent doesn't read
	close(fd2[1]); // Parent recieves message for next only
  	fp = fopen("mobydick.txt" , "r");
  	if(fp == NULL) {
    	perror("Error opening file");
    return;
  	}
  	
  	line = returnLine(fp); //now you have a nice line, so play with it
  	while(line != NULL){
  		write(fd1[1],line, MAXLINE);
  		// Uncomment to see what process 1 sends to process 2
  		/*
  		puts("child 1 sent: ");
  		for (i = 0; i < strlen(line); i++) {
			printf("%c",line[i]);
		}
		printf("\n");
		*/
  		n = read(fd2[0], next, 80);
  		free(line);
  		line = returnLine(fp);
  	}
  	//When file terminates:
  	write(fd1[1], "end",4);
  	fclose(fp);
}

void p2(){
	int n,i,s,m;
	char next[81];
	char * lineBuffer = (char *)malloc(sizeof(char)*MAXLINE+1);
	close(fd1[1]); // child doesn't write on this pipe, child reads from p1
	close(fd2[0]); // child doesn't read on this pipe, child writes back to p1
	close(fd3[0]); // child doesn't read on this pipe, child writes on this pipe to p3
	close(fd4[1]); // child doesn't write on this pipe, child reads
	while((n = read(fd1[0],lineBuffer, MAXLINE)) != 0){
		lineBuffer[n] = '\0';
		// Uncomment to see what process 2 received from process 1
		//printf("child 2 received: %s\n",lineBuffer);
		if(strcmp("end", lineBuffer)==0){ // end of the line
			s=read(fd4[0], lineBuffer, MAXLINE+1); // check to see if p3 done
			write(fd3[1], "end", 4);
			exit(0);
		}
		for (i = 0; i < strlen(lineBuffer); i++){
			if(isupper(lineBuffer[i])){
				lineBuffer[i] = tolower(lineBuffer[i]);
			}
			else if(islower(lineBuffer[i])){
				lineBuffer[i] = toupper(lineBuffer[i]);
			}
		}
		// Uncomment to see what process 2 changes line to
		//puts("Line changed to: ");
		//printf("%s\n",lineBuffer);
		m = read(fd4[0], next,MAXLINE); // is p3 done?
		write(fd3[1],lineBuffer,MAXLINE); // send to p3
		write(fd2[1],"send",5); // ask p1 for moaarrrrrrrr
	}
}

void p3(){
	int n;
	char * lineBuffer = (char *)malloc(sizeof(char)*MAXLINE+1);
	FILE *fo = fopen("mobydicknew.txt", "w");
	if(fo == NULL) {
    	perror("Error opening file\n");
    return;
  	}
  	close(fd3[1]); // child 3 does not write on this pipe, it reads from p2
  	close(fd4[0]); // child 3 does not read on this pipe, it writes back to p2
  	write(fd4[1],"next",5); // first line written, wants moarrr
  	while((n = read(fd3[0],lineBuffer, MAXLINE)) != 0){
  		lineBuffer[n] = '\0';
  		if(strcmp("end", lineBuffer)==0){ // end of the line
  			fclose(fo);
			exit(0);
		}
		fprintf(fo, "%s\n", lineBuffer); // write the line
		write(fd4[1],"send", 5);
  	}
}

//From assignment3b:
char * returnLine(FILE *fp){  //returns line or NULL (if at end of file)
  char c;
  char *line;
  int size=0;
  line = NULL;
  line = realloc(line,sizeof(char));
  c = fgetc(fp);  //read in first char of first line of the file
  if (test_eof(c))  //at end of the file
    return NULL;
  while (!test_eol(c)){//read the line
    *(line+size) = c;
    size++;
    line = realloc(line,sizeof(char)* (size+1));
    c = fgetc(fp);
  }
  *(line+size) = '\0';
  return line;
}

//functions for reading from a file
int test_eol(char a){
  if (a == '\n')
    return 1;
  else
    return 0;
}
int test_eof(char a){
  if (a == EOF)
    return 1;
  else
    return 0;
}
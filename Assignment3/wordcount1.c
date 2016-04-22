/*
 *  wordcount1.c
 *  
 *
 *  Created by SIGNORILE,ROBERT P on 1/20/14.
 *  Copyright 2014 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

int test_eol(char a);
int test_eof(char a);
int change_state(int state,char a);
char * returnLine(FILE *fp);  //returns line or NULL (if at end of file)
void print_string(char *line);
  
int main() {
  char *line;
  FILE *fp;
  
  /* opening file for reading */
  fp = fopen("test_string" , "r");
  if(fp == NULL) {
    perror("Error opening file");
    return(-1);
  }
  
  line = returnLine(fp);
  while(line != NULL){
    print_string(line);
    line = returnLine(fp);//now you have a nice line, so play with it
  }
  fclose(fp);
  return 0;
}

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


void print_string(char *line){
  int i=0;
  while (*(line+i) != '\0'){
    printf("%c",*(line+i)); //no end of line
    i++;
  }
  printf("\n");
}

int test_eol(char a){
  if (a == '\n')
    return TRUE;
  else
    return FALSE;
}
int test_eof(char a){
  if (a == EOF)
    return TRUE;
  else
    return FALSE;
}

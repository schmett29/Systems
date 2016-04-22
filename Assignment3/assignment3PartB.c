
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "definitions.h"

  
int main() {
  char *line;
  String *S;
  stringContainer_t *scHead = NULL;
  wordContainer_t *wcHead = NULL;
  String * newString;
  word_t * W;
  FILE *fp;
  
  /* opening file for reading */
  fp = fopen("poem.txt" , "r");
  if(fp == NULL) {
    perror("Error opening file");
    return(-1);
  }
  
  line = returnLine(fp); //now you have a nice line, so play with it
  while(line != NULL){
    //printLine(line);
    newString = makeString(line);
    //printString(newString);
    scHead = insertStringIntoLinkedList(scHead, newString);
    line = returnLine(fp);//now you have a nice line, so play with it
  }
  fclose(fp);
  displayStringList(scHead);


  // Plan:
  // Add lines to stringContainer - file opener sets this up
  // Create words and add them to a linked list
  wcHead = createWordContainers(scHead);
  // Print out frequency of each word
  displayWordList(wcHead);
  // Print out max frequency
 

  /*
  stringContainer_t *templine;
  templine = scHead;
  char *theline;
  String *thestring;
  int i = 0;
  while(templine != NULL){
    thestring = templine->str;
    theline = thestring->stng;
    while(*(theline+i) != '\0'){
      if(*(theline+i) == ' ','!','.',','){
        *(theline+i) = '\0';
        W = createWord(theline);
        //but does the word already exist?
        if(wcHead == NULL){
          insertWordIntoLinkedList(wcHead, W);
          W->freq++;
          W->numberOfLines++;
          W->lineNumers = realloc(W->lineNumers, W->numberOfLines);
        }
        else{

        }
      }
    }


    templine =scHead->next;
    i++;
  }


  displayWordList(wcHead); //will print out line numbers and frequency
  */ //old strategie was too confusing and giving segmentation faults, so i broke it down into smaller
     // functions in the definitions.c
  return 0;
}
#include "definitions.h"

//functions for reading from a file
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


void printLine(char *line){
  int i=0;
  while (*(line+i) != '\0'){
    printf("%c",*(line+i)); //no end of line
    i++;
  }
  printf("\n");
}


//functions for creating a String
String * makeString(char * s) //pass in a pointer to a block of chars
{
  String *new = (String *) malloc (sizeof(String)); //create memory for String
  new->stng = (char *) malloc(sizeof(char) * strlen(s)); //create memory for chars in String
  strcpy(new->stng,s);  //copy the passsed chars to field in String
  new->len = strlen(new->stng);
  return new; //return filled in Sreing struct
}

void printString(String *s){
  char * c;
  int i=0;
  c = s->stng;  //point to the start of the chars in the String struct
  
  while (*(c+i) != '\0'){
    printf("%c",*(c+i)); //no end of line
    i++;
  }
  printf("\n");
}


int stringLength(String *s)
{
  return s->len;
}

wordContainer_t * insertWordIntoLinkedList(wordContainer_t * head, word_t * newWord){
  //insert new Sting at the end of list
  wordContainer_t *q;
  wordContainer_t * newContainer;
  newContainer = (wordContainer_t *) malloc(sizeof(wordContainer_t *));
  newContainer->wd = newWord;
  newContainer->next = NULL;
  if (head == NULL){
    head = newContainer;
    return head;
  }
  q = head;
  while (q->next != NULL){
    q=q->next;
  }
  q->next = newContainer;
  return head;
}

stringContainer_t * insertStringIntoLinkedList(stringContainer_t * head, String * newString){
  //insert new Sting at the end of list
  stringContainer_t *q;
  stringContainer_t * newContainer;
  newContainer = (stringContainer_t *) malloc(sizeof(stringContainer_t *));
  newContainer->str = newString;
  newContainer->next = NULL;
  if (head == NULL){
    head = newContainer;
    return head;
  }
  q = head;
  while (q->next != NULL){
    q=q->next;
  }
  q->next = newContainer;
  return head;
}

void displayStringList(stringContainer_t * head){
  String *r;
  stringContainer_t * temp;
  if (head == NULL){
    printf("NO STRINGS IN THIS LIST\n");
    return;
  }
  temp = head;
  /*
   no need to reserve memory here, r will point to
   memory locations that are reserved for the linked list
   */
  
  printf("the list of LINES are:\n");
  while (temp != NULL){
    r = temp->str;
    printString(r);  //see above function
    temp=temp->next;
  }
  //printf("\n");
  return;
}


//functions for creating a word
word_t * createWord(char * w){
  word_t * temp;
  int size;
  
  temp = malloc(sizeof(word_t));
  temp->length = strlen(w);
  temp->w = (char *) malloc(sizeof(char)*temp->length);
  temp->freq =1;
  temp->lineNumers =0;
  temp->lineNumers = (int*) malloc(sizeof(int)*temp->numberOfLines); //this is the number of lines in which the
  //word appears (you need this to realloc space for lineNumers
  for (size=0;size<temp->length;size++)
    *(temp->w + size) = *(w + size);
  return temp;
}

wordContainer_t * createWordContainers(stringContainer_t *newContainer){
  wordContainer_t *start;
  start = NULL;
  char *text;
  int i = 0; // which line
  while(newContainer != NULL){
    start = newLine(start, newContainer->str, i);
    newContainer = newContainer->next; //loops through string containers (lines)
    i++;
  }

}

wordContainer_t * newLine(wordContainer_t *wc, String *s, int lineNumber){
  wordContainer_t = *temp;
  word_t = *newWord;
  int i = 0;
  char = s->stng;
  while(*(s+i) != '\0'){
      if(*(s+i) == ' ','!','.',','){
        *(s+i) = '\0';
        newWord = createWord(s+i);
        //but does the word already exist?
        if(wc == NULL){
          insertWordIntoLinkedList(wcHead, W);
          newWord->freq++;
          newWord->numberOfLines++;
          newWord->lineNumers = realloc(W->lineNumers, W->numberOfLines);
 //INCOMPLETE - COME BACK TO THIS
}

void printWord(word_t *m){
  int i=0,j=0;
  char *c;
  c = m->w; //point to the start of the chars in the word struct
  
  while (*(c+i) != '\0'){
    printf("%c",*(c+i)); //no end of line
    i++;
  }
  printf("\n");
  printf("The word occurs %i time(s)\n", m->freq);
  printf("The word occurs on line(s): ");
  for(j; j < m->numberOfLines; j++){
    printf("%i ", *(m->lineNumers+j));
  }
  printf("\n");
  return;
}


void displayWordList(wordContainer_t * head){
  word_t *r;
  wordContainer_t * temp;
  if (head == NULL){
    printf("NO WORDS IN THIS LIST\n");
    return;
  }
  temp = head;
  /*
   no need to reserve memory here, r will point to
   memory locations that are reserved for the linked list
  */
  
  printf("the list of words are:\n");
  while (temp != NULL){
    r = temp->wd;
    printWord(r);  //see above function
    temp=temp->next;
  }
  printf("\n");
  return;
}

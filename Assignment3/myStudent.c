/*
 *  myStudent.c
 *  
 *
 *  Created by Robert Signorile on 2/14/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */

#include "myStudent.h"

char * getline(){
	int i=0; 
	char c;
	char *ptr; 	
	ptr = (char *) malloc(sizeof(char));
	c = getchar(); 
	while (c != '\n') { 
		*(ptr+i) = c;
		//printf("p[%d] = %c",i,*(ptr+i));
		c = getchar(); 
		i++; 
		ptr = (char *) realloc(ptr,sizeof(char)*i+1);
	} 
	//printf("i: %d\n",i);
	*(ptr+i)='\0'; 
	//printf("length: %d\n",strlen(ptr));
	return ptr; 
} 


student_t * createStudent(int age, char * name, int major, float gpa){ 
	student_t *s = (student_t *) malloc(sizeof(student_t)); 
	char * n;
	s->name = (char *) malloc(sizeof(strlen(name)+1));
	s->age = age;
	
	strcpy(s->name,name); 
	//printf("length s->name: %d\n",strlen(s->name));
	s->major = major;
	s->gpa = gpa;
	s->link = NULL;
	return s; 
} 

void insertStudent(student_t ** head,student_t * newStudent ){
	newStudent->link = *head;
	*head = newStudent;
}

void insertStudentRear(student_t ** head, student_t * newStudent ){
	student_t * temp;
	temp = *head;
	if (temp == NULL){
		*head = newStudent;
		return;
	}
	while(temp->link != NULL){
		temp = temp->link;
	}
	temp->link =  newStudent;
	return;
}

void deleteStudent(student_t ** s, char * oldStudent){
	student_t *temp1, *temp2;
	temp1 = *s;
	int found = 0;
	if (strcmp(temp1->name,oldStudent) == 0){  //remove first node in LL
		temp2 = temp1->link;
		temp1 = temp2;
		*s = temp1;
		return;
	}
	temp2 = temp1;  //have a trailer pointer to point to node in LL before the node we and to remove
	temp1 = temp1->link;  //since we are not deleting first node, move to second node
	while(temp1 != NULL){
		if (strcmp(temp1->name,oldStudent) == 0){ //found node to remove
			temp2->link = temp1->link; //have link field in node before the node we want to remove skip over the node being removed
			free(temp1);   //free up deleted node
			temp1 = temp2;
			found = 1;
			//return;  //all done, go back
			}
		temp2 = temp1;  //have a trailer pointer to point to node in LL before the node we and to remove
		temp1 = temp1->link;  //since we are not deleting first node, move to second node
	}
	//if (temp1 == NULL){
	if (found == 0)
		printf("Student %s is not in linked list\n ",oldStudent);
	}
    return;
}

void changeName( student_t *s, char *newname){ 
	strcpy(s->name, newname); 
} 


char * toString( student_t * s){ 
	char info[100], *result; 
	sprintf(info, "Student %s is %d years old, gpa: %f, major:%d\n", s->name, s->age, s->gpa, s->major); 
	result = (char *)malloc(strlen(info)+1); 
	strcpy(result, info); 
	return result; 
} 

char * getName( student_t *s){  
	return s->name;  // shorthand for (*s).name 
} 


int getAge( student_t *s){ 
	return s->age; 
} 

void setAge( student_t *s,int age){
	s->age =age;
}

void setGpa( student_t *s, float gpa){
	s->gpa =gpa;
}


float getGpa( student_t *s){
	return s->gpa; 
}

void setMajor( student_t *s,int major){
	s->major = major;
}


int getMajor( student_t *s){
	return s->major; 
}

student_t * findStudent( student_t *head, char *name){
	student_t * temp;
	temp = head;
	while(temp != NULL){
		if (strcmp(temp->name,name) == 0){ //found node 
			return temp;  //return node
		}
		temp = temp->link;
	}
	return NULL; //not found
}

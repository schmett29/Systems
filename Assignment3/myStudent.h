/*
 *  myStudent.h
 *  
 *
 *  Created by Roert Signorile on 2/14/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define max 20

//#define TRUE 1
//#define FALSE 0

typedef enum {FALSE=0, TRUE = !FALSE} bool;

typedef struct student { 
	int age; 
	char * name;
	float gpa;
	int major;
	struct student *link;
}student_t; 

char *getline(); 
student_t * createStudent(int age, char *name, int major, float gpa);
void insertStudentRear(student_t ** head,student_t * oldStudent );
void insertStudent(student_t ** head, student_t * newStudent);
void changeName( student_t *s, char *newname); 
char * toString( student_t * s); 
char * getName( student_t *s);
int getAge( student_t *s);
void setAge( student_t *s,int age);
void setGpa( student_t *s, float gpa);
float getGpa( student_t *s);
void setMajor( student_t *s, int major);
int getMajor( student_t *s);
student_t * findStudent( student_t *head, char *name);
void deleteStudent(student_t ** s, char * newStudent);
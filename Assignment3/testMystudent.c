/*
 *  testMystudent.c
 *  
 *
 *  Created by Robert Signorile on 2/14/15.
 *  Copyright 2015 __MyCompanyName__. All rights reserved.
 *
 */


#include "myStudent.h"

int menu();

int main(){
	student_t *head, *newStudent,*temp;
	int age,major; 
	float gpa;
	char * name, *name1, cr;
	char *msg;
	int i;
	int answer,data;
	
	head = NULL;
	printf("You are now entering the student zone!\n");

	answer = menu();
	while(answer != 7){
		switch (answer) {
			case 1:
				printf("enter age:\n");
				scanf("%d%c",&age,&cr);
				printf("enter gpa:\n");
				scanf("%f%c",&gpa,&cr);
				printf("enter major:\n");
				scanf("%d%c",&major,&cr);
				printf("enter name:\n");
				name = getline();
				//printf("length: %d\n",strlen(name));
				newStudent = createStudent(age, name,major,gpa);
				break;
			case 2:
				insertStudent(&head,newStudent);
				break;
			case 3:
				printf("enter student name to delete\n");
				name1 = getline();
				deleteStudent(&head,name1);
				free(name1);
				break;
			case 4:
				printf("enter student name to investigate\n");
				name1 = getline();
				data = dataMenu();
				switch (data) {
					case 1:
						temp = findStudent(head, name1);
						if(temp == NULL){
							printf("Student %s not found \n",name1);
							break;
						}
						age = getAge( temp);
						printf("The age of %s, is %d\n",name1,age);
						break;
					case 2:
						temp = findStudent(head, name1);
						if(temp == NULL){
							printf("Student %s not found \n",name1);
							break;
						}
						gpa = getGpa( temp);
						printf("The gpa of %s, is %f\n",name1,gpa);					
						break;
					case 3:						
						temp = findStudent(head, name1);
						if(temp == NULL){
							printf("Student %s not found \n",name1);
							break;
						}
						major = getMajor( temp);
						printf("The gpa of %s, is %d\n",name1,major);					
						break;
						
					default:
						break;
				}
				break;
			case 5:
				temp = head;
				while(temp != NULL){
					msg = toString( temp);
					printf("%s\n",msg);
					temp = temp->link;
				}
				break;
			case 6:
				insertStudentRear(&head,newStudent);
				break;			
			default:
				break;
		}
		answer = menu();
	}
	printf("BYE\n");
	return(0);

}

int menu(){
	int choice;
	char cr;
	printf("what would you like to do?\n");
	printf(" 1. enter student data\n 2. insert student into front of LL\n 3. Delete a student\n 4. Find student data\n 5. Print Linked list\n 6. Insert student at end of LL\n 7. Go Away\n");
	scanf("%d%c",&choice,&cr);
	while (choice <0 || choice > 7){
		printf("BAD BAD BAD, what would you like to do?\n");
		printf(" 1. enter student data\n 2. insert student into LL\n 3. Delete a student\n 4. Find student data\n 5. Print Linked list\n,6. Insert student at end of LL\n 7. Go Away\n");
		scanf("%d%c",&choice,&cr);
	}
	return choice;
}
int dataMenu(){
	int pickOne;
	char cr, *name1;
	printf("now, what data about the student do you want?\n");
	printf(" 1. age\n 2. gpa\n 3. major\n");
	scanf("%d%c",&pickOne,&cr);
	while (pickOne <0 || pickOne > 3){
		printf("BAD BAD BAD, what data about the student do you want?\n");
		printf(" 1. age\n 2. gpa\n 3. major\n");
		scanf("%d%c",&pickOne,&cr);
	}
	return pickOne;
}
	

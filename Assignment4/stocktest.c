/*
David Schmetterling
Section 02
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "doubly_linked_list.h"
#include "stock.h"

main(){
	node_t *p, *head, *tail, *q, *w, *e;
	FILE *fp;
	stock_t *s1,*s2,*s3,*s4;
	char stockSymbol[20];
	char closingSharePrice[20];
	char openingSharePrice[20];
	char numberOfShares[20];
	int success, ans;
	float price;
	head = NULL;
	tail = NULL;
	node_t LL = defaultList();
	fp = fopen("stocks", "r");
	if(fp == NULL){
        puts("file reading error");
        exit( EXIT_FAILURE );
    }
	
	while(!feof(fp)){
		fscanf(fp, "%s %s %s %s", stockSymbol, closingSharePrice, openingSharePrice, numberOfShares);
		// create new stocks
		s1 = newStock(&stockSymbol,closingSharePrice,closingSharePrice,openingSharePrice,numberOfShares);
		node_t * theNode = newNode(s1);
		insert_front(LL,theNode);

		// create new nodes
	}
	//printf("%p\n", s1->stockSymbol);
	
	//fpclose(fp);
	//printf("%p\n", stockSymbol);

	ans = menu();
	while(1){
		switch(ans){
			case 1:
				puts("Enter closing price:")
				scanf("%f", &price);
				puts("\n");


				break;
			case 2:
				//some code
				break;
			case 3:
				//some code
				break;
			case 4: //leave and free memory
				 while(head != NULL){
				 	p = head;
				 	head = (*head).next;
				 	free(p);
				 }
				puts("Memory freed");
				puts("Goodbye");
				exit(1);
				break;
			default:
				puts("Please enter a number 1-4");
				break
		}
		puts("\n");
		ans = menu();
	}
}

int menu(){
  int a;
  puts("welcome to fun C");
  puts("please choose from the following choices");
  puts("1. Search/print stock with closing price > some amount");
  puts("2. Search/print stock with % change  > some amount ");
  puts("3. List all the stocks using toString");
  puts("4. Quit and leave");
  scanf("%d", &a);
  return a;
}// You may add other nice features.
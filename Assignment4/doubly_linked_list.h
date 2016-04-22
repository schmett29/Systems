/*
David Schmetterling
Section 02
*/


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 20

//some fun definitons for the doubly linked list
typedef struct node{
		void * item;
		struct node * next;
		struct node * prev;
	}node_t;
/*
1. insert a node at the end of the list
2. traverse the list using the next field (a forward traversal)
3. delete a node from the list
4. traverse the list using the prior field (a backward traversal)
5. return a the item from a particular node in the list
6. anything else you want
*/

node_t * insert_front(node_t *head, node_t *newItem);
//1
node_t * insert_rear(node_t *tail, node_t *head, node_t *newItem);
//2
node_t * traverseForward(node_t *head);
//3
node_t * deleteIt(node_t *head, node_t *tail, node_t *theItem, int *success);
//4
node_t * traverseBackward(node_t *tail);
//5
void displayItem(node_t *theItem, node_t *head);

node_t * defaultList();
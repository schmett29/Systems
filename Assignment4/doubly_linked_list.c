/*
David Schmetterling
Section 02
*/

#include "doubly_linked_list.h"

node_t * defaultList(){
	node_t *head = (node_t *)malloc(sizeof(node_t));
	node_t *tail = (node_t *)malloc(sizeof(node_t));
	tail->prev = head;
	head->next = tail;
	head->prev = NULL;
	tail->next = NULL;
}

node_t* newNode(void * S){
	node_t *p = (node_t *)malloc(sizeof(node_t));
	p->item = S;
	p->next = NULL;
	p->prev = NULL;
}

node_t * insert_front(node_t *head, node_t *newItem){
	node_t *h;
	if(head == NULL){
		return newItem;
	}
	h = head;
	newItem->next = h;
	head = h;
	return head;
}

node_t * insert_rear(node_t *tail, node_t *head, node_t *newItem){
	node_t *t;
	if(head == NULL){
		return newItem;
	}
	t = tail;
	newItem->prev = t;
	tail = t;
	return head;
}

// Gives you the tail
node_t * traverseForward(node_t *head){
	node_t *p;
	p = head;
	void *d = p->item;
	if(head == NULL){
		printf("%s\n", "No linked list");
		return;
	}
	while(p->next != NULL){
		p = p->next;
	}
	return p;
}

// Assume theItem exists
node_t * deleteIt(node_t *head, node_t *tail, node_t *theItem, int *success){
	node_t *p, *q, *t;
	p = head;
	t = tail;
	q = p;
	//Check to see if there is a linked list
	if(head == NULL){
		puts("No linked list");
		*success = 0;
		return NULL;
	}
	// Other: could be first node, last node, or in beteween
	while(p != NULL){
		if(head == p){ // want to delete first node
			head = head->next;
			free(p);
			*success = 1;
			return head;
		}
		else if(p->next == NULL){ // want to delete last node
			q->next = NULL;
			free(p);
			*success = 1;
			return head;
		}
		else{ // want to delete in the middle
			//temp = p->next;
			//temp->prev = q;
			q->next = p->next;
			free(p);
			*success = 1;
			return head;
		}
		q = p;
		p = p->next;
	}
	//node was not found
	*success = 0;
	return head;
}

// Gives you the head
node_t * traverseBackward(node_t *tail){
	node_t *p;
	p = tail;
	if(tail == NULL){
		printf("%s\n", "No linked list");
		return;
	}
	while(p->prev != NULL){
		p = p->prev;
	}
	return p;
}

void displayItem(node_t *theItem, node_t *head){
	node_t *p;
	void *d;
	p = head;
	d = theItem->item;
	//Check to see if there is a linked list
	if(head == NULL){
		puts("No linked list");
	}
	// Parse though until you find it
	while(p != NULL){
		if(theItem->item == p->item){
			printf("%p\n", d);
		}
		p = p->next;
	}
}

node_t *datagent(){
	node_t *p;
	p = (node_t *) malloc(sizeof(node_t));
	p->next = NULL;
	p->prev = NULL;
	return p;
}



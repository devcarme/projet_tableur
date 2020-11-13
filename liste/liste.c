/* ---------------------------------------------------
 * Entete et macro pour la gestion de pile
 * les elements doivent etre affectables
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
//typedef struct node node_t;

node_t * list_create(void){
	return (node_t *)NULL;
}

void * list_get_data(const node_t * node){
	if(node == NULL){
		return NULL;
	}
	return node->value;
}

void list_set_data(node_t *node, void *data){
	node->value = data;
}

node_t * list_next(node_t * node){
	return node->next;
}

node_t * list_insert(node_t * head, void * data){
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->value = data;
	n->next = head;
	return n;
}

node_t * list_append(node_t * head, void * data){
	node_t *n = (node_t *)malloc(sizeof(node_t));
	n->value = data;
	n->next = NULL;
	if(head == NULL) return n;
	
	node_t *copy = head;
	while (copy->next != NULL){
		copy = copy->next;
	}
	copy->next = n;
	
	return head;
}

node_t * list_remove(node_t * head, void * data){
	if (head == NULL) return NULL;
	
	node_t *copy = head;
	
	while (copy->next != NULL){
		if(copy->value == data){
			copy->next = copy->next->next;
		}
		copy = copy->next;
	}
	
	return head;
}

node_t * list_headRemove(node_t * head){
	if (head == NULL) return NULL;
	return head->next;
}

void list_destroy(node_t * head){
	node_t *copy = head;
	while (copy->next != NULL){
		free(copy);
		copy = copy->next;
	}
	free(head);
}

void list_affichage(node_t * head){
	node_t *copy = head;
	while (copy->next != NULL){
		int *p = list_get_data(copy);
		printf("%d ", *p);
		copy = copy->next;
	}
	printf("\n\n");
}

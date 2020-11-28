/* ---------------------------------------------------
 * Fonctions du module cellule
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"
#include "cellule.h"
#include "../stack/stack.h"
#define SIZE_OPERATOR 4

const char operator[SIZE_OPERATOR] = {'+','-','/','*'};
const char * separator = ",/";

int isOperator(char c){
	int trouve = 0;
	int i = 0;
	while (i < SIZE_OPERATOR && trouve == 0){
		if(operator[i] == c){
			trouve = 1;
		}
		i++;
	}
	return trouve;
}

node_t * evaluation_cellule(s_cell * cellule, node_t * list){
	s_token * t = (s_token*)malloc(sizeof(s_token));
	char saisie[10];
	int pos, val, val_pile;
	int trouve = 0;
	strcpy(saisie, cellule->chaineSaisie);
	printf("%s\n",saisie);
	char *tok = strtok(saisie, separator);
	
	
	while(tok != NULL){
		printf(" %s\n", tok);
		
		if((int)*tok == *tok){ //Si c'est un int
			t->type = VALUE;
			t->value.cst = *tok;
		} else if (tok[1] == NULL){ //Si c'est un opérateur
			if (isOperator(*tok)){
				t->type = OPERATOR;
				switch(*tok){
					case '+' : t->value.cst = 1;
						break;
					case '-' : t->value.cst = 2;
						break;
					case '/' : t->value.cst = 3;
						break;
					case '*' : t->value.cst = 4;
						break;
					default : t->value.cst = 0;
						break;
					}
				}		
			} else{ //Si c'est une reférence à une cellule
				node_t *tmp = list; 
				while (tmp != NULL && trouve == 0){
					s_cell *ce = tmp->value;
					if(strcmp(ce->chaineSaisie,tok)){
						t->type = REF;
						t->value.ref = ce;
						trouve = 1;
					} 
					tmp = tmp->next;
				}
			}
		 
		cellule->listeJeton->value = t;
		cellule->listeJeton = cellule->listeJeton->next;
		tok = strtok(NULL, separator);
	}
	node_t *n = (node_t *)malloc(sizeof(node_t));//fonction list_insert
	n->value = cellule;
	n->next = list;
	
	return n;
}

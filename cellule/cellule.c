/* ---------------------------------------------------
 * Fonctions du module cellule
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../liste/liste.h"
#include "cellule.h"
#include "../stack/stack.h"
#define SIZE_OPERATOR 4

const char operator[SIZE_OPERATOR] = {'+','-','/','*'};
const char * separator = " ";

s_cell * cellule_create(char *chaine){
	s_cell * cell = (s_cell*)malloc(sizeof(s_cell));
	cell->chaineSaisie = chaine;
	cell->listeJeton = list_create();
	cell->next = NULL;
	cell->val = 0;
}

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

void * evaluation_cellule(s_cell * cellule, node_t * list){
	s_token * t = (s_token*)malloc(sizeof(s_token));
	char saisie[10];
	int pos, val, val_pile, trouve = 0;
	strcpy(saisie, cellule->chaineSaisie);
	char *tok = strtok(saisie, separator);
	char *ptr;
	
		
	while(tok != NULL){
		double tokDouble = atof(tok);
		double ret = strtod(saisie, &ptr);
		if (ret == tokDouble){ //Si c'est un double
			printf("%f\n",tokDouble);
			t->type = VALUE;
			t->value.cst = tokDouble;
		} else if (isOperator(*tok)){ //Si c'est un opérateur
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
		cellule->listeJeton = list_insert(cellule->listeJeton, t);
		tok = strtok(NULL, separator);
	}
	list = list_insert(list, cellule); 
}

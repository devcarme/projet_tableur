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
const char * separator = {" "};

s_cell * cellule_create(char *chaine){
	s_cell * cell = (s_cell*)malloc(sizeof(s_cell));
	cell->chaineSaisie = chaine;
	cell->listeJeton = list_create();
	cell->next = NULL;
	cell->val = 0;

	return cell;
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

void affichage_cellule(s_cell * cell){
	char ptr[10];
	strcpy(ptr, cell->chaineSaisie);
	printf("Affichage de cellule\n");
	printf("Chaine saisie : %s\n",ptr);
	printf("Valeur de la cellule : %f\n",cell->val);
	printf("Affichage des jetons de la cellule\n");

	if(cell->listeJeton == NULL){
		 printf("La liste est vide\n\n");
		 return;
	}
	if(cell->listeJeton->next == NULL){
		s_token *tok = cell->listeJeton->value;
		printf("%f\n\n", tok->value.cst);
		return;
	}
	
	node_t *copy = cell->listeJeton;
	while (copy != NULL){
		s_token * tokeneu = copy->value;
		printf("%f JETON VALUE \n", tokeneu->value.cst);
		copy = copy->next;
	}

	}


s_cell * evaluation_cellule(s_cell * cellule, node_t * list){
	char ptr[10];
	int pos, val, val_pile, trouve = 0;
	strcpy(ptr, cellule->chaineSaisie) ;
	printf("SALUT CHAINE SAISIE %s\n",ptr);
	char *tok = strtok(ptr, separator);
	
	
		
	while(tok != NULL){
		double val = 0;
		s_token * t = (s_token*)malloc(sizeof(s_token));
		if (sscanf(tok,"%lf", &val) == 1){ //Si c'est un double
			printf("%f DOUBLE\n",val);
			t->type = VALUE;
			t->value.cst = val;
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
		s_token * tokeneu = cellule->listeJeton->value;
		printf("%f JETON VALUE \n", tokeneu->value.cst);
		tok = strtok(NULL, separator);
	}
	
	return cellule; 
}

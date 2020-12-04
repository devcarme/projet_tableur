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

void affichage_token(s_token * token){
	printf("TYPE : ");
	switch(token->type){
		case 0: printf("VALUE ");
				printf(" VALUE : %f\n",token->value.cst);
			break;
		case 1: printf("REF ");
				printf(" Cellule référencée\n");
				affichage_cellule(token->value.ref);
			break;
		case 2: printf("OPERATOR ");
			break;
		default: printf("Erreur typage token");
			break;	
	}
	
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
		affichage_token(tok);
		return;
	}
	
	node_t *copy = cell->listeJeton;
	while (copy != NULL){
		s_token * tokeneu = copy->value;
		affichage_token(tokeneu);
		copy = copy->next;
	}
	printf("\n");
}


s_cell * evaluation_cellule(s_cell * cellule, node_t * list){
	char ptr[10];
	int pos, val, val_pile, trouve = 0, premierToken = 1;
	strcpy(ptr, cellule->chaineSaisie) ;
	char *tok = strtok(ptr, separator);
	double ret;
	char *ptr2;
  	ret = strtod(tok, &ptr2);
	
	while(tok != NULL){
		double val = 0;
		s_token * t = (s_token*)malloc(sizeof(s_token));
		if (sscanf(tok,"%lf", &val) == 1){ //Si c'est un double
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
			} else if(strcmp(ptr2,"C") == 0 && strcmp(tok,ptr2) == 0 ){ //Si c'est une reférence à une cellule
   				node_t *tmp = list; 
				int i = 0;
				s_cell *ce = tmp->value;
				while (tmp != NULL && i < ret){
					ce = tmp->value;
					tmp = tmp->next;
					i++;
				}
				if(tmp != NULL){
					t->type = REF;
					t->value.ref = ce;
					cellule->next = ce;	
				}
			} else{
				printf("Erreur sur la chaine saisie de la cellule\n");
				return cellule;
			}

			if(premierToken){
				cellule->listeJeton = list_insert(cellule->listeJeton, t);
				premierToken = 0;
			}else{
				cellule->listeJeton = list_append(cellule->listeJeton, t);
			}
			tok = strtok(NULL, separator);
		}
	return cellule; 
}

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

char operator[SIZE_OPERATOR] = {'+','-','/','*'};
const char * separator = {" "};
extern s_calcul_sheet *feuille_calcul;

s_cell * cellule_create(char *chaine, char * nom){
	s_cell * cell = (s_cell*)malloc(sizeof(s_cell));
	cell->chaineSaisie = chaine;
	cell->nom = nom;
	cell->listeJeton = list_create();
	cell->succs = list_create();
	cell->val = 0;
	cell->degre_negatif = 0;

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
		case 2: printf("OPERATOR \n");
			break;
		default: printf("Erreur typage token");
			break;	
	}
	
}

void affichage_cellule(s_cell * cell){
	char ptr[45];
	strcpy(ptr, cell->chaineSaisie);
	printf("Affichage de cellule\n");
	printf("Chaine saisie : %s\n",ptr);
	printf("Valeur de la cellule : %f\n",cell->val);
	printf("Degré négatif de la cellule : %d\n",cell->degre_negatif);
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
}


s_cell * evaluation_cellule(s_cell * cellule){
	char c, ptr[45];
	double l;
	int val;
	strcpy(ptr, cellule->chaineSaisie) ;
	char *tok = strtok(ptr, separator);
	
	while(tok != NULL){
		double val = 0;
		s_token * t = (s_token*)malloc(sizeof(s_token));
		if (sscanf(tok,"%lf", &val) == 1){ //Si c'est un double
			t->type = VALUE;
			t->value.cst = val;
		} else if (isOperator(*tok)){ //Si c'est un opérateur
			t->type = OPERATOR;
				switch(*tok){
					case '+' : t->value.operator = &add;
						break;
					case '-' : t->value.operator = &substract;
						break;
					case '/' : t->value.operator = &divise;
						break;
					case '*' : t->value.operator = &multiply;
						break;
					}
			} else if(sscanf(tok, "%[A-Z]%lf",&c,&l) == 2){ //Si c'est une reférence à une cellule
   				node_t *tmp = feuille_calcul->listCellule;
				s_cell *ce = tmp->value;
				if(tmp->next == NULL && strcmp(tok, ce->nom) == 0){
					ce = tmp->value;
				}
				while (tmp->next != NULL && strcmp(tok, ce->nom) == 0){
					ce = tmp->value;
					tmp = tmp->next;
				}
				if (strcmp(tok, ce->nom) != 0){
					printf("La cellule %s n'existe pas\n",tok);
					return cellule;
				}else{
					ce->succs = list_insert(ce->succs,cellule);
					cellule->degre_negatif++;
					t->type = REF;
					t->value.ref = ce;
				}
			} else{
				printf("Erreur sur la chaine saisie de la cellule\n");
				return cellule;
			}

			if(cellule->listeJeton == NULL){
				cellule->listeJeton = list_insert(cellule->listeJeton, t);
			}else{
				cellule->listeJeton = list_append(cellule->listeJeton, t);
			}
			
			tok = strtok(NULL, separator);
		}
	return cellule; 
}

void add(my_stack_t *stack){
	double val = 0;
	double val2 = 0;
	STACK_POP2(stack, val, double);
	STACK_POP2(stack, val2, double);
	STACK_PUSH(stack, val + val2, double);
}

void divise(my_stack_t *stack){
	double val = 0;
	double val2 = 0;
	STACK_POP2(stack, val, double);
	STACK_POP2(stack, val2, double);
	STACK_PUSH(stack, val2 / val, double);
}

void multiply(my_stack_t *stack){
	double val = 0;
	double val2 = 0;
	STACK_POP2(stack, val, double);
	STACK_POP2(stack, val2, double);
	STACK_PUSH(stack, val * val2, double);
}

void substract(my_stack_t *stack){
	double val = 0;
	double val2 = 0;
	STACK_POP2(stack, val, double);
	STACK_POP2(stack, val2, double);
	STACK_PUSH(stack, val2 - val, double);
}

void traitementCellule(s_cell * cell){
	my_stack_t * stack = STACK_CREATE(32,double);
	node_t *list = cell->listeJeton;
	while(list != NULL){
		s_token *token = list->value;
		switch (token->type){
			case 0:
				STACK_PUSH(stack, token->value.cst, double);
				break;
			case 1:
				STACK_PUSH(stack, token->value.ref->val, double);
				break;
			case 2:
				((token->value.operator)(stack));
			default:
				break;
		}
		list = list->next;
	}
	STACK_POP2(stack, cell->val, double);
}
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
#define SIZE_OPERATOR 5

char *operator[SIZE_OPERATOR] = {"+","-","/","*","mod"};
const char * separator = {" "};
extern s_calcul_sheet *feuille_calcul;

s_cell * cellule_create(char *chaine, char * nom){
	node_t *tmp = feuille_calcul->listCellule;
	int trouve = 0;
	while(tmp != NULL){
		s_cell *tmpCell = tmp->value;
		if(strcmp(tmpCell->nom,nom) == 0){ //Si le nom de cellule existe déjà
			printf("La cellule %s existe déjà, sa chaîne est donc modifiée\n", nom);
			feuille_calcul->listCellule = list_remove(tmp,tmpCell);
			tmpCell->chaineSaisie = chaine;
			tmpCell->listeJeton = list_create();
			trouve = 1;
			return tmpCell;
		}
		tmp = tmp->next;
	}
	if(!trouve){
		s_cell * cell = (s_cell*)malloc(sizeof(s_cell));
		cell->chaineSaisie = chaine;
		cell->nom = nom;
		cell->listeJeton = list_create();
		cell->succs = list_create();
		cell->val = 0;
		cell->degre_negatif = 0;
		return cell;
	}

}

int isOperator(char *c){
	int trouve = 0;
	int i = 0;
	while (i < SIZE_OPERATOR && operator != NULL && trouve == 0){
		if(strcmp(operator[i],c)==0){
			trouve = 1;
		}
		i++;
	}
	return trouve;
}

void affichage_token(s_token * token){
	printf("JETON TYPE -> ");
	switch(token->type){
		case 0: printf("VALUE ");
				printf("-> %.2f\n",token->value.cst);
			break;
		case 1: printf("REF ");
				printf("-> %s\n",token->value.ref->nom);
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
	printf("CELLULE %s\n",cell->nom);
	printf("Chaine saisie ->  %s\n",ptr);
	printf("Valeur de la cellule ->  %.2f\n",cell->val);
	printf("Degré négatif : %d\n",cell->degre_negatif);
	printf("--Liste des jetons--\n");

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


s_cell * evaluation_cellule(s_cell * cellule){
	char c, ptr[45];
	char * stringValue, egal;
	double l, doubleValue;
	int val;
	strcpy(ptr, cellule->chaineSaisie) ;
	char *tok = strtok(ptr, separator);
	if(sscanf(tok,"%[=]",&egal)){//Si c'est une formule
		tok = strtok(NULL, separator);
		while(tok != NULL){
			double val = 0;
			s_token * t = (s_token*)malloc(sizeof(s_token));
			
			if (sscanf(tok,"%lf", &val) == 1){ //Si c'est un caractère représentant des chiffres
				t->type = VALUE;
				t->value.cst = val;
			} else if (isOperator(tok)){ //Si c'est un opérateur
				t->type = OPERATOR;
				if(strcmp(tok,"+") == 0){
					t->value.operator = &add;
				} else if(strcmp(tok,"-") == 0){
					t->value.operator = &substract;
				} else if(strcmp(tok,"/") == 0){
					t->value.operator = &divise;
				} else if(strcmp(tok,"*") == 0){
					t->value.operator = &multiply;
				} else if(strcmp(tok,"mod") == 0){
					t->value.operator = &mod;
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
		}else if(sscanf(tok,"%lf",&doubleValue) == 1){
			cellule->val = doubleValue;
		} else if(sscanf(tok,"%s",stringValue) == 1){
			printf("Le chaine est stockée dans le champe 'chaineSaisie'\n");
		}else{
			printf("Erreur sur la chaine saisie\n");
			return cellule;
		}
		if(LIST_EMPTY(feuille_calcul->listCellule)){
			feuille_calcul->listCellule = list_insert(feuille_calcul->listCellule, cellule);
		} else{
			feuille_calcul->listCellule = list_append(feuille_calcul->listCellule, cellule);
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

void mod(my_stack_t *stack){
	double val = 0;
	double val2 = 0;
	STACK_POP2(stack, val, double);
	STACK_POP2(stack, val2, double);
	STACK_PUSH(stack, (int)val2 % (int)val, double);
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

void affichageListCelluleFeuilleCalcul(){
	printf("Affichage de toutes les cellules de la liste présente dans feuille de calcul\n\n");
	node_t *copy = feuille_calcul->listCellule;
	while (copy != NULL){
		s_cell *p = list_get_data(copy);
		affichage_cellule(p);
		printf("\n");
		copy = copy->next;
	}
}
/* ---------------------------------------------------
 * Test du module cellule
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


#define SIZE_OPERATOR = 3;


int main(){
	char  chaine[] = "1,2,+,4";
	s_cell *cellule;
	cellule = (s_cell *)malloc(sizeof(s_cell));
	cellule->chaineSaisie = chaine;
	cellule->val = 0;
	cellule->listeJeton = (node_t *)malloc(sizeof(node_t));
	
	printf("%s\n",cellule->chaineSaisie);
	node_t * listCellule = (node_t *)NULL;
	listCellule = (node_t *)malloc(sizeof(node_t));
	
	node_t *liste = (node_t *)malloc(sizeof(node_t));//fonction list_insert
	liste->value = cellule;
	liste->next = listCellule;
	
	liste = evaluation_cellule(cellule, liste);
	
	
	
	char addition = '+';
	printf("Test fonction isOperator avec +\n");
	printf("%d\n",isOperator(addition));
	
	printf("Affichage des jetons de la cellule\n");
	s_cell * cel = liste->value;
	while (cel->listeJeton != NULL){
		s_token *tok = cel->listeJeton->value; 
		printf(" %d",tok->value.cst);
		cel->listeJeton = cel->listeJeton->next;
	}
	printf("\n");
	
	return 0;

}

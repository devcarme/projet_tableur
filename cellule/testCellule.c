/* ---------------------------------------------------
 * Test du module cellule
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


#define SIZE_OPERATOR = 3;


int main(){
	char  chaine[] = "4 2 /";
	char  chaine2[] = "2 5 * C1";
	s_cell *cellule = cellule_create(chaine);
	s_cell *cellule2 = cellule_create(chaine2);
	node_t *listCellule = list_create();

	char addition = '+';
	printf("Test fonction isOperator avec +\n");
	printf("%d\n",isOperator(addition));
	
	cellule = evaluation_cellule(cellule, listCellule);
	listCellule = list_insert(listCellule, cellule);
	cellule2 = evaluation_cellule(cellule2, listCellule);
	listCellule = list_append(listCellule, cellule2);
	
	node_t *copy = listCellule;
	while (copy != NULL){
		s_cell *p = list_get_data(copy);
		affichage_cellule(p);
		printf("\n");
		copy = copy->next;
	}

	traitementCellule(cellule);
	affichage_cellule(cellule);

	return 0;

}

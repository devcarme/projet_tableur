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
	char  chaine[] = "1 2 +";
	s_cell *cellule = cellule_create(chaine);

	
	node_t *listCellule = list_create();
	cellule = evaluation_cellule(cellule, listCellule);
	affichage_cellule(cellule);
	listCellule = list_insert(listCellule, cellule);
	
	
	printf("\n\n");
	
	
	//list_affichage(cellule->listeJeton);
	
	char addition = '+';
	printf("Test fonction isOperator avec +\n");
	printf("%d\n",isOperator(addition));
	
	return 0;

}

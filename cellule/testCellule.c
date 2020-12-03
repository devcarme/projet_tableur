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
	char  chaine[] = "1 2 + 4";
	s_cell *cellule = cellule_create(chaine);

	
	node_t *listCellule = list_create();
	listCellule = list_insert(listCellule, cellule); 
	evaluation_cellule(cellule, listCellule);
	
	printf("%f\n",atof("blabla"));

	printf("Affichage des jetons de la cellule\n");
	if(cellule->listeJeton == NULL){
		 printf("La liste est vide\n\n");
	}
	if(cellule->listeJeton->next == NULL){
		double *p = list_get_data(cellule->listeJeton);
		printf("%f\n\n", *p);
	}
	
	node_t *copy = cellule->listeJeton;
	while (copy != NULL){
		double *p = list_get_data(copy);
		printf("%f ", *p);
		copy = copy->next;
	}
	printf("\n\n");
	
	
	//list_affichage(cellule->listeJeton);
	
	char addition = '+';
	printf("Test fonction isOperator avec +\n");
	printf("%d\n",isOperator(addition));
	
	printf("\n");
	
	return 0;

}

/* ---------------------------------------------------
 * Test du module cellule
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "cellule.h"
#include "../liste/liste.h"
#include "../stack/stack.h"

#define SIZE_OPERATOR = 3;

extern s_calcul_sheet * feuille_calcul;

int main(){
	char  chaine[] = "4 2 / 2 + 4 *";
	char  chaine2[] = "2 5 * A1 +";

	feuille_calcul = (s_calcul_sheet *)malloc(sizeof(s_calcul_sheet));
	feuille_calcul->nomFic = "tableur.txt";
	feuille_calcul->nbLignes = 50;
	feuille_calcul->nbColonnes = 26;
	feuille_calcul->listCellule = NULL;

	s_cell *cellule = cellule_create(chaine, "A1");
	s_cell *cellule2 = cellule_create(chaine2,"B1");

	char addition = '+';
	printf("Test fonction isOperator avec +\n");
	printf("%d\n",isOperator(addition));
	
	cellule = evaluation_cellule(cellule);
	feuille_calcul->listCellule = list_insert(feuille_calcul->listCellule, cellule);
	cellule2 = evaluation_cellule(cellule2);
	feuille_calcul->listCellule = list_append(feuille_calcul->listCellule, cellule2);

	printf("Traitement de la première cellule\n");
	traitementCellule(cellule);
	printf("Traitement de la deuxième cellule\n");
	traitementCellule(cellule2);


	printf("Affichage de toutes les cellules\n");
	node_t *copy = feuille_calcul->listCellule;
	while (copy != NULL){
		s_cell *p = list_get_data(copy);
		affichage_cellule(p);
		printf("\n");
		copy = copy->next;
	}

	return 0;
}

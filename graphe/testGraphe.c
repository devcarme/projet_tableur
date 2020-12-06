/* ---------------------------------------------------
 * Test du module cellule
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "../cellule/cellule.h"
#include "../liste/liste.h"
#include "../stack/stack.h"
#include "graphe.h"
#include "../cellule/cellule.h"
extern s_calcul_sheet *feuille_calcul; 

int main(){
	char  chaine[] = "4 2 / 2 + 4 *";
	char  chaine2[] = "2 5 * A1 +";

	feuille_calcul = (s_calcul_sheet *)malloc(sizeof(s_calcul_sheet));
	feuille_calcul->nomFic = "tableur.txt";
	feuille_calcul->nbLignes = 64;
	feuille_calcul->nbColonnes = 64;
	feuille_calcul->listCellule = NULL;

	s_cell *cellule = cellule_create(chaine, "A1");
	s_cell *cellule2 = cellule_create(chaine2,"B1");

	cellule = evaluation_cellule(cellule);
	feuille_calcul->listCellule = list_insert(feuille_calcul->listCellule, cellule);
	cellule2 = evaluation_cellule(cellule2);
	feuille_calcul->listCellule = list_append(feuille_calcul->listCellule, cellule2);

	tri_topologique(cellule2);

	return 0;

}

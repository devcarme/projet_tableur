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

extern char * operator;
extern s_calcul_sheet * feuille_calcul;

int main(){

	printf("TEST DU MODULE CELLULE\n\n");
	//Initialisation de la feuille de calcul
	feuille_calcul = (s_calcul_sheet *)malloc(sizeof(s_calcul_sheet));
	feuille_calcul->nomFic = "tableur.txt";
	feuille_calcul->nbLignes = 50;
	feuille_calcul->nbColonnes = 26;
	feuille_calcul->listCellule = NULL;

	char *addition = "+";
	printf("Test fonction isOperator avec +\n");
	printf("+ est un opérateur ? -> %d\n\n",isOperator(addition));

	char chaineFormule[] = "= 3 4 5 + *";
	char chaineFormuleModif[] = "= 4 2 2 - +";
	char chaineValeurNumerique[] = "255";
	char chaineFormuleRef[] = "= 10 4 mod A1 *";
	char simpleChaine[] = "Je suis une simple chaine";

	s_cell *celluleFormule = cellule_create(chaineFormule, "A1");
	s_cell *celluleNumerique = cellule_create(chaineValeurNumerique,"C2");
	s_cell *celluleFormuleRef = cellule_create(chaineFormuleRef,"B1");
	s_cell *celluleSimpleChaine = cellule_create(chaineFormuleRef,"Z5");

	printf("Evaluation de la chaine de la cellule A1, puis traitement(calcul)...\n");
	celluleFormule = evaluation_cellule(celluleFormule);
	traitementCellule(celluleFormule);
	printf("Résultat attendu pour A1 -> 3*(4+5) = 27\n");
	affichageListCelluleFeuilleCalcul();
	printf("On essaye d'ajouter une cellule du nom de A1\n");
	s_cell *celluleFormuleModif = cellule_create(chaineFormuleModif, "A1");
	celluleFormuleModif = evaluation_cellule(celluleFormuleModif);
	traitementCellule(celluleFormuleModif);
	affichageListCelluleFeuilleCalcul();
	

	printf("Evaluation des chaines saisies des cellules...\n\n");
	celluleFormuleRef = evaluation_cellule(celluleFormuleRef);
	celluleNumerique = evaluation_cellule(celluleNumerique);
	celluleSimpleChaine = evaluation_cellule(celluleSimpleChaine);

	printf("Traitement des cellules (calculs)...\n\n");
	traitementCellule(celluleFormuleRef);
	traitementCellule(celluleNumerique);
	traitementCellule(celluleSimpleChaine);

	printf("Résultat attendu pour A1 -> 4-2+2 = 4\n");
	printf("Résultat attendu pour C2 -> 255\n");
	printf("Résultat attendu pour B1 -> (10 modulo 4) * valeur(A1) soit 2*4 = 8\n");
	printf("Résultat attendu pour Z5 -> 0\n");
	affichageListCelluleFeuilleCalcul();

	
	return 0;
}

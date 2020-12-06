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
#include "../cellule/cellule.h"
#include "../stack/stack.h"
#include "graphe.h"
#define SIZE_OPERATOR 4

extern char operator[SIZE_OPERATOR];
extern const char * separator;
extern s_calcul_sheet *feuille_calcul;

void tri_topologique(s_cell *cellule_evaluee){
	node_t *sous_graphe_init = feuille_calcul->listCellule;
	node_t *list = list_create();
	node_t *tmp = feuille_calcul->listCellule;
	
	while(sous_graphe_init != NULL){
		s_cell *cellule_p = sous_graphe_init->value;
		node_t *succsesseurs = cellule_p->succs; 
		while(succsesseurs != NULL){
			s_cell *cp = succsesseurs->value;
			printf("CP NOM %s\n",cp->nom);
			printf("CelluleEvaluee NOM %s\n",cellule_evaluee->nom);
			if(strcmp(cp->nom , cellule_evaluee->nom)==0){
				printf("YYEEEES\n");
				cellule_p->degre_negatif++;
			}
			succsesseurs = succsesseurs->next;
		}
		
		// if(degre_negatif[i-1].degre < degre_negatif[i].degre){
		// 	s_degre_cell tmpDegre = degre_negatif[i];
		// 	degre_negatif[i] = degre_negatif[i-1];
		// 	degre_negatif[i-1] = tmpDegre;
		// }
		sous_graphe_init = sous_graphe_init->next;
	}
	
	list = feuille_calcul->listCellule;

	if(list == NULL){
		printf("Liste vide\n");
		return;
	}

	node_t *copy = list;
	while(copy != NULL){
		s_cell *tmpCell = list->value;
		printf("DEGRE CELLULE %s : %d  \n",tmpCell->nom,tmpCell->degre_negatif);
		copy = copy->next;
	}
	

	traitementCellule(list->value);

	list = list_headRemove(list);
}
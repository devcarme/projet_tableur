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
	//Initialisation 
	node_t *sous_graphe_init = cellule_evaluee->succs;
	node_t *list = list_create();

	//Le calcul des degrés est fait dans le module cellule

	// while(sous_graphe_init != NULL){
	// 	s_cell *copyCellule = sous_graphe_init->value;
	// 	node_t *copy = feuille_calcul->listCellule;
	// 	while(copy != NULL){
	// 		s_cell *copyCell = copy->value;
	// 		node_t *copyListeJeton = copyCell->listeJeton;
	// 			while(copyListeJeton != NULL){
	// 				s_token *copyToken = copyListeJeton->value;
	// 				if(copyToken->value.ref == copyCellule){
	// 					copyCellule->degre_negatif++;
	// 				}
	// 				copyListeJeton = copyListeJeton->next;
	// 			}
				
	// 		copy = copy->next;
	// 	}
	// 	sous_graphe_init = sous_graphe_init->next;
	// }
	
	list = list_insert(list, cellule_evaluee);
	printf("DEGRE NEGATIF %d\n",cellule_evaluee->degre_negatif);

	//Itération
	while(list != NULL){
		s_cell *cellTete = list->value;
		list = list_headRemove(list);
		traitementCellule(cellTete);
		while (cellTete->succs != NULL){
			s_cell *succ = cellTete->succs->value;
			succ->degre_negatif--;
			if(succ->degre_negatif == 0){
				list = list_insert(list,succ);
			}
			cellTete->succs = cellTete->succs->next; 
		}
	}
	if(list == NULL){
		printf("Liste vide, fin\n");
		return;
	}
}
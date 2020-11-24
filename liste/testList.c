/* -------------------------------------------------------------------
   Teste unitaire de la liste
   -------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

#define SIZE 5

int main(){
	printf("TEST DU MODULE LISTE\n\n");
	int tab[SIZE] = {0,1,2,3,4};
	int a = 6;
	int *p = &a;
	int val = 1;
	
	printf("Création de liste\n");
	node_t *list = list_create();
	
	printf("Insertion de 0 en tête de liste\n");
	list = list_insert(list, &tab[0]);
	
	printf("Test de la fonction list_append. Ajout de 1 2 3 4 en queue de liste\n");
	while(val < SIZE){
		LIST_APPEND(list, &tab[val], int);
		val++;
	}
	
	if  (!LIST_EMPTY(list))
		printf("liste vide : %d (attendu FAUX) \n", LIST_EMPTY(list));
	
	val = 0;
	node_t *listTmp = list;
	while(!LIST_EMPTY(listTmp)){
		int *pv = list_get_data(listTmp);
		printf("Valeur lue : %d (attendue %d)\n",*pv, tab[val]);
		listTmp = list_next(listTmp);
		val++;
	}
	
	
	printf("\nTest de la fonction list_headRemove pour vider toute la liste tête par tête\n");
	val = 5;
	while(val > 0){
		list = list_headRemove(list);
		val--;
	}
	
	if ( LIST_EMPTY(list))
		printf("liste vide : %d (attendu VRAI) \n", LIST_EMPTY(list));
	
	
	
	printf("On essaye d'écrire 1 dans la tête de liste\n");
	list_set_data(list,&tab[0]);
	
	printf("Test de la fonction list_next. On essaye de récupérer le noeud suivant la tête de liste \n");
	if (list_next(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("Test de la fonction list_remove. On essaye de retirer 1 à la liste \n");
	if (list_remove(list,&tab[0]) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("Test de la fonction list_headRemove. On essaye de retirer la tête de liste \n");
	if (list_headRemove(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("Test de la fonction list_append. On essaye d'ajouter 1 à la queue de liste \n");
	if (list_append(list, &tab[0]) == NULL){
		printf("La liste est vide\n\n");
	}
	
	
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	
	
	printf("DESTRUCTION DE LA LISTE\n");
	list_destroy(list);
	printf("FIN DU TEST\n");
	
	return 0;
}

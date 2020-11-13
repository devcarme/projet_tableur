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
	int tab[SIZE] = {1,2,3,4,5};
	int a = 6;
	int *p = &a;
	int val = 0;
	
	node_t *list = list_create();
	printf("La liste est créée. On essaye d'afficher la liste\n");
	list_affichage(list);
	
	printf("On essaye de récupérer la valeur de la tête de liste\n");
	if (list_get_data(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("On essaye d'écrire 1 dans la tête de liste\n");
	list_set_data(list,&tab[0]);
	
	printf("On essaye de récupérer le noeud suivant la tête de liste \n");
	if (list_get_data(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("On essaye de retirer 1 à la liste \n");
	if (list_remove(list,&tab[0]) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("On essaye de retirer la tête de liste \n");
	if (list_headRemove(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
	printf("Ajout de 1 2 3 4 à la liste\n");
	while(val < SIZE){
		list = list_append(list, &tab[val]);
		val++;
	}
	
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	
	printf("Insertion de 5 en tête de liste\n");
	list = list_insert(list, &tab[4]);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Suppression de 3 dans la liste\n");
	list = list_remove(list, &tab[2]);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("On essaye de supprimer le noeud dont la valeur est le pointeur p\n");
	list = list_remove(list, p);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Suppression de la tête de liste\n");
	list = list_headRemove(list);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("DESTRUCTION DE LA LISTE\n");
	list_destroy(list);
	printf("FIN DU TEST\n");
	
	return 0;
}

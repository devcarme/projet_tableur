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
	int val = 1;
	
	node_t *n = (node_t *)malloc(sizeof(node_t));
	list_set_data(n, &tab[4]);
	int *ptn = list_get_data(n);
	printf("Test des fonctions list_set_data et list_get_data\n");
	printf("On crée un noeud dont la valeur est un pointeur sur 5\n");
	printf("La valeur pointée par la valeur du noeud est : %d\n\n",*ptn);
	
	printf("Test de la fonction list_create\n");
	node_t *list = list_create();
	printf("On essaye d'afficher la liste\n");
	list_affichage(list);
	
	if ( LIST_EMPTY(list) == 0  )
		printf("liste vide : %d (attendu FAUX) \n", LIST_EMPTY(list));
	
	
	printf("On essaye de récupérer la valeur de la tête de liste\n");
	if (list_get_data(list) == NULL){
		printf("La liste est vide\n\n");
	}
	
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
	
	printf("Test de la fonction list_insert. Ajout de 1 en tête de liste\n");
	list = list_insert(list,&tab[0]);
	
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Test de la fonction list_append. Ajout de 2 3 4 en queue de liste\n");
	while(val < SIZE){
		list = list_append(list, &tab[val]);
		val++;
	}
	
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Test de la fonction list_next. Affichage du noeud suivant la tête de liste\n");
	int *pn = list_next(list)->value;
	printf("%d\n\n", *pn);
	
	
	printf("Test de la fonction list_insert. Insertion de 5 en tête de liste\n");
	list = list_insert(list, &tab[4]);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Test de la fonction list_remove. Suppression de 3 dans la liste\n");
	list = list_remove(list, &tab[2]);
	printf("Affichage de la liste\n");
	list_affichage(list);
	
	printf("Test de la fonction list_remove. On essaye de supprimer le noeud dont la valeur est le pointeur p\n");
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

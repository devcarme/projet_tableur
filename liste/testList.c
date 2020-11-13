/* -------------------------------------------------------------------
   Teste unitaire de la liste
   -------------------------------------------------------------------
*/
#include <stdio.h>
#include <stdlib.h>
#include "liste.h"

#define SIZE 5

int main(){
	int tab[SIZE];
	tab[0] = 1;
	tab[1] = 2;
	tab[2] = 3;
	tab[3] = 4;
	tab[4] = 5;
	int val = 0;
	node_t *list = list_create();
	
	while(val < SIZE){
		list = list_append(list, &tab[val]);
		val++;
	}
	printf("Ajout de 1 2 3 4 à la liste\nAffichage de la liste\n");
	list_affichage(list);
	list = list_insert(list, &tab[4]);
	printf("Insertion de 5 en tête de liste à la liste\nAffichage de la liste\n");
	list_affichage(list);
	
	/*int *p = list_get_data(list);
	printf("%d\n",*p);
	list = list_append(list, &b);
	list = list_remove(list, &b);
	list = list_headRemove(list);
	list_destroy(list);
	printf("DESTRUCTION DE LA LISTE\n");
	int *p2 = list_get_data(list);
	*/
	
	return 0;
}

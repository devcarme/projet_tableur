/* ---------------------------------------------------
 * Entete et macro pour la gestion des cellules, des 
 * formules et de leur évaluation
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */
#ifndef CELLULE_H
#define CELLULE_H

#include "../stack/stack.h"
#include "liste.h"

struct cell{
	char * chaineSaisie;
	double val;
	node_t * listeJeton;
	struct cell * next;
};
typedef struct cell s_cell;


typedef struct token{
	enum {VALUE, REF, OPERATOR} type;
	union{
			int cst;
			s_cell * ref;
			void (*operator) (my_stack_t * eval);
		} value;
}s_token;	

typedef struct calcul_sheet{
	char * nomFic;
	int nbLignes;
	int nbColonnes;
	s_cell * listCellule;
}calcul_sheet;

//fonction qui analyse la chaîne de caractère associée à une cellule (le contenu de la cellule)
node_t * evaluation_cellule(s_cell *, node_t *);
int isOperator(char);
// declarations des fonctions publics
node_t * list_create(void); 
//creation d'une nouvelle liste vide
void * list_get_data(const node_t *node);
void list_set_data(node_t *node, void *data);
//lire ou écrire la donnée d'un noeud
node_t * list_next(node_t * node); 
//obtenir le noeud suivant;
node_t * list_insert(node_t * head, void * data); 
//creation et insertion d'un noeud en tete de liste
//retourne la tete de liste
node_t * list_append(node_t * head, void * data);
//creation et ajout d'un noeud en queue de la liste
//retourne la tete de liste
node_t * list_remove(node_t * head, void * data);
//suppression de la premiere instance d'une 
//donnée dans la liste, retourne la tete de liste
node_t * list_headRemove(node_t * head);
//suppression de la tete de liste
//retourne la nouvelle tete de liste
void list_destroy(node_t * head);
//destruction d'une liste
//(la libération des données n'est pas prise en charge
void list_affichage(node_t * head);
//afichage de la liste
#endif

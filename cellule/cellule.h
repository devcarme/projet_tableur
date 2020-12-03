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
#include "../liste/liste.h"

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
void * evaluation_cellule(s_cell *, node_t *);
int isOperator(char);
s_cell * cellule_create(char *);
#endif

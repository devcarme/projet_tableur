/* ---------------------------------------------------
 * Entete et macro pour la gestion des cellules, des 
 * formules et de leur �valuation
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
			double cst;
			s_cell * ref;
			void (*operator) (my_stack_t * eval);
		} value;
}s_token;	

typedef struct calcul_sheet{
	char * nomFic;
	int nbLignes;
	int nbColonnes;
	node_t * listCellule;
}s_calcul_sheet;


//fonction qui analyse la cha�ne de caract�re associ�e � une cellule (le contenu de la cellule)
s_cell *evaluation_cellule(s_cell *);
//fonction qui détermine si un caractère est un opérateur
int isOperator(char);
//fonction pour initialiser une cellule
s_cell * cellule_create(char *);
//fonction affichage d'une cellule
void affichage_cellule(s_cell *);
//fonction affichage d'un token
void affichage_token(s_token *);
void add(my_stack_t *);
void divise(my_stack_t *);
void multiply(my_stack_t *);
void substract(my_stack_t *);
void traitementCellule(s_cell *);
#endif

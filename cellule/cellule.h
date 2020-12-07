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
	int degre_negatif;
	char * nom;
	char * chaineSaisie;
	double val;
	node_t * listeJeton;
	node_t * succs;
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
s_calcul_sheet *feuille_calcul; 

//fonction qui analyse la cha�ne de caract�re associ�e � une cellule (le contenu de la cellule)
s_cell *evaluation_cellule(s_cell *);
//fonction qui détermine si un caractère est un opérateur
int isOperator(char *);
//fonction pour initialiser une cellule
s_cell * cellule_create(char *, char *);
//fonction affichage d'une cellule
void affichage_cellule(s_cell *);
//fonction affichage d'un token
void affichage_token(s_token *);
//fonction addition
void add(my_stack_t *);
//fonction division
void divise(my_stack_t *);
//fonction multiplication
void multiply(my_stack_t *);
//fonction soustraction
void substract(my_stack_t *);
//fonction reste de division
void mod(my_stack_t *);
//fonction de traitement d'une cellule, qui affecte une valeur à la cellule selon la notation polonaise inversée
void traitementCellule(s_cell *);
//affichage des cellules dans la liste de la feuille de calcul
void affichageListCelluleFeuilleCalcul();
#endif

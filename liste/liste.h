/* ---------------------------------------------------
 * Entete et macro pour la gestion de liste
 * les elements doivent etre affectables
 * ---------------------------------------------------
 * L. Ducarme
 * ---------------------------------------------------
 */


struct node{
	void *value;
	struct node *next;
};
typedef struct node node_t;


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

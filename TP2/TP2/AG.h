#ifndef AG_H
#define AG_H
/* Classe AG qui permet de creer un arbre generale de noeuds
* Auteur: Edwin Andino
*/
#include <string>
#include "Noeud.h"
using namespace std;

class AG {
public:
	// Constructeur par défaut
	AG();
	// Constructeur avec un pointeur pour definir la racine
	AG(Noeud* ptr);
	// Destructeur
	~AG();
	
	//Permet d'obtenir la racine
	Noeud*& getRacine();

	// permet d'inserer un nouveau noeud dans l'arbre
	void inserer(Noeud* n, string mot, string def, int indice, int taille);
	
	// permet d'afficher l'arbre au complet
	void afficher(Noeud* n, string mot, string tmp, int i, int max, int util);

	// permet de trouver un mot dans l'arbre
	void rechercher(Noeud* n, string mot, int i);

private:
	Noeud* racine;
	bool verifier(Noeud* n, string mot, string def, int indice, int taille);
	void placerNoeud(Noeud* n, string mot, string def, int indice, int taille);
};
#endif;

#ifndef LISTEJOUEURS_H
#define LISTEJOUEURS_H

#include "NoeudJoueur.h"

using namespace std;

class ListeJoueurs {

public:
	ListeJoueurs();
	~ListeJoueurs();

	void ajouterFin(const Joueur& unJoueur);
	int getTaille() const;

	void iterationDebut() const;
	void iterationSuivant() const;
	const Joueur& iterationObtenir() const;
	Joueur& iterationObtenir();
	void iterationSupprimer();

private:
	NoeudJoueur* tete;
	NoeudJoueur* fin;
	mutable NoeudJoueur* iterateur;
	int taille;
};

#endif
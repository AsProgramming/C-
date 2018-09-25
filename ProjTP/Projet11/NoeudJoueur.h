#ifndef NOEUDJOUEUR_H
#define NOEUDJOUEUR_H

#include "Joueur.h"

using namespace std;

class NoeudJoueur {

public:
	NoeudJoueur(const Joueur& unJoueur);
	~NoeudJoueur();

	NoeudJoueur* getSuivant() const;
	void setSuivant(NoeudJoueur* noeud);
	const Joueur& getJoueur() const;
	Joueur& getJoueur();


private:
	NoeudJoueur *suivant;
	Joueur joueur;
};

#endif
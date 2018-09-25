#ifndef NOEUDCARTE_H
#define NOEUDCARTE_H

#include "Carte.h"

using namespace std;

class NoeudCarte {

public:
	NoeudCarte(const Carte& uneCarte);
	~NoeudCarte();

	NoeudCarte* getSuivant() const;
	void setSuivant(NoeudCarte* noeud);
	const Carte& getCarte() const;

private:
	NoeudCarte *suivant;
	Carte carte;
};

#endif

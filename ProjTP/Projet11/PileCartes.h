#ifndef PILECARTES_H
#define PILECARTES_H

#include "NoeudCarte.h"

using namespace std;

class PileCartes {

public:
	PileCartes();
	~PileCartes();

	const PileCartes& operator=(const PileCartes& pile);
	Carte retirerSommet();
	const Carte& getSommet() const;
	void ajouterCarte(const Carte& carte);
	int getTaille() const;
	void ajouterPile(const PileCartes& cartes);

private:
	NoeudCarte *tete;
	int taille;
};

#endif
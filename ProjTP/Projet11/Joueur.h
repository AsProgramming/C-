#ifndef JOUEUR_H
#define JOUEUR_H

#include <string>
#include "Carte.h"
#include "PileCartes.h"

using namespace std;

class Joueur {

public:
	Joueur();
	Joueur(const string& nom);
	~Joueur();

	// Accesseur et mutateur pour le nom
	void setNom(const string& nom);
	const string& getNom() const;

	// Gestion des cartes des joueurs
	int getNombreCartes() const;
	void ajouterCarte(const Carte& carte);
	Carte getProchaineCarte();
	void ajouterCartesSousPaquet(const PileCartes& cartes);

private:
	PileCartes cartes;
	string nom;
};

#endif
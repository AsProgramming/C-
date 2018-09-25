#include "Joueur.h"
#include "NoeudJoueur.h"

/*
	Methode qui cree un noeud de joueur avec un joueur passer en parametre
*/
NoeudJoueur::NoeudJoueur(const Joueur& unJoueur)
{
	joueur = unJoueur;
	suivant = nullptr;
}

/*
	Methode qui detruit le noeud de joueur
*/
NoeudJoueur::~NoeudJoueur()
{

}

/*
	Methode qui retourne le noeud de joueur suivant
*/
NoeudJoueur* NoeudJoueur::getSuivant() const
{
	return suivant;
}

/*
	Methode qui determine le prochain le noeud de joueur
*/
void NoeudJoueur::setSuivant(NoeudJoueur* noeud)
{
	suivant = noeud;
}

/*
	Methode qui retourne le joueur dans le noeud de joueur sans qu'il puisse etre changer
*/
const Joueur& NoeudJoueur::getJoueur() const
{
	return joueur;
}

/*
	Methode qui retourne le joueur dans le noeud de joueur
*/
Joueur& NoeudJoueur::getJoueur()
{
	return joueur;
}
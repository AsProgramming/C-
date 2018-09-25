#include "Carte.h"
#include "NoeudCarte.h"

/*
	Methode qui cree un noeud de carte vide detruit le noeud de carte
*/
NoeudCarte::NoeudCarte(const Carte& uneCarte)
{
	carte = uneCarte;
	suivant = nullptr;
}

/*
	Methode qui detruit le noeud de carte
*/
NoeudCarte::~NoeudCarte()
{

}

/*
	Methode qui retourne le noeud de carte suivant
*/
NoeudCarte* NoeudCarte::getSuivant() const
{
	return suivant;
}

/*
	Methode qui cree le lien du noeud de la carte suivante
*/
void NoeudCarte::setSuivant(NoeudCarte* noeud)
{
	this->suivant = noeud;
}

/*
	Methode qui retourne la carte dans le noeud
*/
const Carte& NoeudCarte::getCarte() const
{
	return carte;
}
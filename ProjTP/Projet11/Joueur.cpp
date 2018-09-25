#include "Joueur.h"
#include "Carte.h"
#include "PileCartes.h"

/*
	Methode qui initialise un joueur vide
*/
Joueur::Joueur() :
	cartes(),
	nom()
{

}

/*
	Methode qui initialise un joueur avec un nom mais paquet vide
*/
Joueur::Joueur(const string& n)
{
		cartes;
		nom = n;
}

/*
	Methode qui detruit un joueur
*/
Joueur::~Joueur()
{

}

/*
	Methode qui met nom au joueur 
*/
void Joueur::setNom(const string& nom)
{
	this->nom = nom;
}

/*
	Methode qui retourne le nom du joueur sans qu'il puisse etre changer
*/
const string& Joueur::getNom() const
{
	return nom;
}

/*
	Methode qui retourne le nombre de cartes du joueur sans qu'il puisse etre changer
*/
int Joueur::getNombreCartes() const
{
	return cartes.getTaille();
}

/*
	Methode qui ajoute une carte au joueur
*/
void Joueur::ajouterCarte(const Carte& carte)
{
	cartes.ajouterCarte(carte);
}

/*
	Methode qui retourne la prochaine carte du joueur
*/
Carte Joueur::getProchaineCarte()
{
	return cartes.retirerSommet();
}

/*
	Methode qui ajoute un paquet de carte en dessous de la pile actuel
*/
void Joueur::ajouterCartesSousPaquet(const PileCartes& c)
{
	cartes.ajouterPile(c);
}
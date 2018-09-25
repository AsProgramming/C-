#include "NoeudJoueur.h"
#include "ListeJoueurs.h"

/*
	Methode qui initialise une liste de joueurs vide
*/
ListeJoueurs::ListeJoueurs() :
	tete(0),
	fin(0),
	iterateur(0),
	taille(0)
{

}

/*
	Methode qui detruit la liste de joueur
*/
ListeJoueurs::~ListeJoueurs()
{

}

/*
	Methode qui ajoute un joueur a fin de la liste
*/
void ListeJoueurs::ajouterFin(const Joueur& unJoueur)
{	
	NoeudJoueur *nouveau = new NoeudJoueur(unJoueur);
	if (tete == nullptr) {
		tete = nouveau;
		tete->setSuivant(tete);
	}else {
		fin->setSuivant(nouveau);
		nouveau->setSuivant(tete);
	}
	fin = nouveau;
	taille++;
}

/*
	Methode qui retourne la taille de la liste
*/
int ListeJoueurs::getTaille() const
{
	return taille;
}

/*
	Methode qui met l'iterateur au debut de la liste
*/
void ListeJoueurs::iterationDebut() const
{
	iterateur = tete;
}

/*
	Methode qui deplace l'iterateur sur le joueur suivant
*/
void ListeJoueurs::iterationSuivant() const
{
	iterateur = iterateur->getSuivant();
}

/*
	Methode qui retourne le Joueur, qui ne peut etre changer, pointer par l'iterateur
*/
const Joueur& ListeJoueurs::iterationObtenir() const
{
	return  iterateur->getJoueur();
}

/*
	Methode qui retourne le Joueur par reference pointer par l'iterateur
*/
Joueur& ListeJoueurs::iterationObtenir()
{
	return iterateur->getJoueur();
}

/*
	Methode qui supprime le Joueur pointer par l'iterateur
*/
void ListeJoueurs::iterationSupprimer()
{
	NoeudJoueur* tmp = iterateur;
	NoeudJoueur* avant = tete;
	if (iterateur == tete) {
		tete = iterateur->getSuivant();
		fin->setSuivant(tete);
		iterateur = tete;
	}
	else if(iterateur == fin){
		while (avant->getSuivant() != iterateur) {
			avant = avant->getSuivant();
		}
		avant->setSuivant(iterateur->getSuivant());
		fin = avant;
		iterateur = tete;
	}
	else {
		while (avant->getSuivant() != iterateur) {
			avant = avant->getSuivant();
		}
		avant->setSuivant(iterateur->getSuivant());
		iterateur = avant;
	}
	delete tmp;
	if (tete == nullptr) {
		fin = nullptr;
	}
	taille--;
	
}
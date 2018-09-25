#include "NoeudCarte.h"
#include "PileCartes.h"

using namespace std;

/*
	Methode qui cree une pile de carte vide
*/
PileCartes::PileCartes() :
	tete(0),
	taille(0)
{

}

/*
	Methode qui detruit la pile de carte
*/
PileCartes::~PileCartes()
{

}

/*
	Methode qui cree une pile a partir d'une autre pile ( en reference de une pile x = une pile z)
*/
const PileCartes& PileCartes::operator=(const PileCartes& pile)
{
	while (tete != nullptr)
	{
		NoeudCarte* tmp = tete;
		tete = tete->getSuivant();
		delete tmp;
	}
	taille = 0;
	NoeudCarte* curseurOriginal = 0;
	NoeudCarte* curseurCopie = 0;
	if (pile.tete != 0)
	{
		tete = new NoeudCarte(pile.tete->getCarte());
		curseurCopie = tete;
		curseurOriginal = pile.tete->getSuivant();
	}

	while (curseurOriginal != 0)
	{
		NoeudCarte* nouveau = new NoeudCarte(curseurOriginal->getCarte());
		curseurCopie->setSuivant(nouveau);
		curseurCopie = nouveau;
		curseurOriginal = curseurOriginal->getSuivant();
	}
	taille = pile.taille;
	return *this;
}

/*
	Methode qui retire le sommet de la pile de carte
*/
Carte PileCartes::retirerSommet()
{
	Carte tmp;
	if (tete != nullptr) {
		tmp = Carte(tete->getCarte());
		NoeudCarte* n = tete;
		tete = tete->getSuivant();
		delete n;
	}
	taille--;
	return tmp;
}

/*
	Methode qui retourne le sommet de la pile de carte
*/
const Carte& PileCartes::getSommet() const
{
	return tete->getCarte();
}

/*
	Methode qui ajoute une carte a la pile de carte
*/
void PileCartes::ajouterCarte(const Carte& carte)
{
	NoeudCarte* nouveau = new NoeudCarte(carte);
	nouveau->setSuivant(tete);
	tete = nouveau;
	taille++;
}

/*
	Methode qui retourne la taille de la pile de carte
*/
int PileCartes::getTaille() const
{
	return taille;
}

/*
	Methode qui ajoute une pile de cartes en dessous de l'autre
*/
void PileCartes::ajouterPile(const PileCartes& cartes)
{
	if (tete == nullptr) {
		*this = cartes;
	}
	else {
		NoeudCarte* curseur = tete;
		while (curseur->getSuivant() != nullptr) {
			curseur = curseur->getSuivant();
		}
		NoeudCarte* tmp = cartes.tete;
		while (tmp != nullptr) {
			curseur->setSuivant(new NoeudCarte(tmp->getCarte()));
			curseur = curseur->getSuivant();
			tmp = tmp->getSuivant();
		}
		taille += cartes.getTaille();
	}
}
#include "Carte.h"
#include <string>

/*
	Methode qui cree une carte a partir d'une autre carte
*/
Carte::Carte(const Carte& carte) :
	id(carte.id)
{

}

/*
	Methode qui met l'id de la carte passer en parametre
*/
Carte::Carte(const string& id) :
	id(id)
{

}

/*
	Methode qui detruit la carte
*/
Carte::~Carte()
{

}

/*
	Methode qui cree une carte a partir d'une autre carte ( en reference de une carte x = une carte z)
*/
const Carte& Carte::operator=(const Carte& autreCarte)
{
	this->id = autreCarte.id;
	return *this;
}

/*
	Methode qui met l'id de la carte passer en parametre
*/
void Carte::setID(const string& id) {
	this->id = id;
}

/*
	Methode qui retourne l'id de la carte
*/
const string& Carte::getID() const
{
	return id;
}

/*
	Methode qui retourne la valeur de la carte
*/
char Carte::getValeur() const
{
	char valeur = id[0];
	return valeur;
}
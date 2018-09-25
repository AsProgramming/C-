#include "Noeud.h"

typedef list<Noeud*>::iterator iterateur;

Noeud::Noeud()
{
	lettre = NULL;
	definition = "";
	fils;
}

Noeud::Noeud(char& valeur)
{
	lettre = valeur;
	definition;
	fils;
}


Noeud::Noeud(char& valeur, string& def)
{
	lettre = valeur;
	definition = def;
	fils;
}


Noeud::~Noeud()
{
	// Rien à faire ici
}
// Met la lettre dans le noeud
void Noeud::setLettre(char& valeur)
{
	this->lettre = valeur;
}
// Met la definition dans le noeud
void Noeud::setDefinition(string& nouvelle)
{
	this->definition = nouvelle;
}
// Met le pointeur de noeud dans la liste par ordre croissant
void Noeud::setFils(Noeud*& ptr)
{
	iterateur i = fils.begin();

	if (fils.size() == 0) {
		fils.insert(i, ptr);
	}
	else {
		Noeud* tmp = *i;
		while (i != fils.end() && tmp->getLettre() < ptr->getLettre()) {
			i++;
			if (fils.size() > 1 && i != fils.end()) {
				tmp = *i;
			}
		}
		fils.insert(i, ptr);
	}
}
// Retourne le pointeur du fils
list<Noeud*> Noeud::getFils() const
{
	//for pour trouver les autres mots avec iterateur
	return fils;
}
// Retourne la definition du noeud
string Noeud::getDefinition() const
{
	return definition;
}
// Retourne la lettre du noeud
char Noeud::getLettre() const
{
	return lettre;
}
// Retourne vrai si la est vide sinon false
bool Noeud::estVide()
{
	return (fils.size() == 0) ? true : false;
}
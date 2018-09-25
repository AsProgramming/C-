#include "AG.h"
#include "UtilES.h"
#include <iostream>


using namespace std;
typedef list<Noeud*>::iterator it;

AG::AG()
{
	racine = new Noeud();
}

AG::~AG()
{
	// Rien à faire ici
}

Noeud*& AG::getRacine()
{
	return racine;
}
// Met un nouveau mot dans l'arbre
void AG::inserer(Noeud* n, string mot, string def, int i,int dernier)
{
	if (n->estVide()) {
		placerNoeud(n, mot, def, i, dernier);
	}
	else {
		bool doublon = verifier(n, mot, def, i, dernier);
		if (!doublon) {
			placerNoeud(n, mot, def, i, dernier);
		}
	}
}

void AG::placerNoeud(Noeud* n, string mot, string def, int i, int dernier)
{
	Noeud *nouveau = new Noeud(mot[i]);
	if (i == dernier && n->getDefinition() == "") {
		nouveau->setDefinition(def);
		n->setFils(nouveau);
	}
	else if (i == dernier && n->getDefinition() != "") {
		if (nouveau->getLettre() == n->getLettre()) {
			string remplacer = ajusterDef(n->getDefinition());
			if (remplacer == "o") {
				n->setDefinition(def);
			}
		}
		else {
			nouveau->setDefinition(def);
			n->setFils(nouveau);
		}

	}
	else {
		n->setFils(nouveau);
		inserer(nouveau, mot, def, i + 1, dernier);
	}
}

//////REUTILISER POUR VERIFIER MOT AJOUTER INDICE DANS LES ARGS
bool AG::verifier(Noeud* n, string mot, string def, int i, int dernier)
{
	list<Noeud*> l = n->getFils();
	for (it iter = l.begin(); iter != l.end(); iter++)
	{
		Noeud* tmp = *iter;
		if (mot[i] == tmp->getLettre()) {
			if (i != dernier) {
				inserer(tmp, mot, def, i + 1, dernier);
			}
			else if (i == dernier) {
				inserer(tmp, mot, def, i, dernier);
			}
			return true;
		}
	}
	return false;
}
// Met le pointeur de noeud dans la liste
void AG::rechercher(Noeud* n, string mot, int i)
{
	int dernier = mot.length() - 1;
	bool pasTrouver = true;
	list<Noeud*> l = n->getFils();
	int verifier = l.size();
	for (it iter = l.begin(); iter != l.end(); iter++)
	{
		Noeud* tmp = *iter;
		if (mot[i] == tmp->getLettre()) {
			if (tmp->getDefinition() != "" && i == dernier) {
				affichage(tmp->getDefinition());
			}
			else if (i == dernier || tmp->estVide()) {
				pasTrouver = true;
				verifier--;
			}
			else
			{
				pasTrouver = false;
				rechercher(tmp, mot, i + 1);
			}
		}
		else {
			verifier--;
		}
	}
	if (pasTrouver && i == l.size()|| 
		pasTrouver && i == 0 
		|| pasTrouver && verifier == 0) {
			affichage("Ce mot n'existe pas dans ce lexique");
	}
}

void AG::afficher(Noeud* n, string mot, string tmp, int indice, int max, int util)
{
	Noeud* ptr;
	int verifier = -1;
	bool pasTrouver = true;

	list<Noeud*> l = n->getFils();
	for (it i = l.begin(); i != l.end(); i++)
	{
		ptr = *i;
		if (max != 0 && mot[indice] == ptr->getLettre()) {
			pasTrouver = false;
			tmp.push_back(ptr->getLettre());
			afficher(ptr, mot, tmp, indice + 1, max, util);
			if (ptr->getDefinition() != "" && tmp.size() == max) {
				if (util == 1) {
					affichage(tmp);
				}
				else {
					sauvegarder(tmp, ptr->getDefinition());
				}
			}
		}
		else if(indice == max){
			pasTrouver = false;
			tmp.push_back(ptr->getLettre());
			afficher(ptr, mot, tmp, max, max, util);
			if (ptr->getDefinition() != "") {
				if (util == 1) {
					affichage(tmp);
				}
				else {
					sauvegarder(tmp, ptr->getDefinition());
				}
			}
			else {
				tmp.pop_back();
			}
		}
		else {
			verifier--;
		}
	}
	if (pasTrouver && verifier < -1) {
		tmp = "Ce terme n'existe pas dans le lexique";
		affichage(tmp);
	}
}
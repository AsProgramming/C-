#include <iostream>
#include <cstdio>
#include <algorithm>
#include <Windows.h>
#include <fstream>
#include "UtilES.h"
#include "AG.h"

using namespace std;
static string fichier;

AG& lireFichier(string);
string* decouper(string);
void creerArbre(string*, AG&);
char decouperMot(string);
void action(AG&, int);
void sauverDonnees(AG&);

void main() {

	fichier = demanderFichier();

	AG arbre = lireFichier(fichier);

	int choix = 0;
	while (choix != 4) {
		choix = menu();
		action(arbre, choix);
	}
	sauverDonnees(arbre);

}

AG& lireFichier(string nomFichier){
	AG arbre = AG();
	ifstream fichier;
	string* tab = new string[2];
	string ligne, test;

	fichier.open(nomFichier);
	
	while (!fichier.eof()) {
		getline(fichier, ligne);
		tab = decouper(ligne);
		creerArbre(tab, arbre);
	}
	return arbre;
}

string* decouper(string ligne) {
	string* tab = new string[2];
	int signet = ligne.find(" : ");

	tab[0] = ligne.substr(0, signet);
	signet += 3;
	tab[1] = ligne.substr(signet);

	return tab;
}

void creerArbre(string* tab, AG& arbre) {
	string mot = tab[0];
	string def = tab[1];
	int taille = mot.size() - 1;

	arbre.inserer(arbre.getRacine(), mot, def, 0, taille);
}

void action(AG& ag, int choix) {
	string* verifier;
	string recherche, leMot;
	switch (choix) {
		case 1:
			verifier = demanderAjout();
			creerArbre(verifier, ag);
			break;
		case 2:
			recherche = demanderMot();
			ag.rechercher(ag.getRacine(), recherche, 0);
			system("pause");
			break;
		case 3:
			leMot = afficherMot();
			ag.afficher(ag.getRacine(), leMot, "", 0, leMot.size() , 1);
			system("pause");
			break;

	}
}

void sauverDonnees(AG& ag) {
	ag.afficher(ag.getRacine(), "", "", 0, 0, 2);
	ifstream ancien("tmp.txt");
	ofstream nouveau(fichier);
	string ligne;
	while (!ancien.eof()) {
		getline(ancien, ligne);
		nouveau << ligne << endl;
	}
	ancien.close();
	nouveau.close();
	remove("tmp.txt");
}

#include <iostream>
#include <string>
#include <Windows.h>
#include <cstdlib>
#include <regex>
#include <cstdio>
#include <fstream>
#include <iomanip>
#include "PileCartes.h"
#include "ListeJoueurs.h"

using namespace std;

#define MAX 48
#define REGEXNB "[2-4]{1}"
#define REGEXALEA "^[1-9]{1}[0-9]{0,1}"
#define REGEXNOM "^[A-Z]{1}[a-z]+||[a-z]+"
#define REGEXFICHIER "^[A-Z]{1}[a-z]+[0-9]*||^[a-z]+[0-9]*||^[a-z]+"
#define AFFICHEFICHIER "Entrez le nom du fichier (sans extension): "
#define AFFICHENB "Entrez un nombre pour le germe aleatoire:"
#define AFFICHEERR "Le nom du fichier est non valide\nVeuillez recommencer\n"
#define ERREURNB "Le nombre doit etre entre 1 et 100 (non-inclus)\nVeuillez recommencer\n"
#define AFFICHEJOUEUR "Entrez le nombre de joueurs:"
#define ERREURJOUEUR "Le nombre de joueurs doit etre entre 2 et 4\nVeuillez recommencer\n"
#define AFFICHENOM "Entrez le nom du joueur "
#define ERREURNOM "Pour le nom la premiere lettre peut etree majuscule mais ne doit avoir que des lettres\nVeuillez recommencer\n"
static int quelJoueur = 1;
static int germe = 1;

string* creationPaquet();
void brasserPaquet(string*, int, int);
PileCartes conversion(string *, int);
void brasserPaquetVoler(PileCartes&);
int demanderValeurs(int);
string demanderNom();
ListeJoueurs& distribuerCarte(int, PileCartes);
void debutJeu(PileCartes&, ListeJoueurs&, string);
int bataille(int, PileCartes&, ListeJoueurs&, ofstream&);
void tenterVole(PileCartes&, char, Carte, ListeJoueurs&, string, ofstream&);
void viderMillieu(PileCartes&, ListeJoueurs&);
void prendreLaCarte(PileCartes&, ListeJoueurs&);
void joueurAvantVole(PileCartes&, ListeJoueurs&, int, int, string, ofstream&);
string demanderFichier();

void main() {

	ListeJoueurs lesJoueurs;
	PileCartes paquet, millieu;
	string fichier;
	string* m;

	int germe = demanderValeurs(1);

	fichier = demanderFichier();

	int nbJoueurs = demanderValeurs(0);

	m = creationPaquet();
	brasserPaquet(m, germe, MAX);
	paquet = conversion(m, MAX);

	lesJoueurs = distribuerCarte(nbJoueurs, paquet);

	debutJeu(millieu, lesJoueurs, fichier);

	system("pause");

}

/*
Methode qui initialise le paquet a distribuer pour la partie
retourne un tableau de string (le paquet de cartes initiliaser
*/
string* creationPaquet()
{
	string* brasser = new string[48];
	string s, suite;
	int lng = 14;
	int k = 0;
	for (int i = 0; i < 4; i++) {

		for (int j = 2; j < lng; j++) {

			switch (i) {
			case 1:
				suite = "P";
				break;
			case 2:
				suite = "A";
				break;
			case 3:
				suite = "T";
				break;
			default:
				suite = "C";
				break;
			}

			switch (j) {
			case 9:
				s = "X";
				break;
			case 10:
				s = "V";
				break;
			case 11:
				s = "D";
				break;
			case 12:
				s = "R";
				break;
			case 13:
				s = "A";
				break;
			default:
				s = to_string(j);
				break;
			}
			brasser[k] = (s + suite);
			k++;
		}
	}

	return brasser;
}

/*
Methode qui brasse les cartes
*/
void brasserPaquet(string* paquet, int germe, int total)
{
	srand(germe);

	for (int i = 0; i < total; i++)
	{
		int num = rand() % total;
		string tmp = paquet[i];
		paquet[i] = paquet[num];
		paquet[num] = tmp;
	}
}

/*
Methode qui converti le paquet de carte en string en Paquet de carte
retourne la Pile de cartes
*/
PileCartes conversion(string * p, int total) {
	PileCartes paquet;
	Carte c;
	for (int i = 0; i < total; i++)
	{
		c = Carte(p[i]);
		paquet.ajouterCarte(c);
	}
	return paquet;
}

/*
Methode qui converti la pile de carte en string pour le brassage
*/
void brasserPaquetVoler(PileCartes& p) {
	int taille = p.getTaille();
	int rendu = 0;
	string* brasser = new string[48];
	string carte;
	Carte c;
	for (int i = 0; i < taille; i++)
	{
		c = Carte(p.retirerSommet());
		carte = c.getID();
		brasser[rendu] = carte;
	}
	brasserPaquet(brasser, germe, taille);
	p = conversion(brasser, taille);
}

/*
Methode qui demande a l'utilisateur le nombre de joueurs pour la partie
retourne le numero entre par l'utilisateur
*/
int demanderValeurs(int leBon)
{
	string ligne;
	bool valide = true;
	int nombre;
	while (valide) {
		if (leBon == 0) {
			cout << AFFICHEJOUEUR;
		}
		else {
			cout << AFFICHENB;
		}

		getline(cin, ligne);

		if (ligne.size() < 1) {
			if (leBon == 0) {
				cout << ERREURJOUEUR;
			}
			else {
				cout << ERREURNB;
			}

			valide = true;
		}
		else {

			if (leBon == 0) {
				valide = regex_match(ligne, regex(REGEXNB));
			}
			else {
				valide = regex_match(ligne, regex(REGEXALEA));
			}


			if (!valide && leBon == 0) {
				cout << ERREURJOUEUR;
				valide = true;
			}
			else if (!valide && leBon == 1) {
				cout << ERREURNB;
				valide = true;
			}
			else {
				nombre = stoi(ligne);
				valide = false;
			}
		}

	}
	return nombre;
}


/*
Methode qui demande a l'utilisateur le nom des joueurs pour la partie
retourne le nom du joueur
*/
string demanderNom()
{
	string ligne;
	ListeJoueurs liste;
	bool valide = true;

	while (valide) {
		cout << AFFICHENOM << quelJoueur << ":";

		getline(cin, ligne);

		if (ligne.size() < 1) {
			cout << ERREURNOM;
			valide = true;
		}
		else {

			valide = regex_match(ligne, regex(REGEXNOM));

			if (!valide) {
				cout << ERREURNOM;
				valide = true;
			}
			else {
				quelJoueur++;
				return ligne;
			}
		}

	}
	return "";
}

/****
Methode qui fait la distribution des cartes aux joueurs de la liste
reourne la liste des Joueurs
*****/
ListeJoueurs& distribuerCarte(int nbJoueurs, PileCartes p)
{
	ListeJoueurs liste;
	int total = p.getTaille();
	int reste = 0;
	int tour = 0;
	Joueur jtmp;
	liste.iterationDebut();
	while (liste.getTaille()<nbJoueurs) {
		string nom = demanderNom();
		jtmp = Joueur(nom);
		liste.ajouterFin(jtmp);
	}
	liste.iterationDebut();

	Carte tmp;

	while (reste < total) {
		tmp = p.retirerSommet();
		int num = rand() % nbJoueurs;
		switch (num) {
		case 1:
			liste.iterationSuivant();
			liste.iterationObtenir().ajouterCarte(tmp);
			break;
		case 2:
			liste.iterationSuivant();
			liste.iterationSuivant();
			liste.iterationObtenir().ajouterCarte(tmp);
			break;
		case 3:
			liste.iterationSuivant();
			liste.iterationSuivant();
			liste.iterationSuivant();
			liste.iterationObtenir().ajouterCarte(tmp);
			break;
		default:
			liste.iterationObtenir().ajouterCarte(tmp);
			break;

		}
		liste.iterationDebut();
		reste++;
	}


	return liste;
}

/*
Methode qui gere le jeux
*/
void debutJeu(PileCartes& millieu, ListeJoueurs& lesJoueurs, string fichier)
{

	int fin = 0;
	char valeur;
	string nomJoueur;
	ofstream leFichier;
	string *m;

	leFichier.open(fichier);

	while (lesJoueurs.getTaille() != 1) {

		if (lesJoueurs.iterationObtenir().getNombreCartes() == 0) {
			leFichier << lesJoueurs.iterationObtenir().getNom() << " est elimine(e)" << endl;
			lesJoueurs.iterationSupprimer();
		}
		else {
			nomJoueur = lesJoueurs.iterationObtenir().getNom();
			leFichier << nomJoueur << " a joue la carte ";
			Carte carte = lesJoueurs.iterationObtenir().getProchaineCarte();
			leFichier << carte.getID();
			leFichier << setw(15) << "==>" << lesJoueurs.iterationObtenir().getNombreCartes() << setw(15) << " ";
			millieu.ajouterCarte(carte);
			valeur = millieu.getSommet().getValeur();
			tenterVole(millieu, valeur, carte, lesJoueurs, nomJoueur, leFichier);
			lesJoueurs.iterationSuivant();
		}
	}

	string gagnant = lesJoueurs.iterationObtenir().getNom();
	leFichier << gagnant << " a gagner la partie!!" << endl;
	leFichier.close();

}

/*
Methode qui gere la bataille du jeu
*/
int bataille(int total, PileCartes& millieu, ListeJoueurs& liste, ofstream& leFichier)
{
	int compteur = 0;
	char obtenu;
	liste.iterationSuivant();
	while (compteur < total && liste.iterationObtenir().getNombreCartes() != 0) {
		leFichier << endl << liste.iterationObtenir().getNom() << " tente un vol avec ";
		Carte nouvCarte = liste.iterationObtenir().getProchaineCarte();
		leFichier  << nouvCarte.getID() << setw(10) << "==>" << liste.iterationObtenir().getNombreCartes()
			<< " "<< setw(15) << "la taille de la pile est "<< millieu.getTaille() << endl;
		obtenu = nouvCarte.getValeur();

		if (obtenu == 'V' || obtenu == 'D' || obtenu == 'R' || obtenu == 'A') {
			millieu.ajouterCarte(nouvCarte);
			brasserPaquetVoler(millieu);
;			if (millieu.getTaille() > 1) {

				millieu.retirerSommet();
				leFichier << liste.iterationObtenir().getNom() << " a vole le millieu" << setw(10) << " ==>" << liste.iterationObtenir().getNombreCartes() << setw(10) <<" ";
				while (millieu.getTaille() != 0) {
					viderMillieu(millieu, liste);
				}
			}
			else {
				millieu.retirerSommet();
				leFichier << liste.iterationObtenir().getNom() << " prends le millieu" << endl;
				prendreLaCarte(millieu, liste);
			}

			compteur = 8;
		}
		else {
			millieu.ajouterCarte(nouvCarte);
			leFichier << endl;
		}
		compteur++;
	}

	if (liste.iterationObtenir().getNombreCartes() == 0) {
		leFichier << liste.iterationObtenir().getNom() << " est elimine(e)" << endl;
		liste.iterationSupprimer();

	}

	return compteur;
}

/*
Methode qui compare les cartes des joueurs
*/
void tenterVole(PileCartes& millieu, char comparer, Carte carte, ListeJoueurs& liste, string nom, ofstream& leFichier)
{
	int compteur = 0;

	switch (comparer) {
	case 'V':
		if (liste.iterationObtenir().getNombreCartes() != 0) {

			compteur = bataille(1, millieu, liste, leFichier);

		}

		joueurAvantVole(millieu, liste, compteur, 1, nom, leFichier);

		break;
	case 'D':
		if (liste.iterationObtenir().getNombreCartes() != 0) {

			compteur = bataille(2, millieu, liste, leFichier);

		}

		joueurAvantVole(millieu, liste, compteur, 2, nom, leFichier);

		break;
	case 'R':
		if (liste.iterationObtenir().getNombreCartes() != 0) {

			compteur = bataille(3, millieu, liste, leFichier);

		}

		joueurAvantVole(millieu, liste, compteur, 3, nom, leFichier);
		break;
	case 'A':
		if (liste.iterationObtenir().getNombreCartes() != 0) {
			compteur = bataille(4, millieu, liste, leFichier);
		}

		joueurAvantVole(millieu, liste, compteur, 4, nom, leFichier);

		break;

	}
	leFichier << "La taille de la pile est " << millieu.getTaille() << endl;
}

/*
Methode qui vide les cartes du paquet
*/
void viderMillieu(PileCartes& millieu, ListeJoueurs& liste) {
	PileCartes paquetVoler;

	while (millieu.getTaille() != 0) {
		Carte nouvelle = millieu.retirerSommet();
		paquetVoler.ajouterCarte(nouvelle);
	}
	liste.iterationObtenir().ajouterCartesSousPaquet(paquetVoler);
}

/*
Methode qui prend la seul carte du paquet
*/
void prendreLaCarte(PileCartes& millieu, ListeJoueurs& liste) {
	PileCartes paquetVoler;
	Carte nouvelle = millieu.retirerSommet();
	liste.iterationObtenir().ajouterCartesSousPaquet(paquetVoler);
}

/*
Methode qui donne les cartes au bon joueur
*/
void joueurAvantVole(PileCartes& millieu, ListeJoueurs& liste, int compteur, int max, string nom, ofstream& leFichier) {

	if (compteur == max || compteur < max) {

		brasserPaquetVoler(millieu);

		while (liste.iterationObtenir().getNom() != nom) {
			liste.iterationSuivant();
		}
		millieu.retirerSommet();
		if (millieu.getTaille() > 1) {

			leFichier << liste.iterationObtenir().getNom() << " prends le millieu" << endl;
			while (millieu.getTaille() != 0) {
				viderMillieu(millieu, liste);
			}
		}
		else {
			leFichier << liste.iterationObtenir().getNom() << " prends le millieu" << endl;
			prendreLaCarte(millieu, liste);
		}
	}
}

/*
Methode qui demande le nom du fichier
*/
string demanderFichier()
{

	string ligne;
	bool valide = true;

	while (valide) {
		cout << AFFICHEFICHIER;

		getline(cin, ligne);

		if (ligne.size() < 1) {
			cout << AFFICHEERR;
			valide = true;
		}
		else {

			valide = regex_match(ligne, regex(REGEXFICHIER));

			if (!valide) {
				cout << AFFICHEERR;
				valide = true;
			}
			else {
				ligne = ligne + ".txt";
				valide = false;
			}
		}

	}

	return ligne;
}

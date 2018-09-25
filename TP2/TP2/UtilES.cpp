#include <iostream>
#include <fstream>
#include <string>
#include <regex>
#include "UtilES.h"
using namespace std;

void affichage(string mot) {
	
	cout << mot << endl;

}

void sauvegarder(string mot, string def) {
	ofstream f("tmp.txt", ios::app);
	f << mot << " : "<< def << "\n";
	f.close();
}

string ajusterDef(string cont) {
	string rep, remplacer;
	cout << "Le mot ajouter existe deja, sa definition est: " << cont << endl;
	cout << "Voulez-vous la modifier? (o/n) ";
	getline(cin, rep);
	if (rep == "o") {
		return rep;
	}
	return cont;
}

string demanderFichier() {
	string fichier;
	bool pasBon = true;
	while (pasBon) {
		cout << "Entrez le nom de fichier valide (nom.txt): ";
		getline(cin, fichier);
		if (fichier.size() > 4) {
			pasBon = verifierTexte(fichier);
			if (pasBon) {
				return fichier;
			}
			else {
				cout << "Le nom de fichier doit etre valide <nom.txt>, veuillez recommencer\n";
				pasBon = true;
			}
		}
		else {
			cout << "Le nom de fichier ne peut etre vide, veuillez recommencer\n";
		}
	}
	return "";
}

bool verifierTexte(string ligne) {
	int taille = ligne.size();
	for (int i = 0; i < taille; i++)
	{
		if (ligne[i] == '.' && ligne[i+1] == 't' 
			&& ligne[i + 2] == 'x' && ligne[i + 3] == 't') {
			ifstream verifier(ligne);
			if (verifier) {
				return true;
			}
		}
	}
	return false;
}

string* demanderAjout() {
	string entrer, laDef;
	string* tab = new string[2];
	bool pasBon = true;
	int nb = 0;
	system("cls");
	while (pasBon) {
		cout << "	AJOUT\nEntrez le mot a ajouter: ";
		getline(cin, entrer);
		if (entrer.size() > 0) {
			pasBon = regex_match(entrer, regex(REGEX));
			if (pasBon) {
				tab[0] = entrer;
				cout << "Entrez la definition: ";
				getline(cin, laDef);
				if (laDef.size() > 0) {
					pasBon = regex_match(laDef, regex(REGEX));
					if (pasBon) {
						tab[1] = laDef;
						pasBon = false;
					}
					else {
						cout << "La definition est invalide, veuillez recommencer\n";
					}

				}
				else {
					cout << "La definition ne peut etre vide, veuillez recommencer\n";
				}
			}
			else {
				cout << "Ce mot n'est pas valide, veuillez recommencer\n";
			}
		}
		else {
			cout << "Le ne peut etre vide, veuillez recommencer\n";
		}

	}
	return tab;
}
string demanderMot() {
	string entrer;
	bool nonValide = true;
	system("cls");
	while (nonValide) {
		cout << "	RECHERCHE\nVeuillez entrer votre mot: ";
		getline(cin, entrer);
		if (entrer.size() > 0) {
			nonValide = regex_match(entrer, regex(REGEX));
			if (nonValide) {
				return entrer;
			}
			else {
				cout << "Ce mot est invalide, veuillez recommencer\n";
			}
		}
		else {
			cout << "Le mot ne peut etre vide, veuillez recommencer\n";
		}
	}

}

string afficherMot() {
	string entrer;
	bool nonValide = true;
	system("cls");
	while (nonValide) {
		cout << "	AFFICHAGE\nVeuillez entrer votre mot: ";
		getline(cin, entrer);
		if (entrer.size() > 0) {
			nonValide = regex_match(entrer, regex(REGEX));
			if (nonValide) {
				return entrer;
			}
			else {
				cout << "Ce mot est invalide, veuillez recommencer\n";
			}
		}
		else {
			entrer = "";
			nonValide = false;
		}
	}
	return entrer;
}

int verifierSelection() {
	string entrer;
	bool pasBon = true;
	while (pasBon) {
		cout << "Entrer votre choix...";
		getline(cin, entrer);
		if (entrer == "1" || entrer == "2" || entrer == "3" || entrer == "4") {
			int choix = stoi(entrer);
			return choix;
		}
		else {
			cout << "Mauvais choix veuillez recommencer\n";
		}
	}
}

int menu() {
	system("cls");
	cout << "	MENU\n" << "Ajouter un mot.......1\n" << "Rechercher un mot....2\n";
	cout << "Afficher le lexique..3\n" << "Quitter..............4" << endl;
	return verifierSelection();
}
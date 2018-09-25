#ifndef UTILES_H
#define UTILES_H
#include <string>
#define VIDE ""
#define REGEX "[a-zA-Z ]+"

using namespace std;

void affichage(string mot);
string demanderMot();
string afficherMot();
string demanderFichier();
bool verifierTexte(string m);
void sauvegarder(string mot, string def);
string ajusterDef(string def);
int verifierSelection();
int menu();
string* demanderAjout();
#endif
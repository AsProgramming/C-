#ifndef NOEUD_H
#define NOEUD_H
/* Classe noeud qui permet de chaîner des lettres et une definition s'il y a lieu
 * Auteur: Edwin Andino
 */
#include <list>
#include <string>
using namespace std;

class Noeud {
public:
	// Constructeur par défaut
	Noeud();

	// Constructeur avec une lettre
	Noeud(char& lettre);
	
	// Constructeur avec une definition
	Noeud(char& lettre, string& definition);

	// Destructeur
	~Noeud();

	// permet de changer la lettre du noeud
	void setLettre(char& lettre);
	
	// permet de changer la definition du noeud
	void setDefinition(string& definition);

	// permet de changer la definition du noeud
	void setFils(Noeud*& nouveau);

	// Retourne la definition du noeud
	string getDefinition() const;
	
	// Retourne la lettre du noeud
	char getLettre() const;

	// permet de changer la definition du noeud
	list<Noeud*> getFils() const;

	// perme de savoir si la liste est vide ou non
	bool estVide();

private:
	char lettre;
	string definition;
	list<Noeud*> fils;
};
#endif;
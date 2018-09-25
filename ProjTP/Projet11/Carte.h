#ifndef CARTE_H
#define CARTE_H

#include <string>

using namespace std;

class Carte {

public:
	Carte(const string& id = "");
	Carte(const Carte& carte);
	~Carte();

	const Carte& operator=(const Carte& carte);

	void setID(const string& id);
	const string& getID() const;
	char getValeur() const;

private:
	string id;
};

#endif

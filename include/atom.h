#ifndef ATOM_H
#define ATOM_H

#include "simpleObj.h"
#include <string>
using namespace std;

class Atom: public SimpleObj {

private:
	string _symbol;
public:
	Atom(string s);
	string symbol() const;
	string value() const;
    bool match(SimpleObj& simple);
};
#endif
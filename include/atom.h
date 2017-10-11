#ifndef ATOM_H
#define ATOM_H

#include "term.h"
#include "variable.h"
#include <string>

using namespace std;

class Atom: public Term {

private:
	string _symbol;
public:
	Atom(string);
	string symbol() const;
	string value() const;
	bool match(Variable& v);
    bool match(Term&);
};
#endif
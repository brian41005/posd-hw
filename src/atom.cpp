#include "../include/atom.h"
#include <iostream>
Atom::Atom(string s) : _symbol(s) {}

string Atom::symbol() { return _symbol; }

string Atom::value() { return _symbol; }

bool Atom::match(Term& term) {
    if (Variable* v = term.getVariable())
        return v->match(*this);
    return this->symbol() == term.symbol();
}
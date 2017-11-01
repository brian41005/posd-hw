#include "../include/atom.h"

Atom::Atom(string s) : _symbol(s) {}

string Atom::symbol() const { return _symbol; }

string Atom::value() { return _symbol; }

bool Atom::match(Variable& v, vector<Variable*> record) {
    return v.match(*this);
}

bool Atom::match(Term& term, vector<Variable*> record) {
    return this->symbol() == term.symbol();
}
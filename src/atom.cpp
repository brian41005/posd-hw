#include "../include/atom.h"

Atom::Atom(string s) : _symbol(s) {}

string Atom::symbol() const { return _symbol; }

string Atom::value() const { return _symbol; }

bool Atom::match(Term& term) {
    if (Variable* v = term.getVariable()) return v->match(*this);
    return this->symbol() == term.symbol();
}
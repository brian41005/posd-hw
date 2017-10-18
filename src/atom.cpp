#include "../include/atom.h"

Atom::Atom(string s) : _symbol(s) {}

string Atom::symbol() const { return this->_symbol; }

string Atom::value() const { return this->_symbol; }

bool Atom::match(Variable& v) { return v.match(*this); }

bool Atom::match(Term& term) { return this->symbol() == term.symbol(); }
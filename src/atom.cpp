#include "../include/atom.h"
#include <string>

Atom::Atom(string s) : symbol(s) {}

bool Atom::operator==(Atom a) { return symbol == a.symbol; }
#include "../include/atom.h"
#include "../include/variable.h"
#include <string>
#include <typeinfo>

Atom::Atom(string s) : _symbol(s) {

}

string Atom::symbol() const{
    return this->_symbol;
}

string Atom::value() const{
    return this->_symbol;
}

bool Atom::match(Term& term){
    if (typeid(term) == typeid(Variable))
        return term.match(*this);
    else
        return this->symbol() == term.symbol();
}
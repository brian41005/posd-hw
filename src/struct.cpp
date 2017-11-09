#include "../include/struct.h"
#include <iostream>
Struct::Struct(): _name(Atom(".")), _terms(vector<Term*>{}) {

}
Struct::Struct(Atom atom, vector<Term*> terms) : _name(atom), _terms(terms) {}

Atom Struct::name() { return _name; }

Term* Struct::args(int i) { return (i < _terms.size())?_terms[i]:nullptr; }

int Struct::arity(){
    size_t ZERO = 0;
    return std::max(ZERO, _terms.size());
}

string Struct::symbol() {
    ostringstream out;
    out << _name.symbol() << "(";
    if (!_terms.empty()) out << _terms[0]->symbol();
    for (auto t = _terms.begin() + 1; t < _terms.end(); t++)
        out << ", " << (*t)->symbol();
    out << ")";
    return out.str();
}

string Struct::value() {
    ostringstream out;
    out << _name.value() << "(";
    if (!_terms.empty()) out << _terms[0]->value();
    for (auto t = _terms.begin() + 1; t < _terms.end(); t++)
        out << ", " << (*t)->value();
    out << ")";
    return out.str();
}


bool Struct::match(Term& term) { 
    if (Variable* v = term.getVariable())
        return v->match(*this); 
    else if (Struct* s = term.getStruct()){
        if (_name.match(s->_name) && _terms.size() == s->_terms.size()) {
            for (int i = 0; i < _terms.size(); i++){
                if (_terms.size() == 2 && i == 0)
                    if (s->_terms[0]->getVariable() && s->_terms[1]->symbol() == "[]")
                        return s->_terms[0]->match(*this);
                if (!_terms[i]->match(*s->_terms[i])) return false;

            }
            return true;
        }
    }
    return false; 
}

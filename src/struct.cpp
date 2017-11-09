#include "../include/struct.h"
#include <iostream>
Struct::Struct(): _name(Atom(".")), _terms(vector<Term*>{}) {

}
Struct::Struct(Atom atom, vector<Term*> terms) : _name(atom), _terms(terms) {}

Struct::Struct(Atom name, Term* head, Term* tail):_name(name){
    if (head)
        _terms.push_back(head);
    if (tail)
        _terms.push_back(tail);
}
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
            int failTime = 0;
            for (int i = 0; i < _terms.size(); i++)
                failTime += (!_terms[i]->match(*s->_terms[i]));
            return failTime == 0;
        }
    }
    return false; 
}

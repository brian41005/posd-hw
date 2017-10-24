#include "../include/struct.h"

Struct::Struct(Atom atom, vector<Term*> terms) : _name(atom), _terms(terms) {}

const Atom Struct::name() const { return _name; }

const Term* Struct::args(int i) const { return _terms[i]; }

string Struct::symbol() const {
    ostringstream out;
    out << _name.symbol() << "(";
    if (!_terms.empty()) out << _terms[0]->symbol();
    for (auto t = _terms.begin() + 1; t < _terms.end(); t++)
        out << ", " << (*t)->symbol();
    out << ")";
    return out.str();
}

string Struct::value(vector<Term*> record) {
    record.push_back(this);
    ostringstream out;
    out << _name.value() << "(";
    if (!_terms.empty()) out << _terms[0]->value(record);
    for (auto t = _terms.begin() + 1; t < _terms.end(); t++)
        out << ", " << (*t)->value(record);
    out << ")";
    return out.str();
}

bool Struct::match(Variable& v, vector<Variable*> record) {
    return v.match(*this);
}

bool Struct::match(Struct& s, vector<Variable*> record) {
    if (_name.match(s._name) && _terms.size() == s._terms.size()) {
        int failTime = 0;
        for (int i = 0; i < _terms.size(); i++)
            failTime += (!_terms[i]->match(*s._terms[i]));
        return failTime == 0;
    }
    return false;
}

bool Struct::match(Term& term, vector<Variable*> record) { return false; }
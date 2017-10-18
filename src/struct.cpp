#include "../include/struct.h"

Struct::Struct(Atom atom, vector<Term*> terms) : _name(atom), _terms(terms) {}

const Atom Struct::name() const { return this->_name; }

const Term* Struct::args(int i) const { return this->_terms[i]; }

string Struct::symbol() const {
    ostringstream out;
    out << this->name().symbol() << "(" << _terms[0]->symbol();
    for (auto t = _terms.begin() + 1; t != _terms.end(); t++)
        out << ", " << (*t)->symbol();
    out << ")";
    return out.str();
}

string Struct::value() const {
    ostringstream out;
    out << this->name().value() << "(" << _terms[0]->value();
    for (auto t = _terms.begin() + 1; t != _terms.end(); t++)
        out << ", " << (*t)->value();
    out << ")";
    return out.str();
}

bool Struct::match(Term& term) {
    if (Struct* s = term.getStruct()) {
        if (!(_name.match(s->_name)) || _terms.size() != s->_terms.size())
            return false;
        else {
            for (int i = 0; i < _terms.size(); i++)
                if (!_terms[i]->match(*s->_terms[i])) return false;
            return true;
        }
    } else
        return false;
}

Struct* Struct::getStruct() { return this; }
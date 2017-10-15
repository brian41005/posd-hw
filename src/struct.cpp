#include "../include/struct.h"


Struct::Struct(Atom atom, vector<Term*> terms):_name(atom), _terms(terms){
}

const Atom Struct::name() const{
    return this->_name;
}

const Term* Struct::args(int i) const{
    return this->_terms[i];
}

string Struct::symbol() const{
    string s = this->name().symbol() +  "(" + _terms[0]->symbol();
    for (auto t = _terms.begin()+1; t != _terms.end(); t++)
        s += ", " + (*t)->symbol();
    return s + ")";

}

string Struct::value() const{
    string s = this->name().value() +  "(" + _terms[0]->value();
    for (auto t = _terms.begin()+1; t != _terms.end(); t++)
        s += ", " + (*t)->value();
    return s + ")";
}

bool Struct::match(Term& term){
    Struct* s = dynamic_cast<Struct*>(&term);
    if (s){
        if (!(_name.match(s->_name)) || _terms.size() != s->_terms.size())
            return false;
        else{
            for (int i = 0; i < _terms.size(); i++)
                if (!this->_terms[i]->match(*s->_terms[i]))
                    return false;
            return true;
        }
    }
    else
        return false;
}
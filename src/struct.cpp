#include "../include/struct.h"

Struct::Struct(vector<Term*> terms): _terms(terms){
}

string Struct::symbol() const{
    string s = "";
    for(Term* t: _terms)
        s += t->symbol();
    return s;

}

string Struct::value() const{
    return this->symbol();
}

bool Struct::match(Term& term){
    return false;
    
}
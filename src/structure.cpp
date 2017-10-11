#include "../include/structure.h"

Structure::Structure(vector<Term*> terms): _terms(terms){
}

string Structure::symbol() const{
    string s = "";
    for(Term* t: _terms)
        s += t->symbol();
    return s;

}

string Structure::value() const{
    return this->symbol();
}

bool Structure::match(Term& term){
    return false;
    
}
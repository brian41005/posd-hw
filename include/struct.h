#ifndef STRUCT_H
#define STRUCT_H


#include <sstream>
#include <string>
#include <vector>
#include "term.h"
#include "atom.h"
using std::vector;

class Struct : public Term {
   protected:
    vector<Term *> _terms;
    Atom _name;
    
   public:
    Struct();
    Struct(Atom, Term*, Term*);
    Struct(Atom, vector<Term *>);
    Atom name();
    Term *args(int);
    int arity();
    
    // Term's interface
   public:
    string symbol();
    string value();
    bool match(Term &);
    Struct *getStruct() { return this; }
    Iterator<Term*>* createIterator() {return new StructIterator(this);}
};

#endif
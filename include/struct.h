#ifndef STRUCT_H
#define STRUCT_H


#include <sstream>
#include <string>
#include <vector>
#include "atom.h"
#include "term.h"
using std::vector;

class Struct : public Term {
   private:
    
   protected:
    vector<Term *> _terms;
    Atom _name;
    
public:
    Struct();
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
};

#endif
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
    vector<Term*> _terms;
    Atom _name;

   public:
    Struct(Atom, vector<Term*>);
    const Atom name() const;
    const Term* args(int) const;
    bool match(Variable&);
    bool match(Struct&);
   
   //Term's interface 
   public:
    string symbol() const;
    string value(vector<Term*> record = vector<Term*>{});
    bool match(Term&);
    Struct* getStruct() { return this; }
};

#endif
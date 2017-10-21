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
    Struct* getStruct() { return this; }

   public:
    string symbol() const;
    string value() const;
    bool match(Term&);
};

#endif
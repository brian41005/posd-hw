#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include "atom.h"
#include <string>
#include <vector>

using std::vector;

class Struct: public Term{
private:
    vector<Term*> _terms;
    Atom _name;
public:
    Struct(Atom, vector<Term*>);
    const Atom name() const;
    const Term* args(int) const;
    string symbol() const;
    string value() const;
    bool match(Term&);
    Struct* getStruct();
};

#endif
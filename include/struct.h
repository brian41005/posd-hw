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
    vector<Term *> _terms;
    Atom _name;

   public:
    Struct(Atom, vector<Term *>);
    const Atom name() const;
    const Term *args(int) const;
    bool match(Variable &, vector<Variable *> record = vector<Variable *>{});
    bool match(Struct &, vector<Variable *> record = vector<Variable *>{});

    // Term's interface
   public:
    string symbol() const;
    string value(vector<Term *> record = vector<Term *>{});
    bool match(Term &, vector<Variable *> record = vector<Variable *>{});
    Struct *getStruct() { return this; }
};

#endif
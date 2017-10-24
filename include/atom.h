#ifndef ATOM_H
#define ATOM_H

#include <string>
#include "term.h"
#include "variable.h"

using namespace std;

class Atom : public Term {
   private:
    const string _symbol;

   public:
    Atom(string);
    bool match(Variable&, vector<Variable*> record = vector<Variable*>{});

    // Term's interface
   public:
    string symbol() const;
    string value(vector<Term*> record = vector<Term*>{});
    bool match(Term&, vector<Variable*> record = vector<Variable*>{});
};
#endif
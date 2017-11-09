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
    bool match(Variable&);

    // Term's interface
   public:
    string symbol();
    string value();
    bool match(Term&);
};
#endif
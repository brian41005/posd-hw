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

   public:
    string symbol() const;
    string value() const;
    bool match(Term&);
};
#endif
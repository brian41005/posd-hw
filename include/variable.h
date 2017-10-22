#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <set>
#include <vector>
#include "term.h"

using namespace std;

class Variable : public Term {
   private:
    const string _symbol;
    Term* _value;

   public:
    Variable(string);

   public:
    string value(vector<Term*> record = vector<Term*>{});
    string symbol() const;
    bool match(Term&);
    Variable* getVariable() { return this; }
};
#endif
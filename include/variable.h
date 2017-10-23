#ifndef VARIABLE_H
#define VARIABLE_H

#include <string>
#include <algorithm>
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
    
    //Term's interface
   public:
    string symbol() const;
    string value(vector<Term*> record = vector<Term*>{});
    bool match(Term&);
    Variable* getVariable() { return this; }
};
#endif
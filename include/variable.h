#ifndef VARIABLE_H
#define VARIABLE_H

#include <algorithm>
#include <set>
#include <string>
#include <vector>
#include "term.h"

using namespace std;

class Variable : public Term {
   private:
    const string _symbol;
    Term* _value;
    bool _isSearching;
    string getLastSymbol();
   public:
    Variable(string);

    // Term's interface
   public:
    string symbol() const;
    string value();
    bool match(Term&, vector<Variable*> record = vector<Variable*>{});
    Variable* getVariable() { return this; }
};
#endif
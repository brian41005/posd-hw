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
    bool _isMatching;
    string getLastSymbol();
    bool matchForce(Term&);
   public:
    Variable(string);

    // Term's interface
   public:
    string symbol();
    string value();
    bool match(Term&);
    Variable* getVariable() { return this; }
};
#endif
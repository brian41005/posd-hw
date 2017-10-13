#ifndef VARIABLE_H
#define VARIABLE_H

#include "term.h"
#include <string>

using namespace std;

class Variable: public Term{

 private:
    string _symbol;
    Term* _value;
 public:
    Variable(string);
    string value() const;
    string symbol() const;
    bool match(Term&);
 };
#endif
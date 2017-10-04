#ifndef VARIABLE_H
#define VARIABLE_H

#include "simpleObj.h"
#include <string>

using namespace std;

class Variable: public SimpleObj{

 private:
    string _symbol, _value;
 public:
    Variable(string symbol);
    string value() const;
    string symbol() const;
    bool match(SimpleObj& simple);
 };
#endif
#ifndef NUMBER_H
#define NUMBER_H

#include "simpleObj.h"
#include <string>

using namespace std;

class Number: public SimpleObj{

private:
    string _symbol;

public:
    Number(string s);
    float value() const;
    string symbol() const;
    bool match(const Number n) const;

};
#endif
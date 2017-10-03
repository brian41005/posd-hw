#ifndef NUMBER_H
#define NUMBER_H

#include "simpleObj.h"
#include <string>

using namespace std;

class Number: public SimpleObj{

private:
    int _n;

public:
    Number(int n);
    string value() const;
    string symbol() const;
    bool match(SimpleObj& simple);

};
#endif
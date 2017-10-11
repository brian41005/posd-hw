#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include "variable.h"
#include <string>

using namespace std;

class Number: public Term{

private:
    int _n;

public:
    Number(int);
    string value() const;
    string symbol() const;
    bool match(Variable& v);
    bool match(Term&);

};
#endif
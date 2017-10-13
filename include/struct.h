#ifndef STRUCT_H
#define STRUCT_H

#include "term.h"
#include <string>
#include <vector>

using std::vector;

class Struct: public Term{
private:
    vector<Term*> _terms;
public:
    Struct(vector<Term*>);
    string symbol() const;
    string value() const;
    bool match(Term&);
};

#endif
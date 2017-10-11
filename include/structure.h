#ifndef STRUCTURE_H
#define STRUCTURE_H

#include "term.h"
#include <string>
#include <vector>

using std::vector;

class Structure: public Term{
private:
    vector<Term*> _terms;
public:
    Structure(vector<Term*>);
    string symbol() const;
    string value() const;
    bool match(Term&);
};

#endif
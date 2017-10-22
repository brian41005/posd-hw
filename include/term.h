#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>
class Struct;
class Variable;
class List;

using namespace std;

class Term {
   public:
    virtual string symbol() const = 0;
    virtual string value(vector<Term*> record = vector<Term*>{}) = 0;
    virtual bool match(Term&) = 0;

   public:
    // get composite
    virtual Variable* getVariable() { return NULL; }
    virtual Struct* getStruct() { return NULL; }
    virtual List* getList() { return NULL; }
};

#endif
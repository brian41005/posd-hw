#ifndef TERM_H
#define TERM_H

#include <string>
#include <vector>
#include "iterator.h"
class Struct;
class Variable;
class List;

using namespace std;

class Term {
   public:
    virtual string symbol() = 0;
    virtual string value() = 0;
    virtual bool match(Term&) = 0;

   public:
    // get composite
    virtual Variable* getVariable() { return NULL; }
    virtual Struct*   getStruct() { return NULL; }
    virtual List*     getList() { return NULL; }

    //iterator
    virtual Iterator<Term*>* createIterator() {return new NullIterator<Term*>();}
    Iterator<Term*>* createDFSIterator() {
        return new DFSIterator<Term*>(createIterator());
    }
    Iterator<Term*>* createBFSIterator() {
        return new BFSIterator<Term*>(createIterator());
        }
};

#endif
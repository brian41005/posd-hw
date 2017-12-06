#ifndef LIST_H
#define LIST_H

#include <sstream>
#include <vector>
#include "struct.h"
#include "term.h"
#include <initializer_list>
using std::initializer_list;
using std::vector;

class List : public Struct {
   public:
    List();
    List(Term*, Term*);
    List(vector<Term *>);
    List(initializer_list<Term *>);
    
    Term *head() const;
    List *tail() const;
    // Term's interfaces
   public:
    string symbol();
    string value();
    List *getList() { return this; }
    Iterator<Term*>* createIterator() {return new ListIterator(this);}
};

#endif
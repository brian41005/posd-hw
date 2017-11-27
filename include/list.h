#ifndef LIST_H
#define LIST_H

#include <sstream>
#include <vector>
#include "struct.h"
#include "term.h"
using std::runtime_error;
using std::vector;

class List : public Struct {
   public:
    List(vector<Term *>);
    List(Term *head = nullptr, Term *tail = nullptr);
    Term *head() const;
    List *tail() const;
    // Term's interfaces
   public:
    string symbol();
    string value();
    List *getList() { return this; }
};

#endif
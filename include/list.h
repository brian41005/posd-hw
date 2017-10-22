#ifndef LIST_H
#define LIST_H

#include <sstream>
#include <vector>
#include "term.h"

using std::vector;
using std::runtime_error;

class List : public Term {
   private:
    vector<Term *> _elements;

   public:
    List();
    List(const vector<Term *> &);
    Term *head() const;
    List *tail() const;

   public:
    string symbol() const;
    string value(vector<Term*> record = vector<Term*>{});
    bool match(Term &term);
    List* getList(){return this;}
};

#endif
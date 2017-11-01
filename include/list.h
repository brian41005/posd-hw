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
    List(vector<Term *>);
    Term *head() const;
    List *tail() const;
    bool match(Variable&, vector<Variable *> record = vector<Variable *>{});
    bool match(List&, vector<Variable *> record = vector<Variable *>{});
    // Term's interfaces
   public:
    string symbol() const;
    string value();
    bool match(Term&, vector<Variable *> record = vector<Variable *>{});
    List *getList() { return this; }
};

#endif
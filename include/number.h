#ifndef NUMBER_H
#define NUMBER_H

#include <iomanip>
#include <sstream>
#include <string>
#include "term.h"
#include "variable.h"

using namespace std;

class Number : public Term {
   private:
    string _n;

   public:
    Number(double);

   public:
    string value(vector<Term*> record = vector<Term*>{});
    string symbol() const;
    bool match(Term &);
};
#endif
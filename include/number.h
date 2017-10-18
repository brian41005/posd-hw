#ifndef NUMBER_H
#define NUMBER_H

#include <string>
#include <type_traits>
#include "term.h"
#include "variable.h"

using namespace std;

class Number : public Term {
   private:
    string _n;

   public:
    Number(int);
    Number(double);
    string value() const;
    string symbol() const;
    bool match(Variable& v);
    bool match(Term&);
};
#endif
#ifndef NUMBER_H
#define NUMBER_H

#include "term.h"
#include "variable.h"
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

class Number : public Term {
private:
  string _n;

public:
  Number(double);
  string value() const;
  string symbol() const;
  bool match(Term &);
};
#endif
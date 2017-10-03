#ifndef ATOM_H
#define ATOM_H

#include <string>
using namespace std;

class Atom {
 public:
  string symbol;

  Atom(string s);
  bool operator==(Atom a);
};
#endif
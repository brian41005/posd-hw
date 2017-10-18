#ifndef TERM_H
#define TERM_H

#include <string>
class Struct;
using namespace std;

class Term {
   public:
    virtual string symbol() const = 0;
    virtual string value() const = 0;
    virtual bool match(Term&) = 0;
    virtual Struct* getStruct() { return NULL; }
};

#endif
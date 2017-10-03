#ifndef SIMPLEOBJ_H
#define SIMPLEOBJ_H

#include <string>
//class Number;

using namespace std;

class SimpleObj{
    public:
        virtual string symbol() const = 0;
        virtual string value() const = 0;
        virtual bool match(SimpleObj& simple) = 0;
};

#endif
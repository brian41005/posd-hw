#ifndef SIMPLEOBJ_H
#define SIMPLEOBJ_H

class Number;


class SimpleObj{
    public:
        virtual bool match(const Number n) const = 0;
};

#endif
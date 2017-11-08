#ifndef PROLOG_H
#define PROLOG_H

#include "atom.h"

class Prolog
{

private:
    static Prolog *_instance;

protected:
    Prolog();

public:
    const int NONE = -1;
    const int EOS = '\0';
    const int NUMBER = 256;
    const int ATOM = 257;
    const int ATOMSC = 258;
    const int VARIABLE = 259;
    Atom EMPTY_LIST = Atom("[]");
    static Prolog *getInstance();
    bool isSpecialChar(char c);

};

#endif